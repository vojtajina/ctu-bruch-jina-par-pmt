
#include "split_stack.h"

using namespace std;

/*
 * Special implementation of stack (its more than common stack)
 * There has to be possibility to iterate stack items from the bottom (first item)
 * When stack is being splitted, we need to iterate the items and REMOVE some of them !!!
 * 
 * When T is int, we could implement removing items, by setting it to 0
 * -> then, we must change the logic in numbering position - it should start from 1 (instead of 0)
 * -> because of these reasons:
 *    -> its not possible to store information, that position is open, -3 is open 3 position, but there is no -0
 *    -> we want use 0 as removed item from the stack
 * 
 * In the future there will be more algorithms of splitting the stack, we dont have to care about this just now
 */
 

SplitStack::SplitStack()
{
	this->data = new vector<int>();
}
	

SplitStack::~SplitStack()
{
	delete(this->data);
}


void SplitStack::push(int item)
{
	this->data->push_back(item);	
}


int SplitStack::pop()
{
	int value = this->data->back();
	this->data->pop_back();
	return value;
}

void SplitStack::turnHead()
{
	int value = -this->data->back();
	this->data->pop_back();
	this->data->push_back(value);
}

int SplitStack::head()
{
	return this->data->back();	
}

bool SplitStack::empty() const
{
	return this->data->empty();	
}


int SplitStack::size() const
{
	return this->data->size();		
}


bool SplitStack::canSplit(int divider)
{
	int states = this->data->size();
	int floors = this->getFloorCount();
	float countf = (states - floors) / divider;
	int counti = ceil(countf);
	return counti > 1;		
}


int* SplitStack::toArray()
{
	int size =this->data->size();
	int *iArray = new int[size];	
	int i;

	for(i = 0;i<size;i++)
	{
		iArray[i] = this->data->at(i);
	}
	return iArray;
}


SplitStack* SplitStack::splitToStack(int divider)
{
	SplitStack* s = new SplitStack();
	int size = this->data->size();
	int floor = 1;
	int statesInFloor = 0;
	do			//find first floor with notopened states
	{
		statesInFloor = this->getStatesCountInFloor(floor++);
	}
	while(statesInFloor == 0);
	
	int countToMove = ceil(statesInFloor / (double)divider); //number of possible states to divide
	//if(countToMove <= statesInFloor)		//count states in current floor is enough to divide
	{	
		int i,j;
		for(i = 0,j = 0;j < countToMove; i++)	//foreach state which is selected to move
		{
			int value = this->data->at(i-j);
			if(value < 0 )							//if value is < 0, state is opened and must be copied into new stack			
			{	s->push(value);			}
			else							//else move this state into new stack
			{	
				s->push(value);
				this->data->erase(this->data->begin() + (i - j));
				j++;
			}
		}
	}

	return s;
}

string SplitStack::toString()
{	
	stringstream ss;
	int size = this->data->size();
	int i;
	for(i = 0;i<size;i++)
	{
		ss << this->data->at(i) << " ";			
	}
	return ss.str();
	
}



int SplitStack::getFloorCount()
{	
	int size = this->data->size();
	int floorCount = 1;
	int i = 0;
	for(i = 0;i<size;i++)
	{
		if(this->data->at(i) < 0)
			floorCount++;
	}
	return floorCount;
}

int SplitStack::getStatesCountInFloor(int floor)
{	
	int size = this->data->size();
	int floorCount = 0;
	int stateCount = 0;
	int i = 0;
	for(i = 0;i<size;i++) //foreach state
	{
		if(this->data->at(i) < 0)		 //if head is negative (opened state)
		{
			floorCount++;				//its mean new floor
			if(floor == floorCount)		//if new floor became i have stateCount what i want
				break;			
			stateCount = 0;				//and statecount is 0
		}
		else							//otherwise its state in floor
			stateCount++;				
	}
	return stateCount;
}