#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "priority_queue.h"
#include "priority_queue.cpp"

/**
 * @class Configuration
 * @author Vojta
 * @date 04/01/10
 * @file configuration.h
 * @brief This class represents instance of the problem
 */
class Configuration
{
  private:
    bool isFinal;
    int* figuresPosition;
    int figuresCount;
    int* queenSteps;
    int queenPosition;
    int queenStepsCount;
    //void addAvailableRight(PriorityQueue<int>)

  public:
    Configuration();

    /**
     * @brief Move queen to new position
     * @param newPosition Index of the new position
     */
    void move(int newPosition);

    /**
     * @brief Revert last move of the queen
     */
    void moveBack();

    /**
     * @brief Is this configuration final = sollution ?
     * @return True if configuration is final, False otherwise
     */
    bool getIsFinal() const;

    /**
     * @brief Return number of steps done in this configuration
     * @return Number of steps
     */
    int getStepsCount() const;

    /**
     * @brief Returns PriorityQueue of available positions (positions the queen can move to)
     * @return PriorityQueue of integers (available positions)
     */
    IntPriQueue* getAvailablePositions() const;
};

#endif // CONFIGURATION_H
