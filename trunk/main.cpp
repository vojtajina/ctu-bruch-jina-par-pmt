#include <iostream>
#include <stdlib.h>
#include "configuration.h"
#include "task.h"

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

  try
  {
    k = atoi(argv[1]);
    K = atoi(argv[2]);
    q = atoi(argv[3]);

    F = new int[q];
    for (int i = 0; i < q; i++)
      F[i] = atoi(argv[i+4]);

  }
  catch (exception& e)
  {
    cout << "Bad input arguments (Exception: " << e.what() << ")";
  }

  // solve
  Configuration* cnf;
  Task* t;
  
  try
  {
    cnf = new Configuration(k, q, F, K);
    t = new Task(false, true);
    cnf = t->solve(cnf);
    cnf->dump();
    cout << "Start figures: " << q << " Steps: " << cnf->getStepsCount();
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
}
