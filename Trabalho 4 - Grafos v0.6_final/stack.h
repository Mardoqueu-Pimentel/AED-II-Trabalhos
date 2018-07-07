#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct stack * stack_t;
struct lib_stack {
	stack_t (*new) (size_t capacity);
	int (*top) (stack_t stack);
	size_t (*size) (stack_t stack);
	void (*pop) (stack_t stack);
	void (*push) (stack_t stack, int obj);
	void (*walk) (stack_t stack, void (*f)(int));
	stack_t (*delete) (stack_t stack);
};
extern const struct lib_stack Stack;

#endif