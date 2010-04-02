#include "configuration.h"
#include <iostream>
using namespace std;

Configuration::Configuration(int k, int q, int* F, int K)
{
  fieldLength = k * k;
  sideLength = k;
  figuresPosition = new bool[fieldLength];
  figuresStartPosition = new bool[fieldLength];
  figuresCount = q;
  queenSteps = new int[fieldLength];
  queenStepsCount = 0;

  // add queen start position to queenSteps history
  queenSteps[0] = K;

  // load figure positions
  int a = 0;
  for (int i = 0; i < fieldLength; i++)
  {
    // there is a figure on i position
    if (a < q && F[a] ==i)
    {
      figuresPosition[i] = true;
      figuresStartPosition[i] = true;
    }
    // no figure on i position
    else
    {
      figuresPosition[i] = false;
      figuresStartPosition[i] = false;
    }

    if (F[a]==i)
      a++;
  }
}

Configuration::Configuration(const Configuration& src)
{
  // copy values
  fieldLength = src.fieldLength;
  sideLength = src.sideLength;
  queenStepsCount = src.queenStepsCount;
  figuresCount = src.figuresCount;

  // *figuresPosition - deep copy
  figuresPosition = new bool[fieldLength];
  for (int i = 0; i < fieldLength; i++)
    figuresPosition[i] = src.figuresPosition[i];

  // *queenSteps - deep copy
  queenSteps = new int[fieldLength];
  for (int i = 0; i <= queenStepsCount; i++)
    queenSteps[i] = src.queenSteps[i];

  // *figuresStartPosition - reference to the same memory address (these values never change)
  figuresStartPosition = src.figuresStartPosition;
}

IntPriQueue* Configuration::getAvailablePositions() const
{
  // new queue with two priorities
  // priority 0 = position with figure
  // priority 1 = free position
  IntPriQueue* pq = new PriorityQueue<int>(2);

  this->addAvailableTop(pq);
  this->addAvailableBottom(pq);
  this->addAvailableLeft(pq);
  this->addAvailableRight(pq);
  this->addAvailableLeftTop(pq);
  this->addAvailableRightTop(pq);
  this->addAvailableLeftBottom(pq);
  this->addAvailableRightBottom(pq);

  return pq;
}

bool Configuration::final() const
{
  return (figuresCount == 0);
}

int Configuration::getStepsCount() const
{
  return queenStepsCount;
}

void Configuration::move(int newPosition)
{
  queenStepsCount++;
  queenSteps[queenStepsCount] = newPosition;
  this->removeFigure(newPosition);
}

void Configuration::moveBack()
{
  if (queenStepsCount > 0)
  {
    this->restoreFigure(queenSteps[queenStepsCount]);
    //queenSteps[queenStepsCount] = -1;
    queenStepsCount--;
  }
}

// PRIVATE METHODS
bool Configuration::removeFigure(int position)
{
  // no figure on the position
  if (!figuresPosition[position])
    return false;

  figuresPosition[position] = false;
  figuresCount--;
  return true;
}

bool Configuration::restoreFigure(int position)
{
  // the figure is already on this position
  // or there was no figure on the start
  if (figuresPosition[position] || !figuresStartPosition[position])
    return false;

  figuresPosition[position] = true;
  figuresCount++;
  return true;
}

int Configuration::getQueenPosition() const
{
  return queenSteps[queenStepsCount];
}

void Configuration::addAvailableLeft(IntPriQueue* pq) const
{
  // init
  int queenPos = this->getQueenPosition();
  int y = queenPos - 1;
  int min = queenPos - (queenPos % sideLength);
  int priority = 1;

  while (y >= min && priority == 1)
  {
    priority = this->addAvailablePosition(pq, y);
    y = y - 1;
  }
}

void Configuration::addAvailableRight(IntPriQueue* pq) const
{
  // init
  int queenPos = this->getQueenPosition();
  int y = queenPos + 1;
  int max = queenPos - (queenPos % sideLength) + sideLength;
  int priority = 1;

  while (y < max && priority == 1)
  {
    priority = this->addAvailablePosition(pq, y);
    y = y + 1;
  }

}

void Configuration::addAvailableTop(IntPriQueue* pq) const
{
  // init
  int y = this->getQueenPosition() - sideLength;
  int priority = 1;

  while (y >= 0 && priority == 1)
  {
    priority = this->addAvailablePosition(pq, y);
    y = y - sideLength;
  }
}

void Configuration::addAvailableBottom(IntPriQueue* pq) const
{
  // init first position
  int y = this->getQueenPosition() + sideLength;
  int priority = 1;

  while (y < fieldLength && priority == 1)
  {
    priority = this->addAvailablePosition(pq, y);
    y = y + sideLength;
  }
}

void Configuration::addAvailableLeftTop(IntPriQueue* pq) const
{
  // init first position
  int y = this->getQueenPosition() - sideLength - 1;
  int priority = 1;

  while (y >= 0 && priority == 1)
  {
    priority = this->addAvailablePosition(pq, y);
    y = y - sideLength - 1;
  }
}

void Configuration::addAvailableRightTop(IntPriQueue* pq) const
{
  // init first position
  int y = this->getQueenPosition() - sideLength + 1;
  int priority = 1;

  while (y > 0 && (y % sideLength) > 0 && priority == 1)
  {
    priority = this->addAvailablePosition(pq, y);
    y = y - sideLength + 1;
  }
}

void Configuration::addAvailableLeftBottom(IntPriQueue* pq) const
{
  // init first position
  int y = this->getQueenPosition() + sideLength - 1;
  int priority = 1;

  while (y < fieldLength && ((y + 1) % sideLength) > 0 && priority == 1)
  {
    priority = this->addAvailablePosition(pq, y);
    y = y + sideLength - 1;
  }
}

void Configuration::addAvailableRightBottom(IntPriQueue* pq) const
{
  // init first position
  int y = this->getQueenPosition() + sideLength + 1;
  int priority = 1;

  while (y < fieldLength && priority == 1)
  {
    priority = this->addAvailablePosition(pq, y);
    y = y + sideLength + 1;
  }
}

int Configuration::addAvailablePosition(IntPriQueue* pq, int position) const
{
  // allow to visit each position only once
  if (this->wasPositionVisited(position))
    return -1;

  // determine the priority
  // if there is a figure - priority 0 = high
  // else - there is no figure - priority 1 = low
  int priority = (figuresPosition[position]) ? 0 : 1;

  pq->push(position, priority);
  return priority;
}

bool Configuration::wasPositionVisited(int position) const
{
  for (int i = 0; i<=queenStepsCount; i++)
    if (queenSteps[i] == position)
      return true;

  return false;
}

void Configuration::dump() const
{
  int* steps = new int[fieldLength];
  
  for (int i = 0; i < fieldLength; i++)
    steps[i] = -1;

  for (int i = 0; i <= queenStepsCount; i++)
    steps[queenSteps[i]] = i;

  for (int i = 0; i < fieldLength; i++)
  {
    if (steps[i] < 10 && steps[i] != -1)
      cout << "0" << steps[i];
    else if (steps[i] == -1)
      cout << "--";
    else
      cout << steps[i];
      
    cout << " ";
    
    if ((i+1)%sideLength == 0)
      cout << "\n";
  }
}

int Configuration::getFiguresCount() const
{
  return figuresCount;
}

int Configuration::getSideLength() const
{
  return sideLength;
}
