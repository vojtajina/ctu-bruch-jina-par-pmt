#ifndef RSPLITSTACK_H
#define RSPLITSTACK_H

#include "abstract_split_stack.h" // Base class: AbstractSplitStack
#include "math.h"

class RSplitStack : public AbstractSplitStack
{
  public:
    RSplitStack* split(int divider);
    bool canSplit(int divider) const;
};

#endif // RSPLITSTACK_H