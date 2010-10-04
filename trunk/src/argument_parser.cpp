#include "argument_parser.h"

ArgumentParser::ArgumentParser()
{
  donor = DONOR_LOCAL;
  stack = STACK_D;
  parseCursor = 1;
  figuresPositions = 0;
}

ArgumentParser::~ArgumentParser()
{
}

int ArgumentParser::getFiguresCount() const
{
  return figuresCount;
}

int* ArgumentParser::getFiguresPositions() const
{
  return figuresPositions;
}

int ArgumentParser::getQueenPosition() const
{
  return queenPosition;
}

int ArgumentParser::getSize() const
{
  return size;
}

void ArgumentParser::parse(int argc, char **argv)
{
  size = parseOneInt(argc, argv);
  queenPosition = parseOneInt(argc, argv);
  figuresCount = parseOneInt(argc, argv);
  
  figuresPositions = new int[figuresCount];
  for (int i = 0; i < figuresCount; i++)
    figuresPositions[i] = parseOneInt(argc, argv);
    
  while (parseCursor < argc)
    parseOne(argc, argv);
}

int ArgumentParser::parseOneInt(int argc, char **argv)
{
  int tempVal = 0;
  while (tempVal == 0)
    tempVal = parseOne(argc, argv);
    
  return tempVal;
}

int ArgumentParser::parseOne(int argc, char** argv)
{
  // to few arguments
  if (parseCursor >= argc)
    throw InvalidArgumentException(0);

  if (strcmp(argv[parseCursor], "-d") == 0)
  {
    stack = STACK_D;
    parseCursor++;
    return 0;
  }
  else if (strcmp(argv[parseCursor], "-dr") == 0)
  {
    stack = STACK_DR;
    parseCursor++;
    return 0;
  }
  else if (strcmp(argv[parseCursor], "-r") == 0)
  {
    stack = STACK_R;
    parseCursor++;
    return 0;
  }
  else if (strcmp(argv[parseCursor], "-loc") == 0)
  {
    donor = DONOR_LOCAL;
    parseCursor++;
    return 0;
  }
  else if (strcmp(argv[parseCursor], "-rnd") == 0)
  {
    donor = DONOR_RANDOM;
    parseCursor++;
    return 0;
  }
  else if (strcmp(argv[parseCursor], "-glb") == 0)
  {
    donor = DONOR_GLOBAL;
    parseCursor++;
    return 0;
  }
    
  try
  {
    int val = atoi(argv[parseCursor]);
    parseCursor++;
    
    if (!val)
      throw new InvalidArgumentException(argv[parseCursor-1]);

    return val;
  }
  catch (exception& e)
  {
    parseCursor++;
    throw new InvalidArgumentException(argv[parseCursor-1]);
  }
}

DonorAlgorithm ArgumentParser::getDonorAlgorithm() const
{
  return donor;
}

StackType ArgumentParser::getStackType() const
{
  return stack;
}

