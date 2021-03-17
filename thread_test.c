#include "threads.h"


int globalCount = 0;

void func1(int threadID, int numExecutions){

    int localVar = 0;
    // printf("threadID: %d", threadID);
    // printf("numExe: %d", numExecutions);
    while (localVar<numExecutions)
    {
        localVar+=1;
        globalCount += threadID;
        
        printf("\n This is %d th execution of thread %d with global var value %d \n", localVar,threadID, globalCount);
        yield();
    }
}

int main(){
    runQ = newItem();
    initQueue(&runQ);
    char str[100];
    char *token;
    int qtyThreads;
    int numExecutions;
    scanf("%s",str);
    //puts(str); //TEST OUTPUT
    
    token = strtok(str,",");
    qtyThreads = atoi(token);
    token = strtok(NULL,"\n");
    numExecutions = atoi(token);
    //puts(token);
    if (numExecutions == 0)
    {
        
    } else{
    
    if (qtyThreads==0)
    {
        printf("No Threads\n");
    } else{
         //printf("%d , %d", qtyThreads,numExecutions);
        for (int threadID = 1; threadID <= qtyThreads; threadID++)
        {
            start_thread(func1,threadID, numExecutions);
        }
      run();
    }
    }
}   