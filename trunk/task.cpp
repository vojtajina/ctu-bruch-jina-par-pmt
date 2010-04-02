#include "task.h"

Task::Task()
{
  Task::Task(false, true);
}

Task::Task(bool stopOnFirstFound, bool stopOnBestFound)
{
  this->stopOnFirstFound = stopOnFirstFound;
  this->stopOnBestFound = stopOnBestFound;
  isFinished = false;
}

Configuration* Task::solve(Configuration* start)
{
  // determine maxSteps
  if (start->getSideLength() >= start->getFiguresCount())
    maxSteps = 2 * start->getFiguresCount();
  else
    maxSteps = (3 * start->getFiguresCount()) - start->getSideLength();

  figuresCount = start->getFiguresCount();
  bestConf = NULL;
  
  this->processConfiguration(start);

  return bestConf;
}

// PRIVATE MEMBERS
bool Task::checkConfiguration(const Configuration* conf)
{
  // is sollution
  if (conf->final())
  {
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
        // TODO free memory of old bestConf;
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

  return true;
}

void Task::processConfiguration(Configuration* conf)
{
  IntPriQueue* positions = conf->getAvailablePositions();
  int position;

  while (!positions->empty() && !isFinished)
  {
    position = positions->pop();
    conf->move(position);

    if (this->checkConfiguration(conf))
      this->processConfiguration(conf);

    conf->moveBack();
  }
}
