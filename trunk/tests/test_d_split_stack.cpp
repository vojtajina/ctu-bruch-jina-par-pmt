#include <UnitTest++.h>


#include "../src/d_split_stack.h"


DSplitStack* GetDStack()
{
	DSplitStack *ds = new DSplitStack();
	ds->push(1);ds->push(2);
	ds->turnHead();
	ds->push(3);ds->push(4);ds->push(5);ds->push(6);ds->push(7);ds->push(8);
	ds->turnHead();
	ds->push(9);ds->push(10);ds->push(11);ds->push(12);ds->push(13);ds->push(14);ds->push(15);
	ds->turnHead();
	//state =  1 -2 3 4 5 6 7 -8 9 10 11 12 13 14 -15
	return ds;
}

//DSplitStack.canSplit()
TEST(TestDSplitStack_canSplit)
{
	//TODO
}

//DSplitStack.split()
TEST(TestDSplitStack_split)
{
	
	int value = 0;
	
	DSplitStack *ds = GetDStack();
	DSplitStack *ds2 = ds->split(2);
	
	
	//first divide
	CHECK(ds2->size() == 1);
	value = ds2->pop();	
	CHECK(value == 1);
	delete(ds2);
	
	int *array = ds->toArray();
	CHECK(array[0] == -2);
	CHECK(array[1] == 3);
	CHECK(array[2] == 4);
	
	
	//second divide
	DSplitStack *ds3 = ds->split(2);
	array = ds3->toArray();
	CHECK(ds3->size() == 4);	
	CHECK(array[0] == -2);
	CHECK(array[1] == 3);
	CHECK(array[2] == 4);	
	CHECK(array[3] == 5);	
	delete(ds3);

	array = ds->toArray();
	CHECK(array[0] == -2);
	CHECK(array[1] == 6);
	CHECK(array[2] == 7);
	CHECK(array[3] == -8);		
	
	delete(ds);
	delete(array);
}