#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct queue * queue_t;
struct lib_queue {
	queue_t (*new) (size_t capacity);
	int (*top) (queue_t queue);
	size_t (*size) (queue_t queue);
	void (*pop) (queue_t queue);
	void (*push) (queue_t queue, int obj);
	queue_t (*delete) (queue_t queue);
};
extern const struct lib_queue Queue;

#endif