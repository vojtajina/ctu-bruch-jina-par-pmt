#ifndef MPICONSTANTS_H
#define MPICONSTANTS_H

// sender peer requests some work
#define MSG_WORK_REQUEST 1000

// sender peer sends some work
#define MSG_WORK_SENT    1001

// sender has no work for us
#define MSG_WORK_NOWORK  1002

// finishing token
#define MSG_TOKEN        1003

// signal from master peer - number 0 (end of the whole process)
#define MSG_FINISH       1004

// send sollution to master, after finish recieved
#define MSG_SOLLUTION    1005

// send to master - no sollution found by this peer
#define MSG_NO_SOLLUTION 1006

// sender has found better sollution (than current global best)
// this message contains only number of steps not whole configuration
#define MSG_SOLLUTION_STEPS 1007

// token values
// MPI has no type bool, therefore I have used char
#define TOKEN_WHITE      'w'
#define TOKEN_BLACK      'b'


// configuration
#define BUFFER_SIZE        20
#define CHECK_MSG_INTERVAL 100

#endif // MPICONSTANTS_H