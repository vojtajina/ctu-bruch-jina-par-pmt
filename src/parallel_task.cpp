#include "parallel_task.h"

ParallelTask::ParallelTask()
{
  // init MPI
  MPI_Init (0, 0);
  MPI_Comm_rank (MPI_COMM_WORLD, &peerId);
  MPI_Comm_size (MPI_COMM_WORLD, &peersCount);

  localRequestsCounter = peerId;
  globalBestConfSteps = 0;

  stopOnFirstFound = false;
  stopOnBestFound = true;
  donorAlg = ParallelTask::LOCAL;
}

ParallelTask::~ParallelTask()
{
  MPI_Finalize();
}

void ParallelTask::initConfiguration(Configuration* init)
{
  AbstractTask::initConfiguration(init);

  isActive = true;
  requestSent = false;
  tokenSent = false;
  recievedSollutionsCount = 0;
  stack = new DSplitStack();

  if (this->isMaster() )
  {
    IntPriQueue* positions = init->getAvailablePositions();

    printf("%d: init positions(%d)\n", peerId, positions->size());

    while (!positions->empty() )
      stack->push (positions->reversePop() );

    delete positions;

    int splitDivider;
    int* data;
    AbstractSplitStack* ss;

    // send work to each slave
    for (int i = 1; i < peersCount; i++)
    {
      splitDivider = peersCount - i + 1;
      printf("%d: split for %d\n", peerId, splitDivider);
      if (stack->canSplit(splitDivider))
      {
        ss = stack->split(splitDivider);
        data = ss->toArray();
        this->send(i, MSG_WORK_SENT, data, ss->size());

        delete ss;
        delete data;
      }
      else
      {
        int zero = 0;
        this->send(i, MSG_WORK_SENT, &zero, 1);
      }
    }
  }
  // slave wait for initial work
  else
  {
    this->handleWorkSent();
  }
}

void ParallelTask::processConfiguration()
{
  // state machine
  while (isActive)
  {
    this->processStack();
    this->noWork();
    this->checkNewMessage();
  }
}

void ParallelTask::releaseMemory()
{
  AbstractTask::releaseMemory();
  delete stack;

  if (!this->isMaster() && bestConf)
  {
    delete bestConf;
    bestConf = 0;
  }
}

bool ParallelTask::isMaster() const
{
  return (peerId == 0);
}

int ParallelTask::getNextPeerId() const
{
  return ParallelTask::getNextPeerId(peerId);
}

int ParallelTask::getNextPeerId(int id) const
{
  return (id + 1) % peersCount;
}

void ParallelTask::incRecievedSollutions()
{
  recievedSollutionsCount++;

  if (recievedSollutionsCount == (peersCount - 1))
  {
    isActive = false;
    printf("%d: MASTER RECIEVED ALL SOLLUTIONS - TIME TO END THIS SHIT!\n", peerId);
  }
}

void ParallelTask::checkNewMessage()
{
  printf("%d: check messages\n", peerId);

  int flag;
  MPI_Status status;
  MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);

  // there is a new message

  if (flag)
  {
    printf("%d: new msg(%d)\n", peerId, status.MPI_TAG);

    switch (status.MPI_TAG)
    {
        // sender is requesting work
      case MSG_WORK_REQUEST:
        this->handleWorkRequest();
        break;

        // work for us is comming
      case MSG_WORK_SENT:
        this->handleWorkSent();
        break;

        // sender has no work for us
      case MSG_WORK_NOWORK:
        this->handleWorkNone();
        break;

        // finishing token is here
      case MSG_TOKEN:
        this->handleToken();
        break;

        // master is sending finish signal
      case MSG_FINISH:
        this->handleFinish();
        break;

        // sender is sending his sollution
      case MSG_SOLLUTION:
        this->handleSollution();
        break;

        // sender did not found any sollution
      case MSG_NO_SOLLUTION:
        this->handleNoSollution();
        break;

        // send has found new global best, here is the steps value
      case MSG_SOLLUTION_STEPS:
        this->handleSollutionSteps();
        break;
    }
  }
}

void ParallelTask::processStack()
{
  printf("%d: check stack (size: %d)\n", peerId, stack->size());

  int counter = 0;

  while (!stack->empty() && !isFinished && isActive)
  {
    int position = stack->head();

    if (position < 0)
    {
      stack->pop();
      workConf->moveBack();
    }
    else
    {
      workConf->move(position);
      stack->turnHead();

      if (workConf->final())
        printf("%d: SOLLUTION(%d)\n", peerId, workConf->getStepsCount());

      if (this->checkConfiguration())
      {
        IntPriQueue* pq = workConf->getAvailablePositions();

        while (!pq->empty())
          stack->push(pq->reversePop());

        delete pq;
      }
    }

    if ((++counter % CHECK_MSG_INTERVAL) == 0)
      this->checkNewMessage();
  }
}

