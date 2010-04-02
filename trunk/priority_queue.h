#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <queue>
using namespace std;

/**
 * @class PriorityQueue
 * @author Vojta
 * @date 04/01/10
 * @file priority_queue.h
 * @brief Different implementation of priority queue than std::priority_queue.
 * This queue contains an array of queues, instead of applying sorting algorithms.
 */
template <typename T>
class PriorityQueue
{
  private:
    int count;
    queue<T>* queues;

  public:

    /**
     * @brief Constructor
     * @param Number of allowed
     */
    PriorityQueue(int priorityCount);

    /**
     * @brief Add item to the queue
     * @param Item
     * @param Priority of the item
     */
    void push(T item, int priority);

    /**
     * @brief Return the first item in FIFO queue and remove this item
     * @return Item
     */
    T pop();

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