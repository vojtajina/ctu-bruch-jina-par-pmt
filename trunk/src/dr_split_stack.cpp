#include "dr_split_stack.h"

bool DRSplitStack::canSplit(int divider) const
{
  int states = this->data->size();
  int floors = this->getFloorCount();
  float countf = (states - floors) / divider;
  int counti = ceil(countf);
  return counti > 1;
}

DRSplitStack* DRSplitStack::split(int divider)
{
  DRSplitStack* s = new DRSplitStack(maxSplitDepth);
  int size = this->data->size();

  int i = 0;
  int floor = 1;
  int floors = this->getFloorCount();
  while(i<size && floor <= floors)
  {
    int statesInFloor = this->getStatesCountInFloor(floor);
    int countToMove = ceil(statesInFloor / (double)divider); //number of possible states to divide
    if(countToMove <= statesInFloor)		//count states in current floor is enough to divide
    {
      int j;
      for(j = 0; j < countToMove; i++)	//foreach state which is selected to move
      {
        int value = this->data->at(i);
        s->push(value);	//insert state into new one stack
        if(value > 0 )	//if value is > 0, notopened state must be removed from old stack
        {
          this->data->erase(this->data->begin() + i); //remove state from current stack
          j++; //new stack was moved
          i--; //number of states in current stack was lowered by 1
        }
      }
    }
    size = this->size();	//get new size of current stack
    while(i<size && this->data->at(i) > 0 )
    {
      i++; //loop until find new openstate
    }
    floor++; //finished floor and go into new one
  }
  return s;
}
