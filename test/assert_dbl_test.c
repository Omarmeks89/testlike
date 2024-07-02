#include <stdio.h>

#include "testlike.h"

int test_assert_eq_dbl_success() {
    double exp_ = 10.0, res = 10.0;
    ASSERT_EQ_DBL(res, exp_, DBL_e_2, "test_assert_eq_dbl_success", LINE());
    return 0;
}

int test_assert_ne_dbl_passed() {
    double exp_ = 10.011, res = 10.00;
    ASSERT_NE_DBL(res, exp_, DBL_e_2, "test_assert_ne_dbl_passed", LINE());
    return 0;
}

int test_expect_eq_dbl_passed() {
    double exp_ = 10.01, res = 10.01;

    EXPECT_EQ_DBL(res, exp_, DBL_e_2, "test_expect_eq_dbl_passed", LINE());
    return 0;
}

int test_expect_ne_dbl_passed() {
    double exp_ = 10.0000010001, res = 10.000000;

    EXPECT_NE_DBL(res, exp_, DBL_e_6, "test_expect_ne_dbl_passed", LINE());
    return 0;
}

int test_expect_ne_dbl_failed() {
    double exp_ = 10.000001, res = 10.000000;

    EXPECT_NE_DBL(res, exp_, DBL_e_6, "test_expect_ne_dbl_failed", LINE());
    return 0;
}

int main() {
    test_assert_eq_dbl_success();
    test_assert_ne_dbl_passed();
    test_expect_eq_dbl_passed();
    test_expect_ne_dbl_passed();
    test_expect_ne_dbl_failed();
    return 0;
}
