#ifndef PARALLELTASK_H
#define PARALLELTASK_H

#include <mpi.h>
#include "d_split_stack.h"
#include "dr_split_stack.h"
#include "r_split_stack.h"
#include "mpi_constants.h"
#include "abstract_task.h" // Base class: AbstractTask

class ParallelTask : public AbstractTask
{
  public:
    ParallelTask();
    ~ParallelTask();

  protected:
    void initConfiguration(Configuration* init);
    void processConfiguration();
    void releaseMemory();

    AbstractSplitStack* stack;

    bool isActive;
    bool requestSent;
    bool tokenSent;
    int recievedSollutionsCount;
    int localRequestsCounter;

    int peerId;
    int peersCount;

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

    void checkNewMessage();
    void processStack();
    void noWork();

    int getNextPeerId() const;
    int getNextPeerId(int id) const;
    int getNextWorkRequestPeerId();
    void incRecievedSollutions();
    bool isMaster() const;
};

#endif // PARALLELTASK_H
