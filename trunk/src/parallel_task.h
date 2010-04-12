#ifndef PARALLELTASK_H
#define PARALLELTASK_H

#include <mpi.h>

/**
 * @class ParallelTask
 * @author Vojta
 * @date 04/12/10
 * @file parallel_task.h
 * @brief Represents parallel task (contains logic to solve the problem and also communication through MPI)
 *
 * TODO:
 * Refactor the code. The should be abstract class Task and SequentialTask, ParallelTask both inheriting the abstract Task
 * Shared methods and member fields should be inside Task.
 */
class ParallelTask
{

  public:
    ParallelTask();
    ~ParallelTask();

    /**
     * @brief The main business of this algorithm
     * @param start Initial configuration
     * @return Sollution - the best found Configuration
     */
    Configuration* solve(Configuration* start);

  private:
  Configuration* bestConf;
  Configuration* initConf;
  Configuration* workConf;
  
  IntSplitStack* stack;
  int maxSteps;
  bool isFinished;
  
  void checkMessage();
  
  void handleWorkRequest(MPI_Status* status);
  void handleWorkSent(MPI_Status* status);
  void handleWorkNone(MPI_Status* status);
  void handleToken(MPI_Status* status);
  void handleFinish(MPI_Status* status);
  
  void sendWorkRequest(int peer);
  void sendWork(int peer, int* work);
  void sendWorkNone(int peer);
  void sendToken(int peer, bool token);
  void sendFinish();
  void sendFinish(int* sollution);
  
  // run the state machine
  void process();

};

#endif // PARALLELTASK_H
