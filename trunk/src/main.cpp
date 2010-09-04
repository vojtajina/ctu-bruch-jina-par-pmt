#include <stdlib.h>
#include "configuration.h"

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
  // parse inputs
  int k, K, q;
  int* F;

  if (argc < 4)
    goto bad_args;

  try
  {
    k = atoi(argv[1]);
    K = atoi(argv[2]);
    q = atoi(argv[3]);

    if (argc < (4 + q))
      goto bad_args;

    F = new int[q];

    for (int i = 0; i < q; i++)
      F[i] = atoi(argv[i+4]);

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
      t = new ParallelTask();
    #endif
    
    cnf = new Configuration(k, q, F, K);   
    cnf = t->solve(cnf);

    if (cnf)
    {
      printf("FINAL SOLLUTION:\n");
      cnf->dump();
      printf("TIME: %f ms\n", t->getTime());
      delete cnf;
    }
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
  delete[] F;
  delete t;

  return 0;

bad_args:
  printf("Bad input arguments\n");
  printf("Arguments: field_size queen_position number_of_figures figures_positions\n");

  return 1;
}