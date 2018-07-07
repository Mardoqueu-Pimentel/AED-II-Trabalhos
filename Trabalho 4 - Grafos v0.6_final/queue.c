#include <queue.h>

struct queue {
	size_t capacity, begin, end;
	int data[0];
};

static queue_t new (size_t capacity) {
	queue_t queue = malloc(
		sizeof(struct queue) +
		(sizeof(int) * capacity)
	);
	queue->capacity = capacity;
	queue->begin = queue->end = 0;

	return queue;
}
inline static inline int top (queue_t queue) {
	return queue->data[queue->begin];
}
inline static inline size_t size (queue_t queue) {
	return queue->end - queue->begin;
}
inline static inline void pop (queue_t queue) {
	++queue->begin;
}
inline static void inline push (queue_t queue, int obj) {
	queue->data[queue->end] = obj;
	++queue->end;
}
static queue_t delete (queue_t queue) {
	free (queue);
	return NULL;
}

const struct lib_queue Queue = {
	.new = new,
	.push = push,
	.top = top,
	.pop = pop,
	.size = size,
	.delete = delete
};