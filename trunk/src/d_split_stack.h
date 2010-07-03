#ifndef DSPLITSTACK_H
#define DSPLITSTACK_H

#include "abstract_split_stack.h" // Base class: AbstractSplitStack
#include "math.h"

class DSplitStack : public AbstractSplitStack
{
public:
    DSplitStack(int maxSplitDepth) : AbstractSplitStack(maxSplitDepth) {};
    DSplitStack* split(int divider);
    bool canSplit(int divider) const;
};

#endif // DSPLITSTACK_H