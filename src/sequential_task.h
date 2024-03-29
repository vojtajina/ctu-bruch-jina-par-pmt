#ifndef SEQUENTIALTASK_H
#define SEQUENTIALTASK_H

/**
 * @file sequential_task.h
 * @brief Definition of the SequentialTask class
 */
 
#include "abstract_task.h" // Base class: AbstractTask
#include <ctime>

/**
 * @class SequentialTask
 * @author Vojta Jina
 * @date 04/22/2010
 * @brief Sequential sollution algorithm
 * @brief Uses recursion instead of stack
 */
class SequentialTask : public AbstractTask
{
  public:

    /**
     * @brief Added elapsed time counting
     */
    virtual Configuration* solve(Configuration* init);
    
  protected:

    /**
    * @brief The main logic of this algorithm
    */
    void processConfiguration();
};

#endif // SEQUENTIALTASK_H