#include <UnitTest++.h>

#include "../src/configuration.h"

//returns initial configuration for UnitTest
Configuration* GetConfiguration()
{
	int k = 3;
  int K = 1;
  int q = 2;
	int F[2] = {2,5};
	
	Configuration* c = new Configuration(k,q,&F[0],K);
  IntPriQueue* pq = c->getAvailablePositions();
  int i = 0;
  while (!pq->empty())
    i = pq->pop();
    
	return c;
}
//constructor test
TEST(TestConfiguration_Configuration)
{	
	Configuration* c = GetConfiguration();
	delete(c);
}

//constructor test
TEST(TestConfiguration_ConfigurationConfiguration)
{
	Configuration* c = GetConfiguration();
	Configuration* c2 = new Configuration(*c);
	delete(c);
	delete(c2);
}

//Configuration.dump()
TEST(TestConfiguration_dump)
{
	Configuration* c = GetConfiguration();
	c->dump();
	delete(c);
}

//Configuration.final()
TEST(TestConfiguration_final)
{
	Configuration* c = GetConfiguration();
	bool value = c->final();
	CHECK(value == false);	
	c->move(2);
	c->move(5);
	value = c->final();
	CHECK(value == true);
	delete(c);
}

//Configuration.getAvailablePositions()
TEST(TestConfiguration_getAvailablePositions)
{
	Configuration* c = GetConfiguration();
	IntPriQueue* value;
	value = c->getAvailablePositions();
	int i = value->pop();	
	CHECK(i == 2);
	i = value->pop();	
	CHECK(i == 5);
	i = value->pop();	
	CHECK(i == 4);
	i = value->pop();	
	CHECK(i == 7);	
	delete(c);
}

//Configuration.getFiguresCount()
TEST(TestConfiguration_getFiguresCount)
{
	Configuration* c = GetConfiguration();
	int value = c->getFiguresCount();
	CHECK(value == 2);
	delete(c);
}

//Configuration.getSideLength()
TEST(TestConfiguration_getSideLength)
{
	Configuration* c = GetConfiguration();
	int value;
	value = c->getSideLength();
	CHECK(value == 3);
	delete(c);
}

//Configuration.getStepsCount()
//Configuration.move()
//Configuration.moveBack()
TEST(TestConfiguration_getStepsCount)
{
	Configuration* c = GetConfiguration();
	c->move(8);
	int value = c->getStepsCount();
	CHECK(value == 1);
	c->move(3);
	value = c->getStepsCount();
	CHECK(value == 2);
	c->moveBack();
	value = c->getStepsCount();
	CHECK(value == 1);
	delete(c);
}

TEST(TestConfiguration_invalidposition)
{
  Configuration* c = GetConfiguration();
  CHECK_THROW(c->move(-1), InvalidPositionException);
  CHECK_THROW(c->move(10), InvalidPositionException);
  delete(c);
}

// check whether queen can jump over visited position
TEST(TestConfiguration_skipvisited)
{
  Configuration* c = GetConfiguration();
  c->move(5);
  c->move(8);
  IntPriQueue* q = c->getAvailablePositions();
  int pos = q->pop();
  CHECK(pos == 2);
  delete q;
  delete c;
}