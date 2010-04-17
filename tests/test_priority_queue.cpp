#include <UnitTest++.h>
#include "../src/priority_queue.h"

//constructor test
TEST(TestPriorityQueue_PriorityQueue)
{
	IntPriQueue *pq = new IntPriQueue(5);	
	CHECK(pq->empty() == true);	
	delete(pq);
}

//IntPriQueue.empty()
TEST(TestPriorityQueue_empty)
{
	IntPriQueue *pq = new IntPriQueue(5);
	pq->push(5,2);
	pq->push(22,3);	
	pq->push(1,4);	
	pq->push(99,1);	
	pq->push(10,3);
	pq->push(1,2);	
	pq->pop();
	pq->pop();
	pq->pop();
	pq->pop();
	pq->pop();
	pq->pop();
	CHECK(pq->empty() == true);
	delete(pq);
}

//IntPriQueue.push()
//IntPriQueue.pop()
TEST(TestPriorityQueue_pushpop)
{
	IntPriQueue *pq = new IntPriQueue(5);
	pq->push(5,2);
	pq->push(22,3);	
	pq->push(1,4);	
	pq->push(99,1);	
	pq->push(10,3);
	pq->push(1,2);	
	int checkvalue;
	checkvalue = pq->pop();
	CHECK(checkvalue == 99);
	checkvalue = pq->pop();
	CHECK(checkvalue == 5);
	checkvalue = pq->pop();
	CHECK(checkvalue == 1);
	checkvalue = pq->pop();
	CHECK(checkvalue == 22);
	checkvalue = pq->pop();
	CHECK(checkvalue == 10);
	delete(pq);
}

//IntPriQueue.reversePop()
TEST(TestPriorityQueue_reversepop)
{
	IntPriQueue *pq = new IntPriQueue(5);
	pq->push(5,2);
	pq->push(22,3);	
	pq->push(1,4);	
	pq->push(99,1);	
	pq->push(10,3);
	pq->push(1,2);	
	int checkvalue;
	checkvalue = pq->reversePop();
	CHECK(checkvalue == 1);
	checkvalue = pq->reversePop();
	CHECK(checkvalue == 22);
	checkvalue = pq->reversePop();
	CHECK(checkvalue == 10);
	checkvalue = pq->reversePop();
	CHECK(checkvalue == 5);
	checkvalue = pq->reversePop();
	CHECK(checkvalue == 1);
	delete(pq);
}

//IntPriQueue.size()
TEST(TestPriorityQueue_size)
{
	IntPriQueue *pq = new IntPriQueue(5);
	pq->push(5,2);
	CHECK(pq->size() == 1);
	pq->push(22,3);	
	CHECK(pq->size() == 2);
	pq->push(1,4);	
	CHECK(pq->size() == 3);
	pq->push(99,1);	
	CHECK(pq->size() == 4);
	pq->push(10,3);
	CHECK(pq->size() == 5);
	pq->push(1,2);	
	CHECK(pq->size() == 6);	
	delete(pq);
}

TEST(TestPriorityQueue_invalidpriority)
{
  IntPriQueue *pq = new IntPriQueue(2);
  CHECK_THROW(pq->push(2,3), InvalidPriorityException);
  CHECK_THROW(pq->push(2,-1), InvalidPriorityException);
  delete(pq);
}
