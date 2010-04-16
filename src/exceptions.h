#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
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
  virtual const char* what() const throw() {
    return "This position is invalid !";
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
  virtual const char* what() const throw() {
    return "This priority is invalid !";
  }
};

#endif // EXCEPTIONS_H