#include "TCB.h"

struct semaphore{
    int valueField;
    TCB_t queue;
}