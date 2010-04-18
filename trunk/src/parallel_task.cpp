#include "parallel_task.h"

ParallelTask::ParallelTask()
{
  // init MPI
  MPI_Init (0, 0);
  MPI_Comm_rank (MPI_COMM_WORLD, &peerId);
  MPI_Comm_size (MPI_COMM_WORLD, &peersCount);
  workRequestPeerCounter = peerId;
}

ParallelTask::~ParallelTask()
{
  MPI_Finalize();
}

Configuration* ParallelTask::solve (Configuration* start)
{
  // init
  if (start->getSideLength() >= start->getFiguresCount() )
    maxSteps = 2 * start->getFiguresCount();
  else
    maxSteps = (3 * start->getFiguresCount() ) - start->getSideLength();

  figuresCount = start->getFiguresCount();

  isFinished = false;

  bestConf = NULL;

  isActive = true;

  initConf = start;

  workConf = new Configuration (*start);

  requestSent = false;

  tokenSent = false;

  recievedSollutionsCount = 0;

  stopOnBestFound = false;

  stopOnFirstFound = false;

  stack = new DSplitStack();

  if (this->isMaster() )
  {
    IntPriQueue* positions = start->getAvailablePositions();

    printf("%d: init positions(%d)\n", peerId, positions->size());

    while (!positions->empty() )
      stack->push (positions->reversePop() );

    this->checkNewMessage();
  }

  // state machine
  while (isActive)
  {
    this->processStack();
    this->noWork();
    this->checkNewMessage();
  }

  //printf ("Task %d of %d\n", peerId, peersCount);

  // release memory
  delete initConf;

  delete workConf;

  delete stack;

  return bestConf;
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

int ParallelTask::getNextWorkRequestPeerId()
{
  // workRequestPeerCounter is local counter
  // skip myself
  do
  {
    workRequestPeerCounter = this->getNextPeerId(workRequestPeerCounter);
  }
  while (workRequestPeerCounter == peerId);

  return workRequestPeerCounter;
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

      if (this->checkConfiguration(workConf))
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

bool ParallelTask::checkConfiguration(const Configuration* conf)
{
  // is sollution
  if (conf->final())
  {
    printf("%d: SOLLUTION (%d)\n", peerId, conf->getStepsCount());

    // current best is empty - this is first sollution

    if (!bestConf)
    {
      bestConf = new Configuration(*conf);

      // best sollution found

      if (stopOnBestFound && bestConf->getStepsCount() == figuresCount)
        isFinished = true;

      // stop whole algorithm
      if (stopOnFirstFound)
        isFinished = true;
    }

    // its not first sollution
    else
    {
      // its better than current best
      if (bestConf->getStepsCount() > conf->getStepsCount())
      {
        // free the memory (delete the old best)
        delete bestConf;

        bestConf = new Configuration(*conf);

        // best sollution found

        if (stopOnBestFound && bestConf->getStepsCount() == figuresCount)
          isFinished = true;
      }
    }

    // stop expanding this branch
    return false;
  }

  // reach max steps - stop expanding
  if (conf->getStepsCount() >= maxSteps)
    return false;

  // reach current bestConf steps - stop expanding
  if (bestConf && (conf->getStepsCount() >= bestConf->getStepsCount()))
    return false;

  return true;
}

void ParallelTask::noWork()
{
  printf("%d: no work\n", peerId);

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
    {
      this->send(this->getNextWorkRequestPeerId(), MSG_WORK_REQUEST);
      requestSent = true;
    }
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
      for (int i = 1; i < peersCount; i++)
        this->send(i, MSG_FINISH);
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

    this->send(this->getNextPeerId(), MSG_TOKEN, token);
  }
}

void ParallelTask::handleWorkNone ()
{
  MPI_Status status;
  MPI_Recv(0, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

  printf("%d: no work\n", peerId);

  // send new request
  this->send(this->getNextWorkRequestPeerId(), MSG_WORK_REQUEST);
}

void ParallelTask::handleWorkRequest ()
{
  MPI_Status status;
  MPI_Recv(0, 0, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

  printf("%d: recieved work request\n", peerId);
  // i can split the stack
  // so i have some work for the sender

  if (stack->canSplit())
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
      workConf->move(buffer[i]);

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
