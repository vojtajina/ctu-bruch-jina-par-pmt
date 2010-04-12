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

// token values
#define TOKEN_WHITE      true
#define TOKEN_BLACK      false

#endif // MPICONSTANTS_H