#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

/**
 * @file exceptions.h
 * @brief Definition and implementation of all exceptions
 */
 
#include <exception>
#include <stdio.h>

using namespace std;

/**
 * @class InvalidPositionException
 * @author Vojta Jina
 * @date 04/04/10
 * @brief This exception is thrown when someone refers to invalid position.
 * @brief Invalid position is out of field range of the configuration.
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

/**
 * @class InvalidArgumentsException
 * @author Vojta Jina
 * @date 10/04/2010
 * @brief Invalid input command arguments
 */

class InvalidArgumentException: public exception
{
  private:
    char message[50];

  public:
    InvalidArgumentException(char* invalidArg)
    {
      if (invalidArg)
        sprintf(message, "Invalid argument \"%s\"", invalidArg);
      else
        sprintf(message, "%s", "To few arguments");
    }

    virtual const char* what() const throw()
    {
      return message;
    }
};

#endif // EXCEPTIONS_H
