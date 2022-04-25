#include "utils_suite.h"

#include <check.h>

#include "../calc.h"

START_TEST(first_test) {
    // test stack 01
    stack_t stack = create_stack();
    // push(s, 111);
    int i = 0, j = 5;
    stack_print(&stack);
    for (int i = 0; i < 5; i++) {
        push(&stack, i);
        // stack_print(&stack); //db
    }
    // printf("!peek top = %f\n", stack_peek(&stack));
    for (; i < 5; i++) {
        // stack_print(&stack);  //db
        pop(&stack);
    }
    pop(&stack);

    ck_assert_int_eq(i, j);
    stack_delete(&stack);
}
END_TEST

START_TEST(second_test) {
    // parser subtest01
    stack_t oper = create_stack();
    stack_print(&oper);
    for (int i = 0; i < 10; i++) {
        push(&oper, i * 100);
        // stack_print(&oper); //bd
    }
    printf("peek top = %5.2f\n", stack_peek(&oper));
    for (int i = 0; i < 10; i++) {
        printf("%d ", oper_priority(oper));
        pop(&oper);
    }
    stack_delete(&oper);

    // subtest02
    oper = create_stack();
    stack_print(&oper);

    // pushing operators
    push(&oper, SIN);
    push(&oper, COS);
    push(&oper, ASIN);
    push(&oper, ASIN);
    push(&oper, TAN);
    push(&oper, ATAN);
    push(&oper, SQRT);
    push(&oper, LOG);
    push(&oper, LN);
    push(&oper, POW);
    push(&oper, MOD);
    push(&oper, MUL);
    push(&oper, DEF);
    push(&oper, PLUS);
    push(&oper, MINUS);
    push(&oper, CLOSE_BRACKET);
    push(&oper, OPEN_BRACKET);

    printf("peek top = %5.2f\n", stack_peek(&oper));
    while (oper.top != 0) {
        printf("%d ", oper_priority(oper));
        pop(&oper);
    }

    printf("\n___________________________________________\n");
    stack_delete(&oper);
}
END_TEST

// START_TEST(new_test) {}
// END_TEST

Suite *utils_suite(void) {
    Suite *suite = suite_create("utils suite");
    TCase *cases = tcase_create("utils case");

    tcase_add_test(cases, first_test);
    tcase_add_test(cases, second_test);

    tcase_set_timeout(cases, 999999);
    suite_add_tcase(suite, cases);

    return suite;
}