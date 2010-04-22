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
class AbstractTask
{

  public:
    /**
     * @brief Default constructor (stopOnFirst = false, stopOnBest = true)
     */
    AbstractTask();

    /**
     * @brief Constructor with task parameters
     * @param stopOnFirst Whether algorithm should stop on any first sollution
     * @param stopOnBest Whether algorithm should stop on the best sollution
     */
    AbstractTask(bool stopOnFirst, bool stopOnBest);

    /**
     * @brief Default destructor
     */
    virtual ~AbstractTask();

    /**
     * @brief Entry point of the whole algorithm
     * @param init Initial configuration, that should be solved
     * @return The best found sollution
     */
    virtual Configuration* solve(Configuration* init);

  protected:
    /**
     * @brief The best sollution (Configuration), null if no sollution found yet
     */
    Configuration* bestConf;

    /**
     * @brief Initial Configuration (constant - this object will not change during the process)
     */
    Configuration* initConf;

    /**
     * @brief Current working configuration
     */
    Configuration* workConf;

    /**
     * @brief Init the process
     * @param init Initial configuration
     */
    virtual void initConfiguration(Configuration* init);

    /**
     * @brief Pure abstract method - core of the algorithm (should be rewritten in concrete class)
     */
    virtual void processConfiguration() = 0;

    /**
     * @brief Checks working configuration, whether it is a sollution, determine end of the algorithm
     * @return True if configuration should be expanded, False otherwise
     */
    virtual bool checkConfiguration();

    /**
     * @brief Release all dynamic allocated memory
     */
    virtual void releaseMemory();

    /**
     * @brief Whether the algorithm should stop on any first sollution
     */
    bool stopOnFirstFound;

    /**
     * @brief Whether the algorithm should stop when best sollution (each step removes a figure) is found
     */
    bool stopOnBestFound;

    /**
     * @brief The number of the worst possible sollution (when this number is reached, configuration expanding stops)
     */
    int maxSteps;

    /**
     * @brief Whether the algorithm is still working
     */
    bool isFinished;
};

#endif // ABSTRACTTASK_H
