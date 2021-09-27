
#ifndef queue_H
#define queue_H

typedef struct queue_T {
    int * entries;
    int max_entries;
    int start;
    int end;
} queue;

int enQueue(queue * queue_p, int value);
int deQueue(queue * queue_p);

int isEmpty(queue * queue_p);
int isFull(queue * queue_p);

queue * new_queue(int size);

#endif