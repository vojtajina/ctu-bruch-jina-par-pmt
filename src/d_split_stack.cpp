#include "d_split_stack.h"

bool DSplitStack::canSplit(int divider) const
{
	//TODO 
	int states = this->data->size();
	int floors = this->getFloorCount();
	float countf = (states - floors) / divider;
	int counti = ceil(countf);
  
	return (counti > 1);
}

DSplitStack* DSplitStack::split(int divider)
{	
	DSplitStack* s = new DSplitStack();
	int size = this->data->size();
	int floor = 1;
	int statesInFloor = 0;
	do			//find first floor with notopened states
	{
		statesInFloor = this->getStatesCountInFloor(floor++);
	}
	while(statesInFloor == 0);
	
	int countToMove = ceil(statesInFloor / (double)divider); //number of possible states to divide	
	int i,j;
	for(i = 0,j = 0;j < countToMove; i++)	//foreach state which is selected to move
	{
		int value = this->data->at(i-j);
		s->push(value);	
		if(value > 0 )	//if value is > 0, notopened state must be removed from old stack
		{	
			this->data->erase(this->data->begin() + (i - j));
			j++;
		}
	}
	return s;
}

