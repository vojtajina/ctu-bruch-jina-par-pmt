#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

/**
 * @file priority_queue.h
 * @brief Definition of the PriorityQueue class
 */
 
#include "exceptions.h"
#include <queue>
using namespace std;

/**
 * @class PriorityQueue
 * @author Vojta
 * @date 04/01/10
 * @brief Different implementation of priority queue than std::priority_queue.
 * @brief This queue contains an array of queues, instead of applying sorting algorithms.
 */
template <typename T>
class PriorityQueue
{
  private:
    int count;
    int priorityCount;
    queue<T>* queues;
    T pop(bool reverse);

  public:

    /**
     * @brief Constructor
     * @param priorityCount Number of allowed priorities
     */
    PriorityQueue(int priorityCount);
    
    /**
     * @brief Destructor
     */
    ~PriorityQueue();

    /**
     * @brief Add item to the queue
     * @param item Added item
     * @param priority Priority of the item
     */
    void push(T item, int priority);

    /**
     * @brief Return the first item in FIFO queue and remove this item
     * @return Item
     */
    T pop();
    
    /**
     * @brief Return the the lowest priority at first (order of items of same priority is same as in pop())
     * @return Item
     */
    T reversePop();

    /**
     * @brief Is the queue empty ?
     * @return True if the queue is empty, False otherwise
     */
    bool empty() const;
    
    /**
     * @brief Number of items in the queue
     * @return Number of items in the queue
     */
    int size() const;
};

// register typename for PriorityQueue<int>
typedef PriorityQueue<int> IntPriQueue;

#endif // PRIORITYQUEUE_H