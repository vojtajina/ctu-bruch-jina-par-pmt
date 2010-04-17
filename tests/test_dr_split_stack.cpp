#include <UnitTest++.h>


#include "../src/dr_split_stack.h"

DRSplitStack* GetDRStack()
{
	DRSplitStack *drs = new DRSplitStack();
	drs->push(1);
	drs->push(2);drs->turnHead();
	
	drs->push(3);drs->push(4);drs->push(5);drs->push(6);drs->push(7);
	drs->push(8);drs->turnHead();
	
	drs->push(9);drs->push(10);drs->push(11);drs->push(12);drs->push(13);drs->push(14);
	drs->push(15);drs->turnHead();
	//state =  1 -2 3 4 5 6 7 -8 9 10 11 12 13 14 -15
	return drs;
}
//DRSplitStack.canSplit()
TEST(TestDDRSplitStack_canSplit)
{
	//TODO
}

//DRSplitStack.split()
TEST(TestDDRSplitStack_split)
{
	int value = 0;
	
	DRSplitStack *drs = GetDRStack();
	DRSplitStack *drs2 = drs->split(2);
	
	
	//fidrst divide	
	CHECK(drs2->size() == 9);	
	int *array = drs2->toArray();
	CHECK(array[0] == 1);
	CHECK(array[1] == -2);
	CHECK(array[2] == 3);
	CHECK(array[3] == 4);
	CHECK(array[4] == 5);
	CHECK(array[5] == -8);	
	value = drs2->pop();	
	CHECK(value == 11);
	delete(drs2);
	
	array = drs->toArray();
	CHECK(array[0] == -2);
	CHECK(array[1] == 6);
	CHECK(array[2] == 7);
	CHECK(array[3] == -8);
	CHECK(array[4] == 12);
	CHECK(array[5] == 13);	
	CHECK(array[6] == 14);	
	CHECK(array[7] == -15);	
	
	
	//second divide
	DRSplitStack *drs3 = drs->split(2);
	array = drs3->toArray();
	CHECK(drs3->size() == 5);	
	CHECK(array[0] == -2);
	CHECK(array[1] == 6);
	CHECK(array[2] == -8);	
	CHECK(array[3] == 12);	
	CHECK(array[4] == 13);	

	delete(drs3);

	array = drs->toArray();
	CHECK(array[0] == -2);
	CHECK(array[1] == 7);
	CHECK(array[2] == -8);	
	CHECK(array[3] == 14);	
	CHECK(array[4] == -15);	
	
	delete(drs);
	delete(array);
	
}
