#include "utils_suite.h"

#include <check.h>

#include "../calc.h"

START_TEST(stack_test01) {
    // test stack 01
    stack_t *sta = stack_init();
    lex *lex1 = lex_init();
    lex1->type = NUMBER;

    int i = 0;
    for (i = 1; i < 6; i++) {
        lex1->num = (double)i;
        stack_add_new_lex(sta, *lex1);
    }

    printf("\n STACK SIZE %d \n", sta->size);

    stack_print(sta);
    if (sta->size > 0) stack_free(sta, 1);
    // TODO: leak if 6 !!!
    ck_assert_int_eq(i, 64);
}
END_TEST

START_TEST(queue_test01) {
    // test stack 01
    que *qu = queue_init();
    lex *lex1 = lex_init();
    lex1->type = NUMBER;

    int i = 0;
    for (i = 1; i < 6; i++) {
        lex1->num = (double)i;
        queue_add_new_lex(qu, *lex1);
    }

    printf("\n QUEUE SIZE %d \n", qu->size);

    queue_print(qu);
    if (qu->size > 0) queue_free(qu, 1);
    // TODO: leak if 6 !!!
    ck_assert_int_eq(i, 65);
}
END_TEST

Suite *utils_suite(void) {
    Suite *suite = suite_create("utils suite");
    TCase *cases = tcase_create("utils case");

    tcase_add_test(cases, stack_test01);
    tcase_add_test(cases, queue_test01);
    // tcase_add_test(cases, unary_test);

    tcase_set_timeout(cases, 999999);
    suite_add_tcase(suite, cases);

    return suite;
}
