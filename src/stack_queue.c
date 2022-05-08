#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

que *queue_init() {
    que *ret;
    ret = (que *)calloc(1, sizeof(que));
    ret->tail = NULL;
    ret->size = 0;
    return ret;
}

lex *queue_pop(que *queue) {
    lex *retval = NULL;
    if (queue->size >= 1) {
        queue->size--;
        retval = queue->tail->lexi;
        quEl *trash = queue->tail;

        if (queue->size > 0) {
            queue->tail = queue->tail->next;
            queue->tail->prev = NULL;
        } else {
            queue->tail = NULL;
        }

        free(trash);
    } else {
        retval = NULL;
    }

    return retval;
}

void queue_push(que *queue, lex *new_value) {
    quEl *new_queue_element = (quEl *)calloc(1, sizeof(quEl));
    new_queue_element->lexi = new_value;
    if (queue->size >= 0) {
        if (queue->size > 0) {
            quEl *head = queue->tail;
            while (head->next != NULL) {
                head = head->next;
            }
            head->next = new_queue_element;
        } else {
            queue->tail = new_queue_element;
        }
        queue->size++;
    }
}

void queue_free(que *queue) {
    if (queue != NULL) {
        while (queue->size > 0) {
            lex *val2clean = queue_pop(queue);
            free(val2clean);
        }
        free(queue);
    }
}

// LEXEMES UTILS

bool queue_add_new_lex(que *queue, lex new_value) {
    int ret = 0;
    lex *new_lex = (lex *)calloc(1, sizeof(lex));
    if (new_lex != NULL) {
        new_lex->num = new_value.num;
        new_lex->type = new_value.type;
        new_lex->chr = new_value.chr;
        queue_push(queue, new_lex);
        ret = true;
    } else {
        free(new_lex);
    }

    return ret;
}

void queue_print(que *queue) {
    printf("!NEW QUEUE! printing ...\n");
    lex *stlx = queue->tail->lexi;
    int len = queue->size;
    for (int i = 0; i < len; i++) {
        if (stlx != NULL && queue->size > 0) {
            stlx = queue_pop(queue);
            print_lexem(*stlx);
            free(stlx);
        }
    }
    printf("\n");
}
