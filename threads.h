
#include "q.h"

struct TCB_t *runQ; //Global Queue

void start_thread(void (*function)(int, int), int A, int B);

void start_thread(void (*function)(int, int), int A, int B)
{
    //allocate a TCB (via malloc)
    struct TCB_t *tcb = (struct TCB_t*)malloc(sizeof(struct TCB_t));

    //printf("\nmade it to start_thread()\n"); //test output
    //allocate a stack (via malloc) of a certain size (choose 8192)
    int size = 8192;
    void *stack = (void*)malloc(size);
    
    //call init_TCB with appropriate arguments
    init_TCB(tcb,function, stack,size, A, B);
    //call addQ to add this TCB into the “RunQ” which is a global header pointer
    addQueue(&runQ,tcb);
}

void run()
{ 
    //printf("\nmade it to run()\n");
    ucontext_t parent;	// get a place to store the main context, for faking
    getcontext(&parent);	// magic sauce
    swapcontext(&parent, &(runQ->context));	// start the first thread
}

void yield() // similar to run
{
    //printf("\nmade it to yield()\n");
    ucontext_t *prev = &(runQ->context);	// get a place to store the main context, for faking
    
    rotateQ(&runQ);//rotate the run Q;
    
    //swap the context, from previous thread to the thread pointed to by RunQ
    swapcontext(prev,&(runQ->context));
 }
