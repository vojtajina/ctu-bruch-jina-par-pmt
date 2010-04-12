#include "split_stack.h"

/*
 * Special implementation of stack (its more than common stack)
 * There has to be possibility to iterate stack items from the bottom (first item)
 * When stack is being splitted, we need to iterate the items and REMOVE some of them !!!
 * 
 * When T is int, we could implement removing items, by setting it to 0
 * -> then, we must change the logic in numbering position - it should start from 1 (instead of 0)
 * -> because of these reasons:
 *    -> its not possible to store information, that position is open, -3 is open 3 position, but there is no -0
 *    -> we want use 0 as removed item from the stack
 * 
 * In the future there will be more algorithms of splitting the stack, we dont have to care about this just now
 */
 
template <typename T>
SplitStack<T>::SplitStack()
{
}

template <typename T>
SplitStack<T>::~SplitStack()
{
}

template <typename T>
void SplitStack<T>::push(T item)
{
}

template <typename T>
T SplitStack<T>::pop()
{
}

template <typename T>
bool SplitStack<T>::empty() const
{
}

template <typename T>
int SplitStack<T>::size() const
{
}


template <typename T>
T* SplitStack<T>::split()
{
}

template <typename T>
SplitStack<T>* SplitStack<T>::splitToStack()
{
}

// public methods for int
template IntSplitStack::SplitStack(int);
template IntSplitStack::~SplitStack();
template void IntSplitStack::push(int);
template int IntSplitStack::pop();
template bool IntSplitStack::empty() const;
template int IntSplitStack::size() const;
template int* IntSplitStack::split();
template IntSplitStack* IntSplitStack::splitToStack();