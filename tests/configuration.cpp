#include <UnitTest++.h>
#include "../src/configuration.h"
#include "../src/configuration.cpp"


//returns initial configuration for UnitTest
Configuration* GetConfiguration()
{
	int k, K, q;
	int* F;  
    k = 3;
    K = 0;
    q = 2;	
	int a[2] = {1,4};
	F = a;	
	
	Configuration* c = new Configuration(k,q,F,K);
	return c;
}

TEST(TestConfiguration_Configuration)
{	
	Configuration* c = GetConfiguration();
	delete(c);
}

TEST(TestConfiguration_ConfigurationConfiguration)
{
	Configuration* c = GetConfiguration();
	Configuration* c2 = new Configuration(*c);
	delete(c);
	delete(c2);
}

TEST(TestConfiguration_dump)
{
	Configuration* c = GetConfiguration();
	c->dump();
	delete(c);
}

TEST(TestConfiguration_final)
{
	Configuration* c = GetConfiguration();
	bool value = c->final();
	CHECK(value == false);	
	c->move(1);
	c->move(4);
	value = c->final();
	CHECK(value == true);
	delete(c);
}

TEST(TestConfiguration_getAvailablePositions)
{
	Configuration* c = GetConfiguration();
	IntPriQueue* value;
	value = c->getAvailablePositions();
	int i= value->pop();	
	CHECK(i == 1);
	i = value->pop();	
	CHECK(i == 4);
	i = value->pop();	
	CHECK(i == 3);
	i = value->pop();	
	CHECK(i == 6);	
	delete(c);
}

TEST(TestConfiguration_getFiguresCount)
{
	Configuration* c = GetConfiguration();
	int value = c->getFiguresCount();
	CHECK(value == 2);
	delete(c);
}

TEST(TestConfiguration_getSideLength)
{
	Configuration* c = GetConfiguration();
	int value;
	value = c->getSideLength();
	CHECK(value == 3);
	delete(c);
}

TEST(TestConfiguration_getStepsCount)
{
	Configuration* c = GetConfiguration();
	c->move(9);
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

TEST(TestConfiguration_move)
{
	
	Configuration* c = GetConfiguration();
	delete(c);
}

TEST(TestConfiguration_moveBack)
{
	Configuration* c = GetConfiguration();	
	delete(c);
}

