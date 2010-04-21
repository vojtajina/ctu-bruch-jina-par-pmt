#ifndef ABSTRACTTASK_H
#define ABSTRACTTASK_H

#include "configuration.h"
#include "priority_queue.h"
#include "exceptions.h"

/**
 * @class AbstractTask
 * @author Vojta Jina
 * @date 04/21/2010
 * @file abstract_task.h
 * @brief Provides interface for handling all tasks and some shared logic
 */
class AbstractTask {

public:
	AbstractTask();
  AbstractTask(bool stopOnFirst, bool stopOnBest);
  virtual ~AbstractTask();
  virtual Configuration* solve(Configuration* init);
  
protected:
  Configuration* bestConf;
  Configuration* initConf;
  Configuration* workConf;
  
  virtual void initConfiguration(Configuration* init);
  virtual void processConfiguration() = 0;
  virtual bool checkConfiguration();
  virtual void releaseMemory();
  
  bool stopOnFirstFound;
  bool stopOnBestFound;
  
  int maxSteps;
  bool isFinished;
};

#endif // ABSTRACTTASK_H