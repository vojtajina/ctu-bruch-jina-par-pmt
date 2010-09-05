#include "priority_queue.h"

/**
 * @file priority_queue.cpp
 * @author Vojta Jina
 * @brief Implementation of the PriorityQueue class
 */
 
template <typename T>
PriorityQueue<T>::PriorityQueue(int priorityCount)
{
  this->priorityCount = priorityCount;
  queues = new queue<T>[priorityCount];
  count = 0;
}

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
  delete[] queues;
}

template <typename T>
bool PriorityQueue<T>::empty() const
{
  return (count == 0);
}

template <typename T>
T PriorityQueue<T>::pop()
{
  return PriorityQueue<T>::pop(false);
}

template <typename T>
T PriorityQueue<T>::reversePop()
{
  return PriorityQueue<T>::pop(true);
}

template <typename T>
void PriorityQueue<T>::push(T item, int priority)
{
  if (priority < 0 || priority > (priorityCount - 1))
    throw InvalidPriorityException(priority);

  queue<T>* q = &queues[priority];
  q->push(item);
  count++;
}

template <typename T>
int PriorityQueue<T>::size() const
{
  return count;
}

// private
template <typename T>
T PriorityQueue<T>::pop(bool reverse)
{
  // queue is empty
  if (empty())
    return NULL;

  int i = reverse ? priorityCount : -1;
  bool last;
  queue<T>* q;

  // get the first non-empty queue with the highest priority
  do {
    i = reverse ? i - 1 : i + 1;
    q = &queues[i];
    last = reverse ? (i == 0) : (i == priorityCount - 1);
  } while (q->empty() && !last);

  // get front item
  // remove it from the queue
  T item = q->front();
  q->pop();
  count--;

  return item;
}

// public methods for int
template IntPriQueue::PriorityQueue(int);
template IntPriQueue::~PriorityQueue();
template bool IntPriQueue::empty() const;
template int IntPriQueue::pop();
template int IntPriQueue::reversePop();
template void IntPriQueue::push(int, int);
template int IntPriQueue::size() const;
