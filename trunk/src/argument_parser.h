#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <cstdlib>
#include <cstring>
#include "exceptions.h"
#include "enums.h"

class ArgumentParser {

public:
	ArgumentParser();
	~ArgumentParser();
  void parse(int argc, char **argv);
  
  int getSize() const;
  int getQueenPosition() const;
  int getFiguresCount() const;
  int* getFiguresPositions() const;
  
  DonorAlgorithm getDonorAlgorithm() const;
  StackType getStackType() const;
  
protected:
  int parseOneInt(int argc, char **argv);
  int parseOne(int argc, char **argv);
  int size;
  int queenPosition;
  int figuresCount;
  int* figuresPositions;
  
  DonorAlgorithm donor;
  StackType stack;
  
  int parseCursor;

};

#endif // ARGUMENTPARSER_H
