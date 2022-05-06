#include "utils_suite.h"

#include <check.h>

#include "../calc.h"

START_TEST(first_test) {
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
    // stack_pop(sta, 0);
    stack_print(sta);
    // TODO: leak if 6 !!!
    ck_assert_int_eq(i, 7);
    // stack_free(sta, 1);
}
END_TEST

// START_TEST(second_test) {}
// END_TEST

// START_TEST(unary_test) {}
// END_TEST

// START_TEST(new_test) {}
// END_TEST

Suite *utils_suite(void) {
    Suite *suite = suite_create("utils suite");
    TCase *cases = tcase_create("utils case");

    tcase_add_test(cases, first_test);
    // tcase_add_test(cases, second_test);
    // tcase_add_test(cases, unary_test);

    tcase_set_timeout(cases, 999999);
    suite_add_tcase(suite, cases);

    return suite;
}
