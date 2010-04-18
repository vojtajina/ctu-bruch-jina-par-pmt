#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <stdio.h>

using namespace std;

/**
 * @file exceptions.h
 * @brief This file contains exceptions
 */

/**
 * @class InvalidPositionException
 * @author Vojta
 * @date 04/04/10
 * @file exceptions.h
 * @brief This exception is thrown when someone refers to invalid position.
 * Invalid position is out of field range of the configuration.
 */

class InvalidPositionException: public exception
{
  private:
    char message[50];

  public:
    InvalidPositionException(int position)
    {
      sprintf(message, "This position(%d) is invalid !", position);
    }

    virtual const char* what() const throw()
    {
      return message;
    }
};


/**
 * @class InvalidPriorityException
 * @author Vojta Jina
 * @date 04/16/2010
 * @file exceptions.h
 * @brief This exception is thrown when someone uses out of range priority
 */

class InvalidPriorityException: public exception
{
  private:
    char message[50];

  public:
    InvalidPriorityException(int priority)
    {
      sprintf(message, "This priority(%d) is invalid !", priority);
    }

    virtual const char* what() const throw()
    {
      return message;
    }
};

#endif // EXCEPTIONS_H