void ParallelTask::noWork()
{
  printf("%d: no work (active: %s, finished: %s)\n", peerId, isActive ? "true" : "false", isFinished ? "true" : "false");

  // master does not request for work
  // send finish token

  if (this->isMaster() )
  {
    if (!tokenSent)
    {
      this->send(this->getNextPeerId(), MSG_TOKEN, TOKEN_WHITE);
      tokenSent = true;
    }
  }

  // no master
  else
  {
    if (!requestSent)
      this->sendWorkRequest();
  }
}

void ParallelTask::handleFinish ()
{
  MPI_Status status;
  MPI_Recv(0, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

  printf("%d: recieved finish\n", peerId);
  // I have sollution - send it to master

  if (bestConf)
  {
    int* sollution = bestConf->toArray();
    this->send(status.MPI_SOURCE, MSG_SOLLUTION, sollution, bestConf->getStepsCount());
    delete sollution;
  }
  else
  {
    this->send(status.MPI_SOURCE, MSG_NO_SOLLUTION);
  }

  isActive = false;
}

void ParallelTask::handleToken ()
{
  MPI_Status status;
  char token;
  MPI_Recv(&token, 1, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

  printf("%d: recieved token: %c\n", peerId, token);

  if (this->isMaster())
  {
    // all peers have already finished
    // send finish token to all peers
    if (token == TOKEN_WHITE)
    {
      this->broadcast(MSG_FINISH);
    }
    else
    {
      tokenSent = false;
    }
  }
  else
  {
    // this peer is not finished yet
    if (!isFinished && !stack->empty())
      token = TOKEN_BLACK;

    // if token is black - send direct to master
    this->send((token == TOKEN_BLACK) ? 0 : this->getNextPeerId(), MSG_TOKEN, token);
  }
}

void ParallelTask::handleWorkNone ()
{
  MPI_Status status;
  MPI_Recv(0, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

  printf("%d: no work\n", peerId);

  // send new request
  this->sendWorkRequest();
}

void ParallelTask::handleWorkRequest ()
{
  MPI_Status status;
  MPI_Recv(0, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

  printf("%d: recieved work request\n", peerId);
  // i can split the stack
  // so i have some work for the sender

  if (stack->canSplit() && !isFinished)
  {
    AbstractSplitStack* s = stack->split();
    int* sa = s->toArray();
    this->send(status.MPI_SOURCE, MSG_WORK_SENT, sa, s->size());

    delete s;
    delete sa;
  }

  // there is no work
  else
  {
    this->send(status.MPI_SOURCE, MSG_WORK_NOWORK);
  }
}

void ParallelTask::handleWorkSent ()
{
  MPI_Status status;
  int buffer[BUFFER_SIZE];
  MPI_Recv(&buffer, BUFFER_SIZE, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

  requestSent = false;
  // TODO check if the stack is empty, it should be

  int i = 0;
  workConf = new Configuration(*initConf);

  while (buffer[i] != 0 && i < BUFFER_SIZE)
  {
    stack->push(buffer[i]);

    if (buffer[i] < 0)
      workConf->move(-buffer[i]);

    i++;
  }

  printf("%d: recieved work(%d)\n", peerId, i);
}

void ParallelTask::handleSollution()
{
  printf("%d: recieved sollution\n", peerId);

  MPI_Status status;
  int buffer[BUFFER_SIZE];
  MPI_Recv(&buffer, BUFFER_SIZE, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

  // TODO check if the stack is empty, it should be

  int i = 0;
  Configuration* cnf = new Configuration(*initConf);

  while (buffer[i] != 0 && i < BUFFER_SIZE)
  {
    cnf->move(buffer[i]);
    i++;
  }

  // compare with local best
  if (cnf->getStepsCount() < bestConf->getStepsCount())
  {
    delete bestConf;
    bestConf = cnf;
  }
  else
  {
    delete cnf;
  }

  this->incRecievedSollutions();
}

void ParallelTask::handleNoSollution()
{
  MPI_Status status;
  MPI_Recv(0, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
  this->incRecievedSollutions();
}

void ParallelTask::send(int recieverId, int tag)
{
  printf("%d: send %d to %d\n", peerId, tag, recieverId);

  MPI_Send (0, 0, MPI_INT, recieverId, tag, MPI_COMM_WORLD);
}

void ParallelTask::send(int recieverId, int tag, int message)
{
  printf("%d: send %d(value: %d) to %d\n", peerId, tag, message, recieverId);

  MPI_Send (&message, 1, MPI_INT, recieverId, tag, MPI_COMM_WORLD);
}

void ParallelTask::send(int recieverId, int tag, char message)
{
  printf("%d: send(%c) %d to %d\n", peerId, message, tag, recieverId);

  MPI_Send (&message, 1, MPI_CHAR, recieverId, tag, MPI_COMM_WORLD);
}

void ParallelTask::send(int recieverId, int tag, int* message, int msgLength)
{
  printf("%d: send(size: %d) %d to %d\n", peerId, msgLength, tag, recieverId);

  printf("%d: send content: (", peerId);

  for (int i = 0; i < msgLength; i++)
    printf("%d ", message[i]);

  printf(")\n");

  // TODO add enclosing zero during export (stack, configuration)
  // and remove this extra copying whole array

  int buffer[msgLength + 1];

  for (int i = 0; i < msgLength; i++)
    buffer[i] = message[i];

  buffer[msgLength] = 0;

  MPI_Send (&buffer, msgLength + 1, MPI_INT, recieverId, tag, MPI_COMM_WORLD);
}

void ParallelTask::broadcast(int tag)
{
  for (int i = 0; i < peersCount; i++)
  {
    if (i != peerId)
      this->send(i, tag);
  }
}

void ParallelTask::broadcast(int tag, int message)
{
  for (int i = 0; i < peersCount; i++)
  {
    if (i != peerId)
      this->send(i, tag, message);
  }
}

void ParallelTask::broadcast(int tag, char message)
{
  for (int i = 0; i < peersCount; i++)
  {
    if (i != peerId)
      this->send(i, tag, message);
  }
}

void ParallelTask::broadcast(int tag, int* message, int msgLength)
{
  for (int i = 0; i < peersCount; i++)
  {
    if (i != peerId)
      this->send(i, tag, message, msgLength);
  }
}

void ParallelTask::handleSollutionSteps()
{
  MPI_Status status;
  int buffer;
  MPI_Recv(&buffer, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

  printf("%d: recieved new global sollution (steps: %d)\n", peerId, buffer);

  // received globalBest is better than my current
  if (globalBestConfSteps > buffer || globalBestConfSteps == 0)
  {
    globalBestConfSteps = buffer;

    // check for best possible sollution
    if (this->isMaster() && stopOnBestFound && globalBestConfSteps == initConf->getFiguresCount())
    {
      isFinished = true;
      isActive = false;
      tokenSent = true;
      this->broadcast(MSG_FINISH);
    }
  }
}

bool ParallelTask::checkConfiguration()
{
  if (globalBestConfSteps > 0 && workConf->getStepsCount() >= globalBestConfSteps)
  {
    //printf("%d: work conf has reached globalBest - stop\n", peerId);
    return false;
  }

  if (workConf->final() && (globalBestConfSteps == 0 || globalBestConfSteps > workConf->getStepsCount()))
  {
    printf("%d: new globalBest - broadcast\n", peerId);
    globalBestConfSteps = workConf->getStepsCount();

    // if master finds the best sollution - stop immediately
    if (this->isMaster() && stopOnBestFound && globalBestConfSteps == initConf->getFiguresCount())
    {
      isFinished = true;
      isActive = false;
      tokenSent = true;
      this->broadcast(MSG_FINISH);
    }
    else
    {
      this->broadcast(MSG_SOLLUTION_STEPS, globalBestConfSteps);
    }

  }

  return AbstractTask::checkConfiguration();
}

void ParallelTask::sendWorkRequest()
{
  // this situation should not occur (master does not request)
  // if so, the global behavior is local (global counter is master's local counter)
  if (this->isMaster() && donorAlg == ParallelTask::GLOBAL)
    donorAlg = ParallelTask::LOCAL;

  int lastRequestPeerId = localRequestsCounter;

  switch (donorAlg)
  {
      // send direct request to specific peer
    case ParallelTask::RANDOM:
    case ParallelTask::LOCAL:
      do
      {
        localRequestsCounter = (donorAlg == ParallelTask::RANDOM) ? (rand() % peersCount) : this->getNextPeerId(localRequestsCounter);
      }
      // do not send to self and do not send to last
      while (localRequestsCounter == peerId && (peersCount > 2 && localRequestsCounter == lastRequestPeerId));

      this->send(localRequestsCounter, MSG_WORK_REQUEST);
      break;
      // send request to master
    case ParallelTask::GLOBAL:
      // TODO
      break;
  }

  requestSent = true;

}
