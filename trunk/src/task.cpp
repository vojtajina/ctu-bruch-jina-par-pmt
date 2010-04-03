#include "task.h"

Task::Task()
{
  Task::Task(false, true);
}

Task::Task(bool stopOnFirstFound, bool stopOnBestFound)
{
  this->stopOnFirstFound = stopOnFirstFound;
  this->stopOnBestFound = stopOnBestFound;
}

Task::~Task()
{
}

Configuration* Task::solve(Configuration* start)
{
  this->initConfiguration(start);
  this->processConfiguration(start);
  delete start;

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
  
  // free the memory
  delete positions;
}

void Task::initConfiguration(const Configuration* conf)
{
  // determine maxSteps
  if (conf->getSideLength() >= conf->getFiguresCount())
    maxSteps = 2 * conf->getFiguresCount();
  else
    maxSteps = (3 * conf->getFiguresCount()) - conf->getSideLength();

  figuresCount = conf->getFiguresCount();
  bestConf = NULL;
  isFinished = false;
}