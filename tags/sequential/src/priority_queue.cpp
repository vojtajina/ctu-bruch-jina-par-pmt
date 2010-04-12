#include "priority_queue.h"

template <typename T>
PriorityQueue<T>::PriorityQueue(int priorityCount)
{
  count = 0;
  queues = new queue<T>[priorityCount];
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
  // queue is empty
  if (empty())
    return NULL;

  int i = -1;
  queue<T>* q;

  // get the first non-empty queue with the highest priority
  do
  {
    i++;
    q = &queues[i];
  }
  while (q->empty());

  // get front item
  // remove it from the queue
  T item = q->front();
  q->pop();
  count--;

  return item;
}

template <typename T>
void PriorityQueue<T>::push(T item, int priority)
{
  queue<T>* q = &queues[priority];
  q->push(item);
  count++;
}

template <typename T>
int PriorityQueue<T>::size() const
{
  return count;
}

// public methods for int
template IntPriQueue::PriorityQueue(int);
template IntPriQueue::~PriorityQueue();
template bool IntPriQueue::empty() const;
template int IntPriQueue::pop();
template void IntPriQueue::push(int, int);
template int IntPriQueue::size() const;