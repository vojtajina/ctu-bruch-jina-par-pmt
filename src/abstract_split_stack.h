#ifndef SPLITSTACK_H
#define SPLITSTACK_H

#include <vector>
#include "string.h"
#include <sstream>

using namespace std;
/**
 * @class SplitStack
 * @author Vojta
 * @date 04/12/10
 * @file split_stack.h
 * @brief Stack with some special features (can be splitted)
 */

class AbstractSplitStack
{
	
	  
public:
  

    /**
     * @brief Default constructor
     */
    AbstractSplitStack();

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
    virtual int head();

	/**	
	*	@brief Turn head value into negative	
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
     * @brief return as integer Array
     * @return Pointer to array of splitted items
     */
    virtual int* toArray();

    /**
     * @brief Split the stack (same as split())
     * @return Pointer to new instance of SplitStack<T>
     */
    virtual AbstractSplitStack* split(int divider) = 0;
    
    /**
     * @brief Whether the stack can be splitted
     * @return True if is possible to split the stack, False otherwise
     */
    virtual bool canSplit(int divider) = 0;
	
	/**	
	*	@brief returns readable current state of stack 
	* 	@return readable state
	*/
	virtual string toString();	
	
  protected:
    // TODO
	    vector<int>* data;
		
		int getFloorCount();		
		int getStatesCountInFloor(int floor);
		int getFloorStartIndex(int floor);

  // register typename for SplitStack
  //typedef SplitStack IntSplitStack;
};

#endif // SPLITSTACK_H