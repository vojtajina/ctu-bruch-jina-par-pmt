#include "abstract_task.h"

AbstractTask::AbstractTask()
{
  stopOnFirstFound = false;
  stopOnBestFound = true;
}

AbstractTask::AbstractTask(bool stopOnFirst, bool stopOnBest)
{
  stopOnFirstFound = stopOnFirst;
  stopOnBestFound = stopOnBest;
}

AbstractTask::~AbstractTask()
{}

bool AbstractTask::checkConfiguration()
{
  // is sollution
  if (workConf->final())
  {
    // current best is empty - this is first sollution
    if (!bestConf)
    {
      bestConf = new Configuration(*workConf);

      // best sollution found

      if (stopOnBestFound && bestConf->getStepsCount() == initConf->getFiguresCount())
        isFinished = true;

      // stop whole algorithm
      if (stopOnFirstFound)
        isFinished = true;
    }
    // its not first sollution
    else
    {
      // its better than current best
      if (bestConf->getStepsCount() > workConf->getStepsCount())
      {
        // free the memory (delete the old best)
        delete bestConf;

        bestConf = new Configuration(*workConf);

        // best sollution found

        if (stopOnBestFound && bestConf->getStepsCount() == initConf->getFiguresCount())
          isFinished = true;
      }
    }

    // stop expanding this branch
    return false;
  }

  // reach max steps - stop expanding
  if (workConf->getStepsCount() >= maxSteps)
    return false;

  // reach current bestConf steps - stop expanding
  if (bestConf && (workConf->getStepsCount() >= bestConf->getStepsCount()))
    return false;

  return true;
}

void AbstractTask::initConfiguration(Configuration* init)
{
  initConf = new Configuration(*init);
  workConf = init;
  bestConf = 0;
  elapsedTime = 0;

  // determine maxSteps = the worst sollution
  if (init->getSideLength() >= init->getFiguresCount() )
    maxSteps = 2 * init->getFiguresCount();
  else
    maxSteps = (3 * init->getFiguresCount() ) - init->getSideLength();


  isFinished = false;
}

void AbstractTask::releaseMemory()
{
  delete workConf;
  delete initConf;
}

Configuration* AbstractTask::solve(Configuration* init)
{
  this->initConfiguration(init);
  this->processConfiguration();
  this->releaseMemory();

  return bestConf;
}

double AbstractTask::getTime()
{
  return elapsedTime;
}

