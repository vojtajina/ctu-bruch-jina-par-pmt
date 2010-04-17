#include "abstract_split_stack.h"
#include "math.h"

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
 

AbstractSplitStack::AbstractSplitStack()
{
	this->data = new vector<int>();
}
	

AbstractSplitStack::~AbstractSplitStack()
{
	delete(this->data);
}


void AbstractSplitStack::push(int item)
{
	this->data->push_back(item);	
}


int AbstractSplitStack::pop()
{
	int value = this->data->back();
	this->data->pop_back();
	return value;
}

void AbstractSplitStack::turnHead()
{
	int value = -this->data->back();
	this->data->pop_back();
	this->data->push_back(value);
}

int AbstractSplitStack::head()
{
	return this->data->back();	
}

bool AbstractSplitStack::empty() const
{
	return this->data->empty();	
}


int AbstractSplitStack::size() const
{
	return this->data->size();		
}

int* AbstractSplitStack::toArray()
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

string AbstractSplitStack::toString()
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



int AbstractSplitStack::getFloorCount()
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

int AbstractSplitStack::getFloorStartIndex(int floor)
{	
	int size = this->data->size();
	int floorCount = 1;
	int i = 0;
	for(i = 0;i<size;i++)
	{
		if(this->data->at(i) < 0)
			floorCount++;
		if(floorCount == floor)	//this is index of negative number => enterstate
			return i+1;			//so first index of state in floor is enterstate+1
	}
	return 0;
}

int AbstractSplitStack::getStatesCountInFloor(int floor)
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