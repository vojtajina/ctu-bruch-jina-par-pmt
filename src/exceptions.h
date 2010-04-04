#include <exception>
using namespace std;

/**
 * @file exceptions.h
 * @brief This file contains exceptions
 */

/**
 * @class invalid_position
 * @author Vojta
 * @date 04/04/10
 * @file exceptions.h
 * @brief This exception is thrown when someone refers to invalid position.
 * Invalid position is out of field range of the configuration.
 */
class invalid_position: public exception
{
  virtual const char* what() const throw()
  {
    return "This position is invalid !";
  }
} invalid_position_ex;
