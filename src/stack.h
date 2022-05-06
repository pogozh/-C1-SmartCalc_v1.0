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
    char chr;
    double num;
} lex;

// stack struct with lexem type in it
typedef struct stack_elements stEl;
struct stack_elements {
    lex *value;
    stEl *next;
    stEl *prev;
};

typedef struct stacks {
    int size;
    stEl *head;
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

stack_t *stack_init();
lex *stack_pop(stack_t *stack, int freeFlag);
void stack_free(stack_t *stack, int value);
void stack_push(stack_t *stack, lex *new_value);
bool stack_add_new_lex(stack_t *stack, lex new_value);

lex *lex_init();
void print_lexem(lex lex);
void stack_print(stack_t *stack);

// ---OLD---//

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

#endif /* SRC_STACK_H_ */
