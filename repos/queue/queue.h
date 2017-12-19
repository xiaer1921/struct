#pragma c9x on
#ifndef _QUEUE_H
#define _QUEUE_H
#include <stdbool.h>

#define MAXQUEUE 10

typedef int Item;

typedef struct node
{
    Item item;
    struct node* next;
}Node;

typedef struct queue
{
    Node* front;
    Node* rear;
    int items;
}Queue;

void InitializeQueue(Queue* pq);

bool QueueIsFull(const Queue* pq);

bool QueueIsEmpty(const Queue* pq);

int QueueItemCount(const Queue* pq);

// add a item in queue rear
bool EnQueue(Item item, Queue* pq);

// del a item from queue front
bool DeQueue(Item* pitem, Queue* pq);

void EmptyTheQueue(Queue* pq);

#endif
