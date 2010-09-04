#ifndef PARALLELTASK_H
#define PARALLELTASK_H

#include <mpi.h>
#include <cstdlib>
#include "math.h"
#include "d_split_stack.h"
#include "dr_split_stack.h"
#include "r_split_stack.h"
#include "mpi_constants.h"
#include "abstract_task.h" // Base class: AbstractTask

/**
 * @class ParallelTask
 * @author Vojta Jina
 * @date 04/22/2010
 * @file parallel_task.h
 * @brief Parallel sollution algorithm - uses MPI
 */
class ParallelTask : public AbstractTask
{
  public:

    /**
     * @brief Default constructor (init MPI)
     */
    ParallelTask();

    /**
     * @brief Default destructor (closes MPI)
     */
    ~ParallelTask();
    
    /**
     * @brief Enum of possible select donor algorithms
     */
    enum SelectDonorAlgorithm { LOCAL, GLOBAL, RANDOM };
    
    int getPeerId() const;

  protected:

    /**
     * @brief Initialise all requirements
     * @brief Master expand the init configuration and divide the stack to all peers
     * @param init Initial configuration
     */
    void initConfiguration(Configuration* init);

    /**
     * @brief The core logic of the process (state machine)
     */
    void processConfiguration();
    
    /**
     * @brief Checks working configuration, whether it is a sollution, determine end of the algorithm
     * @return True if configuration should be expanded, False otherwise
     */
    bool checkConfiguration();

    /**
     * @brief Release dynamic allocated memory
     */
    void releaseMemory();

    /**
    * @brief Stack used for DFS
    */
    AbstractSplitStack* stack;

    /**
    * @brief Whether this peer is still active in the MPI communication (can be finished, but still active)
    */
    bool isActive;
    
    /**
     * @brief Algorithm, that will be used for requesting work
     * @brief Default is LOCAL counter
     */
    SelectDonorAlgorithm donorAlg;

    /**
    * @brief Whether request for work has been sent
    * @brief [not used by master]
    */
    bool requestSent;

    /**
    * @brief Whether finishing token has beenn sent
    * @brief [used only by master]
    */
    bool tokenSent;

    /**
    * @brief Number of received sollutions (master must wait for all peers)
    * @brief [used only by master]
    */
    int recievedSollutionsCount;

    /**
    * @brief Local counter to determine peer to ask for some work
    */
    int localRequestsCounter;

    /**
    * @brief MPI ID of this peer
    */
    int peerId;
    
    /**
    * @brief Number of peers in the MPI network
    */
    int peersCount;

    /**
     * @brief Handles MSG_WORK_REQUEST received
     * @brief Reply some work or MSG_WORK_NOWORK
     */
    void handleWorkRequest();
    
    /**
     * @brief Handles MSG_WORK_REQ_INDIRECT received
     * @brief Master can receive msg from requester (without any data
     */
    void handleWorkRequestIndirect();
    
    /**
    * @brief Handles MSG_WORK_SENT received
    * @brief Add received work to local stack
    */
    void handleWorkSent();
    
    /**
    * @brief Handles MSG_WORK_NOWORK received
    * @brief Ask someone else
    * @brief Master does not ask for work and sends finish token
    */
    void handleWorkNone();
    
    /**
    * @brief Handles MSG_TOKEN received
    * @brief If this peer is not finished with the work, change to TOKEN_BLACK
    * @brief And sends the token to next peer
    */
    void handleToken();
    
    /**
    * @brief Handles MSG_FINISH received
    * @brief Sends the best local sollution (to master) or MSG_NO_SOLLUTION
    */
    void handleFinish();
    
    /**
    * @brief Handles MSG_SOLLUTION received
    * @brief Compare the sollution with the best local sollution
    * @brief [used only by master]
    */
    void handleSollution();
    
    /**
    * @brief Handles MSG_NO_SOLLUTION received
    * @brief [used only by master]
    */
    void handleNoSollution();
    
    /**
     * @brief Handles MSG_SOLLUTION_STEPS received
     * @brief This message contains new global sollution (current best)
     */
    void handleSollutionSteps();

    /**
     * @brief Sends message without any content
     * @param recieverId Id of the receiver
     * @param tag Tag of the message
     */
    void send(int recieverId, int tag);
    
    /**
     * @brief Sends message with one integer
     * @param recieverId Id of the receiver
     * @param tag Tag of the message
     * @param message The content of the message
     */
    void send(int recieverId, int tag, int message);
    
    /**
     * @brief Sends message with one character
     * @param recieverId Id of the receiver
     * @param tag Tag of the message
     * @param message The content of the message
     */
    void send(int recieverId, int tag, char message);
    
    /**
     * @brief Sends message with array of integers
     * @param recieverId Id of the receiver
     * @param tag Tag of the message
     * @param message Pointer to array of integers, that should be sent
     * @param msgLength Size of the content array
     */
    void send(int recieverId, int tag, int* message, int msgLength);

    /**
     * @brief Sends message without any content to all peers
     * @see ParallelTask::send(int recieverId, int tag)
     * @param tag Tag of the message
     */
    void broadcast(int tag);
    
    /**
     * @brief Sends message with one integer to all peers
     * @see ParallelTask::send(int recieverId, int tag, int message)
     * @param tag Tag of the message
     * @param message The content of the message
     */
    void broadcast(int tag, int message);
    
    /**
     * @brief Sends message with one character to all peers
     * @see ParallelTask::send(int recieverId, int tag, char message)
     * @param tag Tag of the message
     * @param message The content of the message
     */
    void broadcast(int tag, char message);
    
    /**
     * @brief Sends message with array of integers to all peers
     * @see ParallelTask::send(int recieverId, int tag, int* message, int msgLength);
     * @param tag Tag of the message
     * @param message Pointer to array of integers, that should be sent
     * @param msgLength Size of the content array
     */
    void broadcast(int tag, int* message, int msgLength);
    
    /**
     * @brief Send request for work - with selected algorithm
     * @brief The algorithm is set in donorAlg member
     */
    void sendWorkRequest();
    
    /**
     * @brief Check stack and send MSG_WORK_SENT or MSG_WORK_NOWORK
     * @param recieverId Id of the receiver
     */
    void sendWork(int recieverId);
    
    /**
     * @brief Check whether there is a new message
     */
    void checkNewMessage();
    
    /**
    * @brief Check whether the stack contains something and process it
    */
    void processStack();
    
    /**
    * @brief There is no work
    * @brief If request was not send yet, send it, else do nothing
    */
    void noWork();

    /**
    * @brief Counts id of the next peer
    * @return Id of the next peer
    */
    int getNextPeerId() const;
    
    /**
    * @brief Counts id of the next peer (from specific peer)
    * @param id Id of the specific peer
    * @return Id of the next peer
    */
    int getNextPeerId(int id) const;
    
    /**
    * @brief Increment sollutions counter and check whether it was the last
    * @brief [used only by master]
    */
    void incRecievedSollutions();
    
    /**
    * @brief Is this peer master
    * @return True if this peer is master
    */
    bool isMaster() const;
    
    /**
     * @brief The best sollution (across all peers)
     * @brief It's not whole configuration object (only number of its steps)
     * @brief When peer finds better Configuration than this number, broadcast the new value to all peers
     */
    int globalBestConfSteps;
    
    /**
     * @brief Start time (after the work is divided)
     * @brief [used only by master]
     */
    double startTime;
};

#endif // PARALLELTASK_H