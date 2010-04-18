#include <iostream>
#include <stdlib.h>
#include "configuration.h"
#include "parallel_task.h"

using namespace std;

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
    cout << "Exception: " << e.what() << "\n";
    goto bad_args;
  }

  // solve
  Configuration* cnf;
  ParallelTask* t;
  
  try
  {
    cnf = new Configuration(k, q, F, K);
    t = new ParallelTask();
    cnf = t->solve(cnf);
    if (t->isMaster())
    {
      cnf->dump();
      cout << "Start figures: " << q << " Steps: " << cnf->getStepsCount() << "\n";
    }
  }
  catch (exception& e)
  {
    cout << "Exception: " << e.what();
  }
  
  // free the memory
  delete[] F;
  delete t;
  delete cnf;

  return 0;
  
  bad_args:
  cout << "Bad input arguments\n";
  return 1;
}
