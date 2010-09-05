#ifndef RSPLITSTACK_H
#define RSPLITSTACK_H

/**
 * @file r_split_stack.h
 * @brief Definition of the RSplitStack class
 */
 
#include "abstract_split_stack.h" // Base class: AbstractSplitStack
#include "math.h"

/**
 * @class RSplitStack
 * @author Jirka
 * @date 04/01/10
 * @brief Represents R type of stack
 * @brief R type means R type of splitting algorithm
 */
class RSplitStack : public AbstractSplitStack
{
  public:
  
    /**
     * @brief Constructor
     * @param maxSplitDepth After reaches this depth, no splitting
     */
    RSplitStack(int maxSplitDepth) : AbstractSplitStack(maxSplitDepth) {};
    
    /**
     * @brief Split the stack - the main algorithm is here
     * @param divider The number how many parts
     * @return New RSplitStack
     */
    RSplitStack* split(int divider);
    
    /**
     * @brief Could this stack be splitted ?
     * @return True if is able to be splitted
     */
    bool canSplit(int divider) const;
};

#endif // RSPLITSTACK_H