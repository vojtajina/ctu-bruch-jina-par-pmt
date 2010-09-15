#include "r_split_stack.h"

/**
 * @file r_split_stack.cpp
 * @author Jirka
 * @brief Implementation of the RSplitStack class
 */
 
bool RSplitStack::canSplit(int divider) const
{
  //TODO
  int states = this->data->size();
  int floors = this->getFloorCount();
  float countf = (states - floors) / divider;
  int counti = ceil(countf);
  return counti > 1;
}

RSplitStack* RSplitStack::split(int divider)
{
  RSplitStack* s = new RSplitStack(maxSplitDepth);
  int size = this->data->size();
  int floor = this->getFloorCount();
  int statesInFloor = this->getStatesCountInFloor(floor);
  while(statesInFloor == 0 && floor > 0)	//get some floor with notopened states
  {
    statesInFloor = this->getStatesCountInFloor(--floor);
  }

  int i,j;

  for(i = 0,j = 1; i < size && j < floor; i++)	//opened state (route from root) must be copied into new stack
  {
    int value = this->data->at(i);
    if(value < 0)
    {
      s->push(value);
      j++;
    }
  }

  int startFloorIndex = this->getFloorStartIndex(floor);
  int countToMove = ceil(statesInFloor / (double)divider) -1; //number of possible states to divide

  for(i = startFloorIndex,j = 0; j < countToMove; i++)	//foreach state which is selected to move
  {
    int value = this->data->at(i-j);
    s->push(value);
    if(value > 0 )	//if value is > 0, state must be removed from old stack
    {
      this->data->erase(this->data->begin() + (i - j));
      j++;
    }
  }
  return s;
}
