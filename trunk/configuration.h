#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "priority_queue.h"

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

    /**
     * @brief Current position of remaining figures
     * Array of bools - true if position is full, false if position is empty
     */
    bool* figuresPosition;

    /**
     * @brief Original position of all figures
     * Array of bools - true if position is full, false if position is empty
     * This array is constant - these values wil not change (its for moving back)
     */
    bool* figuresStartPosition;

    /**
     * @brief Number of remaining figures
     */
    int figuresCount;

    /**
     * @brief History of queen steps (positions visited)
     */
    int* queenSteps;

    /**
     * @brief Number of steps (visited positions)
     */
    int queenStepsCount;
    
    /**
     * @brief Size of the field = k x k
     */
    int fieldLength;
    
    /**
     * @brief Size of one side of the field = k
     * fieldLength = sideLength x sideLength
     */
    int sideLength;

    /**
     * @brief Add available positions in left direction from the queen position
     * @param pq PriorityQueue
     */
    void addAvailableLeft(IntPriQueue* pq) const;

    /**
     * @brief Add available positions in right direction from the queen position
     * @param pq PriorityQueue
     */
    void addAvailableRight(IntPriQueue* pq) const;    
    
    /**
     * @brief Add available positions in top direction from the queen position
     * @param pq PriorityQueue
     */
    void addAvailableTop(IntPriQueue* pq) const;
    
    /**
     * @brief Add available positions in bottom direction from the queen position
     * @param pq PriorityQueue
     */
    void addAvailableBottom(IntPriQueue* pq) const;

    /**
     * @brief Add available positions in left-top (diagonal) direction from the queen position
     * @param pq PriorityQueue
     */
    void addAvailableLeftTop(IntPriQueue* pq) const;
    
    /**
     * @brief Add available positions in right-top (diagonal) direction from the queen position
     * @param pq PriorityQueue
     */
    void addAvailableRightTop(IntPriQueue* pq) const;

    /**
     * @brief Add available positions in left-bottom (diagonal) direction from the queen position
     * @param pq PriorityQueue
     */
    void addAvailableLeftBottom(IntPriQueue* pq) const;
    
    /**
     * @brief Add available positions in right-bottom (diagonal) direction from the queen position
     * @param pq PriorityQueue
     */
    void addAvailableRightBottom(IntPriQueue* pq) const;
    
    /**
     * @brief Abstract method for adding available position into PriorityQueue
     * This method is used by all methods like addAvailableLeftBottom, addAvailableRightBottom, etc...
     * Determines the priority of specific position
     * @param pq PriorityQueu
     * @param position Index of the position to add
     * @return Priority of the avaible position
     */
    int addAvailablePosition(IntPriQueue* pq, int position) const;
    
    /**
     * @brief Remove figure on specific position
     * @param position Index of the position
     * @return True if figure was removed, False if there was no figure on the position
     */
    bool removeFigure(int position);
    
    /**
     * @brief Revert removeFigure() - take the figure back
     * @param position Index of the position
     * @return True if figure was restored, False if there was no figure on start
     */
    bool restoreFigure(int position);
    
    /**
     * @brief Returns index of current position of the queen
     * @return Index of the position
     */
    int getQueenPosition() const;
    
    /**
     * @brief Check whether the position has been visited or not
     * @param position Index of the position
     * @return True if position has been visited, False otherwise
     */
    bool wasPositionVisited(int position) const;

  public:

    /**
     * @brief Constructor
     * @param k Size of the chess box (k x k)
     * @param q Number of figures
     * @param F Array of integers (length q) with positions of the figures
     * @param K Position of the queen (starting position)
     */
    Configuration(int k, int q, int* F, int K);
    
    /**
     * @brief Copying constructor
     * @param src Source Configuration object
     * Object is deeply copyied (except figuresStartPosition pointer)
     */
    Configuration(const Configuration &src);

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
    bool final() const;

    /**
     * @brief Return number of steps done in this configuration
     * @return Number of steps
     */
    int getStepsCount() const;

    /**
     * @brief Returns the length of one side of the field (k)
     * @return Lenght of the side of the field
     */
    int getSideLength() const;
    
    /**
     * @brief Returns the number of figures
     * @return Number of figures in the configuration 
     */
    int getFiguresCount() const;
    
    /**
     * @brief Returns PriorityQueue of available positions (positions the queen can move to)
     * @return PriorityQueue of integers (available positions)
     */
    IntPriQueue* getAvailablePositions() const;
    
    /**
     * @brief Dump the configuration to console
     * Test and debug purposes
     */
    void dump() const;
};

#endif // CONFIGURATION_H
