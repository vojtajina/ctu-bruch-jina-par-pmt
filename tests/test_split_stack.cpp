#include <UnitTest++.h>

#include "../src/d_split_stack.h"

DSplitStack* GetStack()
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

//AbstractSplitStack.empty()
TEST(TestDbstractSplitStack_empty)
{
	DSplitStack *ds = GetStack();
	int i;
	for(i = 0;i<15;i++)
	{
		ds->pop();
	}
	CHECK(ds->empty() == true);
	delete(ds);
}


TEST(TestDbstractSplitStack_head)
{
	DSplitStack *ds = GetStack();
	CHECK(ds->head() == -15);
	delete(ds);

}

TEST(TestDbstractSplitStack_pop)
{
	DSplitStack *ds = GetStack();		
	CHECK(ds->pop() == -15);
	CHECK(ds->pop() == 14);
	CHECK(ds->pop() == 13);
	CHECK(ds->pop() == 12);
	CHECK(ds->pop() == 11);
	CHECK(ds->pop() == 10);
	CHECK(ds->pop() == 9);
	CHECK(ds->pop() == -8);
	CHECK(ds->pop() == 7);
	CHECK(ds->pop() == 6);
	CHECK(ds->pop() == 5);
	CHECK(ds->pop() == 4);
	CHECK(ds->pop() == 3);
	CHECK(ds->pop() == -2);
	CHECK(ds->pop() == 1);
	delete(ds);
}

TEST(TestDbstractSplitStack_push)
{
	DSplitStack *ds = GetStack();
	int size = ds->size();
	ds->push(99);
	CHECK(ds->size() == (size+1));
	CHECK(ds->head() == 99);
	CHECK(ds->pop() == 99);
	CHECK(ds->size() == size);
	delete(ds);
}

TEST(TestDbstractSplitStack_size)
{
	DSplitStack *ds = GetStack();
	CHECK(ds->size() == 15);
	delete(ds);
}

TEST(TestDbstractSplitStack_toArray)
{
	DSplitStack *ds = GetStack();
	int *array = ds->toArray();
	int i;
	int size = ds->size() + 1 ;
	for(i = 1;i<size;i++)
	{
		int value = array[i-1];
		if(i == 2 || i == 8 || i == 15)		
			CHECK(value == -i);
		else
			CHECK(value == i);
	}
	delete(array);
	delete(ds);
}


TEST(TestDbstractSplitStack_turnHead)
{
	DSplitStack *ds = GetStack();
	CHECK(ds->head() == -15);
	ds->turnHead();
	CHECK(ds->head() == 15);
	ds->push(16);ds->turnHead();
	CHECK(ds->head() == -16);
	delete(ds);
}

