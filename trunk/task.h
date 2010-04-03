#ifndef TASK_H
#define TASK_H

#include "configuration.h"
#include "priority_queue.h"

class Task {

  public:

  /**
   * @brief Constructor
   * @param stopOnFirstFound If true - algorithm stops on first sollution found, else search whole space (to find the best sollution)
   * @param stopOnBestFound If true - algorithm stops on best sollution found (number of steps = number of figures on start)
   */
	Task(bool stopOnFirstFound, bool stopOnBestFound);
  
  /**
   * @brief Constructor (stopOnFirstFound set to false)
   */
  Task();
  
  /**
   * @brief Destructor
   */
  ~Task();
  
  /**
   * @brief The main business of this algorithm
   * @param start Initial configuration
   * @return Sollution - the best found Configuration
   */
  Configuration* solve(Configuration* start);
  
  private:
  
  /**
   * @brief Current best found configuration
   */
  Configuration* bestConf;
  
  /**
   * @brief Max allowed steps
   */
  int maxSteps;
  
  /**
   * @brief Number of figures in initial configuration
   * Its used to check whether the found sollution is best possible (stop)
   */
  int figuresCount;
  
  /**
   * @brief If true - algorithm stops on first sollution found, if false - search whole space to find the best sollution
   */
  bool stopOnFirstFound;
  
  /**
   * @brief If true - algorithm stops when find sollution with steps = figures (the best possible)
   */
  bool stopOnBestFound;
  
  /**
   * @brief If true - algorithm is ending - search is stopped
   */
  bool isFinished;
  
  /**
   * @brief Here is the business - this method is called recursively
   * @param conf Configuration that should be expanded
   */
  void processConfiguration(Configuration* conf);
  
  /**
   * @brief After moving, this method check new configuration
   * Check whether the configuration is sollution, whether is better than current best
   * Determine whether stop searching this branch or not
   * @param conf Configuration to check
   * @return 
   */
  bool checkConfiguration(const Configuration* conf);
  
  /**
   * @brief Initialize the task (for new configuration)
   * This method loads some initial variables (maxSteps, figuresCount, bestConf null, etc.)
   * @param conf Initial configuration
   */
  void initConfiguration(const Configuration* conf);
};

#endif // TASK_H
