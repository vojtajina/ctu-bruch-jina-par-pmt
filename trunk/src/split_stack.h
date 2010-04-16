#ifndef SPLITSTACK_H
#define SPLITSTACK_H

#include <vector>
#include "string.h"
#include "math.h"
#include <sstream>

using namespace std;
/**
 * @class SplitStack
 * @author jBr
 * @date 2010-04-16
 * @file split_stack.h
 * @version beta1
 * @brief Stack with some special features (can be splitted)
 */

class SplitStack
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
    void push(int item);

    /**
     * @brief Remove item from the top of the stack
     * @return Removed item
     */
    int pop();
	
	/**
     * @brief Returns item from the top of the stack
     * @return Last item
     */
    int head();

	/**	
	*	@brief Turn head value into negative	
	*/
	void turnHead();


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
     * @brief return as integer Array
     * @return Pointer to array of splitted items
     */
    int* toArray();

    /**
     * @brief Split the stack (same as split())
     * @return Pointer to new instance of SplitStack<T>
     */
    SplitStack* splitToStack(int divider);
    
    /**
     * @brief Whether the stack can be splitted
     * @return True if is possible to split the stack, False otherwise
     */
    bool canSplit(int divider) ;
	
	/*
	*
	*	@brief returns readable current state of stack 
	*/
	string toString();	
  private:
    // TODO
	    vector<int>* data;
		
		int getFloorCount();		
		int getStatesCountInFloor(int floor);

  // register typename for SplitStack
  typedef SplitStack IntSplitStack;
};

#endif // SPLITSTACK_H