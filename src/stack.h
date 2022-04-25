#ifndef SRC_STACK_STACK_H_
#define SRC_STACK_STACK_H_

#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>

#include "errors.h"

typedef struct stack {
    double *data;
    ssize_t top;
    ssize_t size;
} stack_t;

stack_t create_stack();

void stack_delete(stack_t *stack);

bool stack_is_empty(stack_t *stack);

bool stack_is_full(stack_t *stack);
status_t extend_stack(stack_t *stack);

status_t push(stack_t *stack, double value);

double pop(stack_t *stack);

double stack_peek(stack_t *stack);

void stack_print(stack_t *stack);

#endif /* SRC_STACK_STACK_H_ */