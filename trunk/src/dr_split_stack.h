#ifndef DRSPLITSTACK_H
#define DRSPLITSTACK_H

#include "abstract_split_stack.h" // Base class: AbstractSplitStack
#include "math.h"

class DRSplitStack : public AbstractSplitStack {

public:
	DRSplitStack();
	~DRSplitStack();
	DRSplitStack* split(int divider);
	bool canSplit(int divider);
};

#endif // DRSPLITSTACK_H
