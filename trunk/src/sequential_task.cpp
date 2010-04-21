#include "sequential_task.h"

void SequentialTask::processConfiguration()
{
  IntPriQueue* positions = workConf->getAvailablePositions();
  int position;

  while (!positions->empty() && !isFinished)
  {
    position = positions->pop();
    workConf->move(position);

    if (this->checkConfiguration())
      this->processConfiguration();

    workConf->moveBack();
  }
  
  // free the memory
  delete positions;
}