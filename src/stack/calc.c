#include "calc.h"

int main() {
    // test stack 01
    stack_t s = create_stack();
    // push(s, 111);
    stack_print(&s);
    for (int i = 0; i < 5; i++) {
        push(&s, i);
        stack_print(&s);
    }
    printf("!peek top = %li\n", stack_peek(&s));
    for (int i = 0; i < 5; i++) {
        stack_print(&s);
        pop(&s);
    }
    stack_delete(&s);

    // try calc funx
    stack_t numbers = create_stack();
    // stack_t funtions = create_stack();
    int i;
    while (!feof(stdin)) {
        int c = getchar();
        // int x;
        switch (c) {
            case '\n':
            case ' ':
                break;
            case '=':
                printf("Result = %ld\n", pop(&numbers));
                break;
            case 27:
                goto RESULT;
            case '+':
                push(&numbers, pop(&numbers) + pop(&numbers));
                break;
            case '-':
                push(&numbers, -pop(&numbers) + pop(&numbers));
                break;
            case '*':
                push(&numbers, pop(&numbers) * pop(&numbers));
                break;
                // default:
                //     ungetc(c, stdin);
                //     if (scanf("%d", &x) != 1) {
                //         fprintf(stderr, "Can't read integer\n");
                //         return -1;
                //     } else {
                //         push();
                //     }
                //     break;
        }
    }
RESULT:
    i = 0;
    while (!stack_is_empty(&numbers)) {
        printf("Stack[%d] = %ld\n", i, pop(&numbers));
        i++;
    }

    // stack_delete(&funtions);
    stack_delete(&numbers);
    return 0;
}
