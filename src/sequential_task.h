#ifndef SEQUENTIALTASK_H
#define SEQUENTIALTASK_H

#include "abstract_task.h" // Base class: AbstractTask

/**
 * @class SequentialTask
 * @author Vojta Jina
 * @date 04/22/2010
 * @file sequential_task.h
 * @brief Sequential sollution algorithm
 * @brief Uses recursion instead of stack
 */
class SequentialTask : public AbstractTask
{
  protected:

    /**
    * @brief The main logic of this algorithm
    */
    void processConfiguration();
};

#endif // SEQUENTIALTASK_H