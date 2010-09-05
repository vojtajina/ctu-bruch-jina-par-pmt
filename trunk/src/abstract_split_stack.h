#ifndef SPLITSTACK_H
#define SPLITSTACK_H

/**
 * @file abstract_split_stack.h
 * @brief Definition of the AbstractSplitStack class
 */
 
#include <vector>
#include "string.h"
#include <sstream>

using namespace std;

/**
 * @class AbstractSplitStack
 * @author Vojta Jina
 * @date 04/12/10
 * @brief Stack with some special features (can be splitted)
 * @brief This is an abstract class, that provides the basic API for all concrete stacks
 * @brief Conrete stacks contain the logic of splitting the stack
 */
class AbstractSplitStack
{
  public:

    /**
     * @brief Default constructor
     * @param maxSplitDepth The depth, that stack could be splitted up to
     */
    AbstractSplitStack(int maxSplitDepth);

    /**
     * @brief Default destructor
     */
    ~AbstractSplitStack();

    /**
     * @brief Add item to the top of the stack
     * @param item Added item
     */
    virtual void push(int item);

    /**
     * @brief Remove item from the top of the stack
     * @return Removed item
     */
    virtual int pop();

    /**
       * @brief Returns item from the top of the stack
       * @return Last item
       */
    virtual int head() const;

    /**
    *	@brief Turn head value into negative
    * @brief Negative numbers represent open position (graph node)
    */
    virtual void turnHead();


    /**
     * @brief Whether the stack is empty
     * @return True if stack is empty, False otherwise
     */

    virtual bool empty() const;

    /**
     * @brief Return number of items in the stack
     * @return Number of items in the stack
     */
    virtual int size() const;

    /**
     * @brief Return as integer array (without enclosing zero)
     * @return Pointer to array of integers
     */
    virtual int* toArray() const;

    /**
     * @brief Return as integer array
     * @param enclosingZero If true enclosing zero will appended after the array
     * @return Pointer to array of integers
     */
    virtual int* toArray(bool enclosingZero) const;

    /**
     * @brief Split the stack (extract half - default divider is 2)
     * @return Pointer to new instance of SplitStack
     */
    virtual AbstractSplitStack* split();

    /**
     * @brief Split the stack
     * @param divider Number of parts that stack should be divided into
     * @return Pointer to new instance of SplitStack
     */
    virtual AbstractSplitStack* split(int divider) = 0;

    /**
     * @brief Whether the stack can be splitted (default divider is 2)
     * @return True if is possible to split the stack, False otherwise
     */
    virtual bool canSplit() const;

    /**
     * @brief Whether the stack can be splitted
     * @param divider Number of parts that stack should be divided into
     * @return True if is possible to split the stack, False otherwise
     */
    virtual bool canSplit(int divider) const = 0;

    /**
    *	@brief returns readable current state of stack
    * @return readable state
    */
    virtual string toString() const;

  protected:
  
    /**
     * @brief The storage for the data (integers)
     */
    vector<int>* data;
    
    /**
     * @brief The stack could be splitted up to this depth
     */
    int maxSplitDepth;

    /**
     * @brief Number of floors (depth)
     */
    int getFloorCount() const;
    
    /**
     * @brief Number of not-opened items in specific floor
     * @param floor Specific floor (starts with 1)
     */
    int getStatesCountInFloor(int floor) const;
    
    /**
     * @brief The index of the first item in specific floor
     * @param floor Specific floor (starts with 1)
     */
    int getFloorStartIndex(int floor) const;
};

#endif // SPLITSTACK_H
