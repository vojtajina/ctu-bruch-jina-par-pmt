#include <UnitTest++.h>

#include "../src/argument_parser.h"

// basic arguments
TEST(TestArgumentParser_Basic)
{
	ArgumentParser* a = new ArgumentParser();
  char* argv[] = {"fake", "6", "1", "2", "2", "4"};
  
  a->parse(6, argv);
  CHECK(a->getSize() == 6);
  CHECK(a->getQueenPosition() == 1);
  CHECK(a->getFiguresCount() == 2);
  
  int *pos = a->getFiguresPositions();
  CHECK(pos != 0);
  CHECK(pos[0] == 2);
  CHECK(pos[1] == 4);
  
  delete[] pos;
  delete a;
}

// should throw InvalidArgumentsException if to few arguments
TEST(TestArgumentParser_ToFewArguments)
{
	ArgumentParser* a = new ArgumentParser();
  char* argv[] = {"fake", "6", "1"};
  
  CHECK_THROW(a->parse(3, argv), InvalidArgumentException);
  
  delete a;
}

// should throw InvalidArgumentException if not positions for all figures
TEST(TestArgumentParser_ToFewPositions)
{
  ArgumentParser* a = new ArgumentParser();
  char* argv[] = {"fake", "6", "1", "3", "4", "5"};
  
  CHECK_THROW(a->parse(6, argv), InvalidArgumentException);
  
  delete a;
}

// default stack should be D, default donor algorithm should be LOCAL
TEST(TestArgumentParser_DefaultStackAndDonor)
{
  ArgumentParser* a = new ArgumentParser();
  CHECK(a->getStackType() == STACK_D);
  CHECK(a->getDonorAlgorithm() == DONOR_LOCAL);
  
  delete a;
}

TEST(TestArgumentParser_StackOnAnyPosition)
{
  ArgumentParser* a = new ArgumentParser();
  char* argv[] = {"fake", "6", "-dr", "1", "3", "4", "5", "6"};
  a->parse(8, argv);
  
  CHECK(a->getStackType() == STACK_DR);
  
  delete a;
}

TEST(TestArgumentParser_StackR)
{
  ArgumentParser* a = new ArgumentParser();
  char* argv[] = {"fake", "6", "-r", "1", "3", "4", "5", "8"};
  a->parse(8, argv);
  
  CHECK(a->getStackType() == STACK_R);
  
  delete a;
}

TEST(TestArgumentParser_StackD)
{
  ArgumentParser* a = new ArgumentParser();
  char* argv[] = {"fake", "6", "-d", "1", "3", "4", "5", "8"};
  a->parse(8, argv);
  
  CHECK(a->getStackType() == STACK_D);
  
  delete a;
}

TEST(TestArgumentParser_DonorLocal)
{
  ArgumentParser* a = new ArgumentParser();
  char* argv[] = {"fake", "6", "-loc", "1", "3", "4", "5", "8"};
  a->parse(8, argv);
  
  CHECK(a->getDonorAlgorithm() == DONOR_LOCAL);
  
  delete a;
}


TEST(TestArgumentParser_DonorGlobal)
{
  ArgumentParser* a = new ArgumentParser();
  char* argv[] = {"fake", "6", "-glb", "1", "3", "4", "5", "8"};
  a->parse(8, argv);
  
  CHECK(a->getDonorAlgorithm() == DONOR_GLOBAL);
  
  delete a;
}


TEST(TestArgumentParser_DonorRandom)
{
  ArgumentParser* a = new ArgumentParser();
  char* argv[] = {"fake", "6", "-rnd", "1", "3", "4", "5", "8"};
  a->parse(8, argv);
  
  CHECK(a->getDonorAlgorithm() == DONOR_RANDOM);
  
  delete a;
}

TEST(TestArgumentParser_DonorOrStackAtTheEnd)
{
  ArgumentParser* a = new ArgumentParser();
  char* argv[] = {"fake", "6", "1", "3", "4", "5", "8", "-dr", "-glb"};
  a->parse(9, argv);
  
  CHECK(a->getDonorAlgorithm() == DONOR_GLOBAL);
  CHECK(a->getStackType() == STACK_DR);
  
  delete a;
}