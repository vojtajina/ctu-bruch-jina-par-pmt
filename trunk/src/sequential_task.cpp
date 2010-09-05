#include "sequential_task.h"

/**
 * @file sequential_task.cpp
 * @author Vojta Jina
 * @brief Implementation of the SequentialTask class
 */
 
Configuration* SequentialTask::solve(Configuration* init)
{
  this->initConfiguration(init);
  
  clock_t startClock = clock();
  this->processConfiguration();
  clock_t endClock = clock();
  elapsedTime = (double)(endClock - startClock) / CLOCKS_PER_SEC * 1000;
  
  this->releaseMemory();

  return bestConf;
}

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