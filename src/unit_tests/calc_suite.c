#include <check.h>
#include <math.h>

#include "../calc.h"
#include "../pars.h"

bool nums_cmp(double num1, double num2) {
    int ret = false;
    if (isnan(num1) && isnan(num2))
        ret = true;
    else if (isinf(num1) && isinf(num2))
        ret = true;
    else
        ret = (fabs((num1 - num2)) < __FLT_EPSILON__);
    return ret;
}

START_TEST(calc_test1) {
    char str[] = "-476567mod693+1/ln(x)+sin(x)+(3-3)*1+3^4^4";
    double x = 18.17;
    double expected =
        -476567 % 693 + 1 / log(x) + sin(x) + (3 - 3) * 1 + pow(3, pow(4, 4));
    que *converted;
    if (str_to_polish(str, &converted)) {
        double result = calculate(converted, x);
        // printf("res = %lf\n", result);
        // printf("exp = %lf\n", expected);
        ck_assert_msg(nums_cmp(result, expected), "exp: %.lf\nres: %.lf",
                      expected, result);
    } else {
        ck_abort_msg("test fail");
    }
    queue_free(converted);
}
END_TEST

START_TEST(calc_test2) {
    char str[] =
        "asin(x+45)+acos(x)/"
        "tan(x)-acos(x-0.122)*asin(x)-atan(x)-sqrt(4)+ln(x)+log(x)+ ln(123^x)";
    double x = 0.170001;
    double expected = asin(x + 45) + acos(x) / tan(x) -
                      acos(x - 0.122) * asin(x) - atan(x) - sqrt(4) + log(x) +
                      log10(x) + log10(pow(12312, x)) + 1;
    que *converted;
    if (str_to_polish(str, &converted)) {
        double result = calculate(converted, x);
        ck_assert_msg(nums_cmp(result, expected), "exp: %f\nres: %f", expected,
                      result);
    } else {
        ck_abort_msg("parse fail");
    }
    queue_free(converted);
}
END_TEST

START_TEST(calc_test3) {
    char str[] = "12+log(10)+12";
    double x = 0.00;
    double expected = 25;
    que *converted;
    if (str_to_polish(str, &converted)) {
        double result = calculate(converted, x);
        printf("res = %.9f\n", result);
        printf("exp = %.9f\n", expected);
        ck_assert_msg(nums_cmp(result, expected), "exp: %f\nres: %f", expected,
                      result);
    } else {
        ck_abort_msg("parse fail");
    }
    queue_free(converted);
}
END_TEST

/*_______SUITE_______*/
Suite *calc_suite(void) {
    Suite *suite = suite_create("calc suite");
    TCase *cases = tcase_create("calc case");

    tcase_add_test(cases, calc_test1);
    tcase_add_test(cases, calc_test2);
    tcase_add_test(cases, calc_test3);

    // tcase_set_timeout(cases, 9999999);

    suite_add_tcase(suite, cases);
    return suite;
}
