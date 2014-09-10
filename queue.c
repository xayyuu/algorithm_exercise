#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>


#define ELEMENT_TYPE  int
#define QUEUE_SIZE 10
enum {YES =1, NO = 0 };

typedef struct _NODE
{
	struct _NODE *next;
	ELEMENT_TYPE nvalue;
}node;

typedef struct _QUEUE_LIST 
{
	node * head;
	node *tail;
 
}  *pqueue ;

pqueue make_empty_queue_list(void)
{
	pqueue t = (pqueue) malloc (sizeof( node));
	assert( t != NULL);

	t->head = t->tail = NULL;
	return t;
}

void destory_list(node *head, node *tail)
{
	if( head == NULL || tail == NULL )
		return ;
	node *tmp = head->next;
	while(head != tail)
	{
		free(head);
		head = tmp;
		tmp = head->next;
	}
	free(tail);
	return ;
	
}

void destory_queue_list(pqueue t)
{
	if( t == NULL ) 
		return ;

	destory_list(t->head, t->tail);
	t->head = t->tail  = NULL;
	free(t);
	printf("distory the queue\n");
	return ;
}
		

void enqueue_v2(pqueue t, ELEMENT_TYPE x)
{
	node *tmp = (node *) malloc (sizeof(node));
	assert(tmp != NULL );
	tmp->nvalue = x;
	tmp->next  = NULL;
	if( t->head == NULL || t->tail == NULL )
	{
		t->head = t->tail = tmp;
	}
	else
	{
		t->tail->next = tmp;
		t->tail = tmp;
	}
}

int isempty_queue_v2(pqueue t)
{
	if( t->head ==  NULL || t->tail  == NULL )
		return YES;
	return NO;
}

ELEMENT_TYPE dequeue_v2(pqueue t)
{
	assert(isempty_queue_v2(t) == NO );

	ELEMENT_TYPE x = t->head->nvalue;
	node *tmp = t->head->next;
	free(t->head);
	t->head = tmp;
	return x;
}
 

typedef struct _QUEUE
{
	int head;
	int tail;
	ELEMENT_TYPE ary[QUEUE_SIZE];
}queue;

void make_empty_queue_v1(queue *q)
{
	q->head = q->tail = 0;
}
	

int isfull_queue(queue *q)
{
	if( q->head < q->tail && (q->tail - q->head) == (QUEUE_SIZE - 1))
		return YES;
	else if( q->head > q->tail && q->head  == (q->tail + 1) )
		return YES;
	else
		return NO;

}

int isempty_queue(queue *q)
{
	return q->head == q->tail ?  YES: NO;
}

void enqueue_v1(queue * q, ELEMENT_TYPE x)
{
	assert( isfull_queue(q) == NO );
 
	(q->ary)[q->tail] = x;
	q->tail = (q->tail+1)%QUEUE_SIZE;

}

ELEMENT_TYPE dequeue_v1(queue* q)
{
	assert( isempty_queue(q)  == NO);
	ELEMENT_TYPE x = (q->ary)[q->head];
	q->head = (q->head + 1) % QUEUE_SIZE;
	return x;
}

 

int main()
{
 	pqueue q = make_empty_queue_list();

	int i ;
	for(i = 0; i < QUEUE_SIZE; ++i)
		enqueue_v2(q, i);
	for(i = 0 ; i < QUEUE_SIZE; ++i)
		printf("deque: %d\n", dequeue_v2(q));
 	destory_queue_list(q);
	system("pause");
	return 0;
}



