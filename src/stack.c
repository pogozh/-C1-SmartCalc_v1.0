#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

mstack *stack_init() {
    mstack *ret;
    ret = (mstack *)calloc(1, sizeof(mstack));
    ret->head = NULL;
    ret->size = 0;
    return ret;
}

lex *stack_pop(mstack *stack) {
    lex *retval = NULL;
    if (stack->size >= 1) {
        stack->size--;
        retval = stack->head->lexi;
        stEl *trash = stack->head;

        if (stack->size > 0) {
            stack->head = stack->head->prev;
            stack->head->next = NULL;
        } else {
            stack->head = NULL;
        }

        free(trash);
    } else {
        retval = NULL;
    }
    return retval;
}

void stack_push(mstack *stack, lex *new_value) {
    stEl *new_stack_element = (stEl *)calloc(1, sizeof(stEl));
    new_stack_element->lexi = new_value;
    if (stack->size > 0) {
        stack->head->next = new_stack_element;
        new_stack_element->prev = stack->head;
    }
    stack->head = new_stack_element;
    stack->size++;
}

// TODO: delete flag
void stack_free(mstack *stack) {
    if (stack != NULL) {
        while (stack->size > 0) {
            lex *val2clean = stack_pop(stack);
            free(val2clean);
        }
        free(stack);
    }
}

// LEXEMES UTILS

bool stack_add_new_lex(mstack *stack, lex new_value) {
    int ret = 0;
    lex *new_lex;
    new_lex = (lex *)calloc(1, sizeof(lex));
    if (new_lex != NULL) {
        new_lex->num = new_value.num;
        new_lex->type = new_value.type;
        new_lex->chr = new_value.chr;
        stack_push(stack, new_lex);
        ret = true;
    } else {
        free(new_lex);
    }

    return ret;
}

lex lex_init() {
    lex new_lex = {.num = 0, .chr = '\0', .type = UNDEFINED};
    return new_lex;
}

// DEBUG FUCTIONS - COMMENTS FOR BETTER COVERAGE
// void stack_print(mstack *stack) {
//     printf("!NEW STACK! printing ...\n");
//     lex *stlx = stack->head->lexi;
//     int len = stack->size;

//     for (int i = 0; i < len; i++) {
//         if (stlx != NULL && stack->size > 0) {
//             stlx = stack_pop(stack);
//             print_lexem(*stlx);
//             free(stlx);
//         }
//     }
//     printf("\n");
// }

// void print_lexem(lex lex) {
//     if (lex.type != UNDEFINED)
//         printf("type:%d chr:|%c| num:%5.3lf\n", lex.type, lex.chr, lex.num);
// }
