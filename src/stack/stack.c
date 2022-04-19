#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

#define STD_SIZE 64

stack_t create_stack() {
    stack_t stack = {
        .data = NULL,
        .top = -1,
        .size = 0,
    };
    return stack;
}

void stack_delete(stack_t *stack) {
    if (stack->data != NULL) free(stack->data);
    stack = NULL;
    printf("stack deleted\n");
}

bool stack_is_empty(stack_t *stack) {
    bool state;
    if (stack->top < 0) {
        state = true;
    } else {
        state = false;
    }
    printf("stack empty %i\n", state ? true : false);
    return state;
}

status_t stack_push(stack_t *stack, ssize_t item) {
    status_t status = 0;
    // printf("stack pushing ...\n"); debag
    if (stack_is_full(stack)) {
        stack->size = (stack->size + 1) * 2;
        stack->data =
            (ssize_t *)realloc(stack->data, sizeof(ssize_t) * stack->size);
        // printf("stack_ext");  // debag
    } else {
        status = OK;
    }
    stack->top += 1;
    stack->data[stack->top] = item;

    return status;
}

bool stack_is_full(stack_t *stack) {
    bool state;
    if (stack->data == NULL || (stack->top >= stack->size - 1)) {
        state = true;
    } else {
        state = false;
    }
    // printf("stack is full =  %s\n", state ? "true" : "false"); debag
    return state;
}

ssize_t stack_pop(stack_t *stack) {
    if (stack->top > 0) stack->top--;
    return stack->data[stack->top];
}

ssize_t stack_peek(stack_t *stack) { return stack->data[(stack->top)]; }

void stack_print(stack_t *stack) {
    // printf("stack printing ...\n");
    // printf("stack->top = %ld \n", stack->top); //debag
    char *delimetr = "";
    for (int i = 0; i <= stack->top; i++) {
        printf("%s%ld", delimetr, stack->data[i]);
        delimetr = ", ";
    }
    printf("\n");
}
int main() {
    stack_t s = create_stack();
    // stack_push(s, 111);
    stack_print(&s);
    for (int i = 0; i < 5; i++) {
        stack_push(&s, i);
        stack_print(&s);
    }
    printf("!peek top = %li\n", stack_peek(&s));
    for (int i = 0; i < 5; i++) {
        stack_print(&s);
        stack_pop(&s);
    }
    stack_delete(&s);
    return 0;
}
