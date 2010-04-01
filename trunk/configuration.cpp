#include "configuration.h"

Configuration::Configuration()
{
  this->isFinal = false;
  this->figuresPosition = new int[2];
  this->figuresCount = 0;
  this->queenSteps = new int[2];
  this->queenStepsCount = 0;
  this->queenPosition = 0;
}

IntPriQueue* Configuration::getAvailablePositions() const
{
  // new queue with two priorities
  // priority 0 = position with figure
  // priority 1 = free position
  IntPriQueue* pq = new PriorityQueue<int>(2);
  pq->push(1, 0);

  return pq;
}

bool Configuration::getIsFinal() const
{
}

int Configuration::getStepsCount() const
{
}

void Configuration::move(int newPosition)
{
}

void Configuration::moveBack()
{
}
