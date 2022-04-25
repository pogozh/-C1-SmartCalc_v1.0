#include <check.h>

#include "../calc.h"

START_TEST(temp) {
    // TEST 1
    int i = 0;
    int j = 0;
    for (; i < 5; ++i) j *= 2;
    i = j;
    ck_assert_int_eq(i, j);
}

END_TEST

Suite *calc_suite(void) {
    Suite *suite = suite_create("calc suite");
    TCase *cases = tcase_create("calc case");

    // jdreama
    tcase_add_test(cases, temp);

    // tcase_set_timeout(cases, 9999999);

    suite_add_tcase(suite, cases);
    return suite;
}
