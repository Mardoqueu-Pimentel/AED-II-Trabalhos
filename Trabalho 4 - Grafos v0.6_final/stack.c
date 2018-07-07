#include <stack.h>

struct stack {
	size_t capacity, size;
	int data[0];
};

static stack_t new (size_t capacity) {
	stack_t stack = malloc(
		sizeof(struct stack) +
		(sizeof(int) * capacity)
	);
	stack->capacity = capacity;
	stack->size = 0;

	return stack;
}
inline static int top (stack_t stack) {
	return stack->data[stack->size - 1];
}
inline static size_t size (stack_t stack) {
	return stack->size;
}
inline static void pop (stack_t stack) {
	--stack->size;
}
static void push (stack_t stack, int obj) {
	stack->data[stack->size] = obj;
	++stack->size;
}
static void walk (stack_t stack, void (*f)(int)){
	int size = stack->size;
	for (int i = 0; i < size; ++i) {
		f(stack->data[i]);
	}
}
static stack_t delete (stack_t stack) {
	free(stack);
	return NULL;
}

const struct lib_stack Stack = {
	.new = new,
	.push = push,
	.top = top,
	.pop = pop,
	.size = size,
	.walk = walk,
	.delete = delete
};