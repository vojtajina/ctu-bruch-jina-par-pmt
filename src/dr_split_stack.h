#ifndef DRSPLITSTACK_H
#define DRSPLITSTACK_H

/**
 * @file dr_split_stack.h
 * @brief Definition of the DRSplitStack class
 */
 
#include "abstract_split_stack.h" // Base class: AbstractSplitStack
#include "math.h"

/**
 * @class DRSplitStack
 * @author Jirka
 * @date 04/01/10
 * @brief Represents DR type of stack
 * @brief DR type means DR type of splitting algorithm
 */
class DRSplitStack : public AbstractSplitStack
{
  public:
  
    /**
     * @brief Constructor
     * @param maxSplitDepth After reaches this depth, no splitting
     */
    DRSplitStack(int maxSplitDepth) : AbstractSplitStack(maxSplitDepth) {};
    
    /**
     * @brief Split the stack - the main algorithm is here
     * @param divider The number how many parts
     * @return New DSplitStack
     */
    DRSplitStack* split(int divider);
    
    /**
     * @brief Could this stack be splitted ?
     * @return True if is able to be splitted
     */
    bool canSplit(int divider) const;
};

#endif // DRSPLITSTACK_H
