#ifndef PARALLELTASK_H
#define PARALLELTASK_H

#include <mpi.h>
#include "d_split_stack.h"
#include "priority_queue.h"
#include "configuration.h"
#include "mpi_constants.h"

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

  /**
   * @brief Is this peer master ? (process 0 is master)
   * @return True if this MPI peer has id 0, False otherwise
   */
  bool isMaster() const;

private:
  Configuration* bestConf;
  Configuration* initConf;
  Configuration* workConf;

  AbstractSplitStack* stack;
  
  int maxSteps;
  int figuresCount;
  
  bool isFinished;
  bool isActive;
  
  bool requestSent;
  bool tokenSent;
  
  int recievedSollutionsCount;
  
  bool stopOnBestFound;
  bool stopOnFirstFound;
  
  int workRequestPeerCounter;
  
  int peerId;
  int peersCount;

  void checkNewMessage();

  void handleWorkRequest();
  void handleWorkSent();
  void handleWorkNone();
  void handleToken();
  void handleFinish();
  void handleSollution();
  void handleNoSollution();

  void send(int recieverId, int tag);
  void send(int recieverId, int tag, char message);
  void send(int recieverId, int tag, int* message, int msgLength);

  void processStack();
  bool checkConfiguration(const Configuration* conf);
  void noWork();
  int getNextPeerId() const;
  int getNextPeerId(int id) const;
  int getNextWorkRequestPeerId();
  void incRecievedSollutions();

};

#endif // PARALLELTASK_H