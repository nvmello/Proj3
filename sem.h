#include "threads.h"


/**
 * semaphore data structure
 *  Contains a value field and a queue of TCBs.
 */
typedef struct semaphore{
    int valueField;     //int value field
    TCB_t *semQ;        //queue of TCBs.
};

/**
 * initSem(sem, val)
 * Initializes the value field with the specified value.
 */
void initSem(struct semaphore *sem, int val){
    sem->valueField = val;
    sem->semQ=newItem();
    initQueue(&(sem->semQ));
}

/**
 * P(sem)
 * The P routine decrements the semaphore, 
 * and if the value is 0 or less than zero then 
 * blocks the process in the queue associated with the semaphore.
 */
void P(struct semaphore *sem){
    sem->valueField--;

    while (sem->valueField<=0) //block process
    {
        //To perform task (a) for every semaphore you declare you have to create a new queue semQ. 
        struct TCB_t *temp;
        //Whenever a thread executed P(S) and S <= 0 the TCB of the thread gets deleted from the RunQ
        temp = delQueue(&(runQ));
        // and inserted at the end of the semQ. 
        addQueue(&(sem->semQ),temp);
        //Then the process calls yield(). 
        yield();
        //In this way if the thread remains in the semQ it never gets executed again. 
    }
    return;
}

/**
 * V(sem)
 * The V routine increments the semaphore,
 * and if the value is 0 or negative, 
 * then takes a PCB out of the semaphore queue 
 * and puts it into the run queue. 
 * Note: The V routine also "yields" to the next runnable process. //this is important.
 */
void V(struct semaphore *sem){
    sem->valueField++;

    while (sem->valueField<=0)
    {
        struct TCB_t *temp;
        //unblock one process. To unblock a process, 
        //you will deleted the head of semQ 
        temp = delQueue(&(sem->semQ));
        //and add at the end of the ReadyQ. 
        addQueue(&runQ, temp);
    }
    //This way the processes can perform yield and the unblocked process will execute again.
    yield();
}


/**
 * 5. Implement a solution to the Producer Consumer Problem with the following settings:
 *      ~see README~ 
 */
