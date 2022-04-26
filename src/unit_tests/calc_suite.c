#include <check.h>

#include "../calc.h"
#include "../pars.h"

START_TEST(temp) {
    // TEST 1
    int i = 0;
    int j = 0;
    for (; i < 5; ++i) j *= 2;
    i = j;
    ck_assert_int_eq(i, j);
}
END_TEST

START_TEST(First_test) {
    int i = 0;
    ++i;
    ck_assert_uint_eq(calculation("1.34+2.56"), 3);
}
END_TEST

START_TEST(c02_test) {
    int i = 0;
    ++i;
    ck_assert_uint_eq(calculation("-1-sin(0)+(-9.8)"), 2);
}
END_TEST

// START_TEST(temp) {}
// END_TEST

/*_______SUITE_______*/
Suite *calc_suite(void) {
    Suite *suite = suite_create("calc suite");
    TCase *cases = tcase_create("calc case");

    // jdreama
    tcase_add_test(cases, temp);
    tcase_add_test(cases, First_test);
    // tcase_add_test(cases, c02_test);

    // tcase_set_timeout(cases, 9999999);

    suite_add_tcase(suite, cases);
    return suite;
}
