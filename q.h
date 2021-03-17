#include "TCB.h"
#include <stdlib.h>

/**
 * qElement
 * Basic structure for each link in the doubly linked list
 */
struct qElement{
	int payload;
	struct qElement *prev;
	struct qElement *next;
};

/**
 * newItem()
 * returns a pointer to a new q-element
 * must allocate memory for new q-element
 */
struct TCB_t* newItem(){
	struct TCB_t *newQ = (struct TCB_t*)malloc(sizeof(struct TCB_t));
	return newQ;
}

/**
 * initQueue
 * initializes our queue's head to null and sets the counter to zero
 */
void initQueue(struct TCB_t **input){
	*input=NULL;
}

/**
 * addQueue
 * adds a queue item, pointed to by “item”, to the queue pointed to by head.
 */
void addQueue(struct TCB_t **queue,struct TCB_t *item){
	if ((*queue)==NULL)	//if queue is empty
	{
		(*queue)=item;	//insert into empty queue, head = tail
		(*queue)->prev=item; //because queue is circular, head.pervious = itself
		(*queue)->next=item; //because queue is circular, head.next = itself
	} else{
		struct TCB_t *tail = (*queue)->prev;
		item->next=(*queue);
		item->prev = tail;
		(*queue)->prev = item;
		tail->next = item;
	}
}

/**
 * delQueue
 * deletes an item from head and returns a pointer to the deleted item
 */
struct TCB_t* delQueue(struct TCB_t **queue){
	if ((*queue)!=NULL) //if the queue is not empty
	{
		if ((*queue == (*queue)->next) && (*queue == (*queue)->prev)) //if the queue only has one item in it
		{
			*queue=NULL;		//set head to null
		} 
		else //if the queue has more than one item in it
		{
			struct TCB_t *tail = (*queue)->prev; //create a tail object to keep track of the end
			(*queue)->next->prev=tail;		//point head.next.prev to tail
			tail->next=(*queue)->next;		//point tail.next to head.next
			(*queue)=(*queue)->next;		//reset queue.head
		}
		//set both prev and next pointers of deletedElement to NULL
	} 
	else	//queue has no items in it, simply return NULL value
	{
		return NULL; //else queue is empty, nothing to delete, return
	}
	return (*queue);
}

/**
 * rotateQ
 * Moves the header pointer to the next element in the queue. 
 * This is equivalent to AddQ(&head, DeleteQ(&head)), 
 * but is simpler to use and more efficient to implement.
 */
void rotateQ(struct TCB_t **queue){
	if (*queue != NULL)
    {
        *queue = (*queue)->next; 
    }
}