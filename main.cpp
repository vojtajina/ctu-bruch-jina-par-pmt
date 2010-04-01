#include <iostream>
#include "configuration.h"
#include "priority_queue.h"
//#include "priority_queue.cpp"

using namespace std;

int main(int argc, char **argv)
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

  return 0;
}
