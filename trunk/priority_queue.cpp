#include "priority_queue.h"

template <typename T>
PriorityQueue<T>::PriorityQueue(int priorityCount)
{
  this->count = 0;
  this->queues = new queue<T>[priorityCount];
}

template <typename T>
bool PriorityQueue<T>::empty() const
{
  return (this->count == 0);
}

template <typename T>
T PriorityQueue<T>::pop()
{
  // queue is empty
  if (this->empty())
    return NULL;

  int i = -1;
  queue<T>* q;

  // get the first non-empty queue with the highest priority
  do
  {
    i++;
    q = &this->queues[i];
  }
  while (q->empty());

  // get front item
  // remove it from the queue
  T item = q->front();
  q->pop();
  this->count--;

  return item;
}

template <typename T>
void PriorityQueue<T>::push(T item, int priority)
{
  queue<T>* q = &this->queues[priority];
  q->push(item);
  this->count++;
}

template <typename T>
int PriorityQueue<T>::size() const
{
  return this->count;
}

// public methods for int
template IntPriQueue::PriorityQueue(int);
template bool IntPriQueue::empty() const;
template int IntPriQueue::pop();
template void IntPriQueue::push(int, int);
template int IntPriQueue::size() const;