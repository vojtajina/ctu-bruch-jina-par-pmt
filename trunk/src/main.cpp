#include <stdlib.h>
#include "configuration.h"
#include "argument_parser.h"

/**
 * @file main.cpp
 * @author Vojta Jina
 * @brief The starting point of the application
 * @brief Parsing the arguments
 * @brief Arguments are:
 * @brief 1 - k = field side length
 * @brief 2 - K = queen position (first position is 1 not zero !!!)
 * @brief 3 - q = number of figures
 * @brief 4 - positions of all figures
 */
 
#ifdef SEQUENTIAL
  #include "sequential_task.h"
#else
  #include "parallel_task.h"
#endif

/**
 * ARGUMENTS
 * 1 - k = field side length (field length = side x side)
 * 2 - K = queen position
 * 3 - q = number figures
 * 4 - F[q] = array of figure positions
 */
int main(int argc, char **argv)
{
  ArgumentParser* ap = new ArgumentParser();
  
  try
  {
    ap->parse(argc, argv);
  }
  catch (exception& e)
  {
    printf("Exception: %s\n", e.what());
    goto bad_args;
  }

  // solve
  Configuration* cnf;
  AbstractTask* t;

  try
  {
    #ifdef SEQUENTIAL
      t = new SequentialTask();
    #else
      t = new ParallelTask(ap->getDonorAlgorithm(), ap->getStackType());
    #endif
    
    cnf = new Configuration(ap->getSize(), ap->getFiguresCount(), ap->getFiguresPositions(), ap->getQueenPosition());   
    cnf = t->solve(cnf);

    if (cnf)
    {
      printf("FINAL SOLLUTION:\n");
      cnf->dump();
      printf("TIME: %f ms\n", t->getTime());
      delete cnf;
    }
    printf("END\n");
  }
  catch (exception& e)
  {
    #ifdef SEQUENTIAL
      printf("Exception: %s\n", e.what());
    #else
      printf("%d: Exception: %s\n", ((ParallelTask*)t)->getPeerId(), e.what());
    #endif
  }

  // free the memory
  delete ap;
  delete t;

  return 0;

bad_args:
  printf("Bad input arguments\n");
  printf("Arguments: field_size queen_position number_of_figures figures_positions\n");

  return 1;
}