#include <iostream>
#include "configuration.h"
#include "priority_queue.h"

using namespace std;

int main(int argc, char **argv)
{
  try
  {
    Configuration* cnf;
    cnf = new Configuration();

    IntPriQueue* pq = cnf->getAvailablePositions();

    int a;
    while (!pq->empty())
    {
      a = pq->pop();
      cout << a << "\n";
    }

  }
  catch (exception& e)
  {
    cout << "Exception: " << e.what();
  }

  return 0;
}
