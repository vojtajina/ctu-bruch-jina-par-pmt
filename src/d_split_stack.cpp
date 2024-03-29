#include "d_split_stack.h"

/**
 * @file d_split_stack.cpp
 * @author Jirka
 * @brief Implementation of the DSplitStack class
 */
 
bool DSplitStack::canSplit(int divider) const
{
  //TODO
  int states = this->data->size();
  int floors = this->getFloorCount();
  float countf = (states - floors) / (double)divider;
  int counti = ceil(countf);

  return (counti >= 1);
}

DSplitStack* DSplitStack::split(int divider)
{
  DSplitStack* s = new DSplitStack(maxSplitDepth);
  int size = this->data->size();
  int floor = 1;
  int statesInFloor = 0;

  // find first floor with not-opened states
  do
  {
    statesInFloor = this->getStatesCountInFloor(floor++);

    // reaches the depth limit - do not split
    if (floor > maxSplitDepth)
      return 0;
  }
  while(statesInFloor == 0);

  // number of possible states to divide
  int countToMove = ceil(statesInFloor / (double)divider);
  int i, j;
  for(i = 0, j = 0; j < countToMove; i++)	//foreach state which is selected to move
  {
    int value = this->data->at(i - j);
    s->push(value);
    if(value > 0 )	//if value is > 0, notopened state must be removed from old stack
    {
      this->data->erase(this->data->begin() + (i - j));
      j++;
    }
  }
  
  if (s->size() > 0)
    return s;
    
  delete s;
  return 0;
}
