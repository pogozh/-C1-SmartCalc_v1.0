#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>

#include "errors.h"

// lexem type for tokenize
enum lexemeType { NUMBER, OPERATOR, FUNCTION, BRACKET, UNDEFINED };

typedef struct lexemes {
    enum lexemeType type;
    char val;
    double num;
} lex;

// stack struct with lexem type in it
typedef struct struct_elements stEl;
struct struct_elements {
    lex *value;
    stEl *next;
};

typedef struct stacks {
    int size;
    stEl *top;
} stack_t;

// queue
typedef struct queue_elements quEl;
struct queue_elements {
    lex *value;
    quEl *next;
};

typedef struct queue {
    int size;
    quEl *tail;
} que;

// -----//

typedef struct stack {
    double *data;
    ssize_t top;
    ssize_t size;
} stack;

stack create_stack();

void stack_delete(stack *stack);

bool stack_is_empty(stack *stack);

bool stack_is_full(stack *stack);
status_t extend_stack(stack *stack);

status_t push(stack *stack, double value);

double pop(stack *stack);

double stack_peek(stack *stack);

void stack_print(stack *stack);

#endif /* SRC_STACK_H_ */
