#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>

#include "errors.h"

// STACK PART
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
    lex *lexi;
    stEl *next;
    stEl *prev;
};

typedef struct stacks {
    int size;
    stEl *head;
} stack_t;

stack_t *stack_init();
lex *stack_pop(stack_t *stack, int freeFlag);
void stack_free(stack_t *stack);
void stack_push(stack_t *stack, lex *new_value);
bool stack_add_new_lex(stack_t *stack, lex new_value);

// stack utils
lex lex_init();
void print_lexem(lex lex);
void stack_print(stack_t *stack);

// QUEUE PART !
typedef struct queue_elements quEl;
struct queue_elements {
    lex *lexi;
    quEl *next;
    quEl *prev;
};

typedef struct queue {
    int size;
    quEl *tail;
} que;

que *queue_init();
lex *queue_pop(que *queue);
void queue_push(que *queue, lex *new_value);
void queue_free(que *queue);
bool queue_add_new_lex(que *queue, lex new_value);
void queue_print(que *queue);
#endif /* SRC_STACK_H_ */
