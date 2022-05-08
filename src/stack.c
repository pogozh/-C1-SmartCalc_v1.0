#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

stack_t *stack_init() {
    stack_t *ret;
    ret = (stack_t *)calloc(1, sizeof(stack_t));
    ret->head = NULL;
    ret->size = 0;
    return ret;
}

lex *stack_pop(stack_t *stack, int freeFlag) {
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

    if (freeFlag) retval = NULL;
    return retval;
}

void stack_push(stack_t *stack, lex *new_value) {
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
void stack_free(stack_t *stack) {
    if (stack != NULL) {
        while (stack->size > 0) {
            lex *val2clean = stack_pop(stack, 0);
            free(val2clean);
        }
        free(stack);
    }
}

// LEXEMES UTILS

bool stack_add_new_lex(stack_t *stack, lex new_value) {
    int ret = 0;
    lex *new_lex = (lex *)calloc(1, sizeof(lex));
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

void stack_print(stack_t *stack) {
    printf("!NEW STACK! printing ...\n");
    lex *stlx = stack->head->lexi;
    int len = stack->size;

    for (int i = 0; i < len; i++) {
        if (stlx != NULL && stack->size > 0) {
            stlx = stack_pop(stack, 0);
            print_lexem(*stlx);
            free(stlx);
        }
    }
    printf("\n");
}

void print_lexem(lex lex) {
    printf("type: ");
    switch (lex.type) {
        case NUMBER:
            printf("NUM");
            break;
        case OPERATOR:
            printf("OP");
            break;
        case FUNCTION:
            printf("FNC");
            break;
        case BRACKET:
            printf("BR");
            break;
        case UNDEFINED:
            printf("UND");
            break;
        default:
            printf("N/A");
            break;
    }
    fflush(stdout);
    if (lex.type != UNDEFINED)
        printf(" chr:|%c| num:%5.3lf\n", lex.chr, lex.num);
}
