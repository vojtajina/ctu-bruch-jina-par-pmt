#ifndef DSPLITSTACK_H
#define DSPLITSTACK_H

/**
 * @file d_split_stack.h
 * @brief Definition of the DSplitStack class
 */
 
#include "abstract_split_stack.h" // Base class: AbstractSplitStack
#include "math.h"

/**
 * @class DSplitStack
 * @author Jirka
 * @date 04/01/10
 * @brief Represents D type of stack
 * @brief D type means D type of splitting algorithm
 */
class DSplitStack : public AbstractSplitStack
{
  public:

    /**
     * @brief Constructor
     * @param maxSplitDepth After reaches this depth, no splitting
     */
    DSplitStack(int maxSplitDepth) : AbstractSplitStack(maxSplitDepth) {};
    
    /**
     * @brief Split the stack - the main algorithm is here
     * @param divider The number how many parts
     * @return New DSplitStack
     */
    DSplitStack* split(int divider);
    
    /**
     * @brief Could this stack be splitted ?
     * @return True if is able to be splitted
     */
    bool canSplit(int divider) const;
};

#endif // DSPLITSTACK_H