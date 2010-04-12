#ifndef SPLITSTACK_H
#define SPLITSTACK_H

#include <stdlib.h>

/**
 * @class SplitStack
 * @author Vojta
 * @date 04/12/10
 * @file split_stack.h
 * @brief Stack with some special features (can be splitted)
 */
template <typename T>
class SplitStack<T>
{
  public:
    /**
     * @brief Default constructor
     */
    SplitStack();

    /**
     * @brief Default destructor
     */
    ~SplitStack();

    /**
     * @brief Add item to the top of the stack
     * @param item Added item
     */
    void push(T item);

    /**
     * @brief Remove item from the top of the stack
     * @return Removed item
     */
    T pop();

    /**
     * @brief Whether the stack is empty
     * @return True if stack is empty, False otherwise
     */
    bool empty() const;

    /**
     * @brief Return number of items in the stack
     * @return Number of items in the stack
     */
    int size() const;

    /**
     * @brief Split the stack (remove some items)
     * @return Pointer to array of splitted items
     */
    T* split();

    /**
     * @brief Split the stack (same as split())
     * @return Pointer to new instance of SplitStack<T>
     */
    SplitStack<T>* splitToStack();

  private:
    // TODO

  // register typename for SplitStack<int>
  typedef SplitStack<int> IntSplitStack;
};

#endif // SPLITSTACK_H
