#include <UnitTest++.h>

#include "../src/r_split_stack.h"

RSplitStack* GetRStack()
{
	RSplitStack *rs = new RSplitStack();
	rs->push(1);rs->push(2);
	rs->turnHead();
	rs->push(3);rs->push(4);rs->push(5);rs->push(6);rs->push(7);rs->push(8);
	rs->turnHead();
	rs->push(9);rs->push(10);rs->push(11);rs->push(12);rs->push(13);rs->push(14);rs->push(15);
	rs->turnHead();
	//state =  1 -2 3 4 5 6 7 -8 9 10 11 12 13 14 -15
	return rs;
}
//RSplitStack.canSplit()
TEST(TestRSplitStack_canSplit)
{
	//TODO
}

//RSplitStack.split()
TEST(TestRSplitStack_split)
{
	int value = 0;
	
	RSplitStack *rs = GetRStack();
	RSplitStack *rs2 = rs->split(2);
	
	
	//first divide	
	CHECK(rs2->size() == 5);	
	value = rs2->pop();	
	CHECK(value == 11);
	//delete(rs2);
	
	int *array = rs->toArray();
	CHECK(array[0] == 1);
	CHECK(array[1] == -2);
	CHECK(array[2] == 3);
	
	
	//second divide
	RSplitStack *rs3 = rs->split(2);
	array = rs3->toArray();
	CHECK(rs3->size() == 4);	
	CHECK(array[0] == -2);
	CHECK(array[1] == -8);
	CHECK(array[2] == 12);	
	CHECK(array[3] == 13);	
	//delete(rs3);

	array = rs->toArray();
	CHECK(array[0] == 1);
	CHECK(array[1] == -2);
	CHECK(array[2] == 3);	
	
	//delete(rs);
	delete(array);
	
}