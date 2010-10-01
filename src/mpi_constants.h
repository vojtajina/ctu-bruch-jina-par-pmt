#ifndef MPICONSTANTS_H
#define MPICONSTANTS_H

/**
 * @file mpi_constants.h
 * @brief Definition of all constants
 */

/**
 * @brief Sender peer requests some work
 */
#define MSG_WORK_REQUEST 1000

/**
 * @brief Sender peer requests some for indirect
 * @brief requester -> master (without data)
 * @brief master -> donor (with integer - id of requester)
 * @brief donor will reply MSG_WORK_SENT or MSG_WORK_NOWORK to requester
 */
#define MSG_WORK_REQ_INDIRECT 1008

/**
 * @brief Sender peer sends some work
 * @brief Contains the work (array of integers)
 */
#define MSG_WORK_SENT    1001

/**
 * @brief Sender has no work for us
 */
#define MSG_WORK_NOWORK  1002

/**
 * @brief Finishing token
 * @brief Contains a token (white/black)
 */
#define MSG_TOKEN        1003

/**
 * @brief Signal from master peer (end of the whole process)
 * @brief Peers reply to this message by MSG_SOLLUTION or MSG_NO_SOLLUTION
 */
#define MSG_FINISH       1004

/**
 * @brief Send sollution to master, after finish recieved
 * @brief Contains the sollution (array of integers - steps)
 */
#define MSG_SOLLUTION    1005

/**
 * @brief Send to master - no sollution found by this peer
 */
#define MSG_NO_SOLLUTION 1006

/**
 * @brief Sender has found better sollution (than current global best)
 * @brief Contains number of steps of this best sollution
 */
#define MSG_SOLLUTION_STEPS 1007

/**
 * @brief Token white
 * @brief There is no bool type in MPI, so we use char
 */
#define TOKEN_WHITE      'w'

/**
 * @brief Token black
 * @brief There is no bool type in MPI, so we use char
 */
#define TOKEN_BLACK      'b'


/**
 * @brief Size of the buffer
 * @brief Buffer is used for reading message content
 */
#define BUFFER_SIZE        130

/**
 * @brief How often should be new messages checked ?
 * @brief The number is number of positions checked before checking messages again
 */
#define CHECK_MSG_INTERVAL 80

#endif // MPICONSTANTS_H