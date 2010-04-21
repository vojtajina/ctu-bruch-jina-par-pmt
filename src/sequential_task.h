#ifndef SEQUENTIALTASK_H
#define SEQUENTIALTASK_H

#include "abstract_task.h" // Base class: AbstractTask

class SequentialTask : public AbstractTask
{
  protected:
    void processConfiguration();
};

#endif // SEQUENTIALTASK_H
