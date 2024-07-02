#include <stdio.h>

#include "testlike.h"

int test_LINE_macro_success() {
    int exp = __LINE__, res = LINE();
    ASSERT_EQ_INT32(res, exp, "test_LINE_macro_success", LINE());
    return 1;
}

int test_assert_eq_int32() {
    int exp = 10, res = 10;
    ASSERT_EQ_INT32(res, exp, "test_assert_eq_int32", LINE());
    return 1;
}

int test_expect_eq_int32() {
    int exp = 10, res = 10;
    EXPECT_EQ_INT32(res, exp, "test_expect_eq_int32", LINE());
    return 0;
}

int test_expect_ne_int32_passed() {
    int exp = 10, res = 8;
    EXPECT_NE_INT32(res, exp, "test_expect_ne_int32_passed", LINE());
    return 0;
}

int test_expect_ne_int32_failed() {
    int exp = 10, res = 10;
    EXPECT_NE_INT32(res, exp, "test_expect_ne_int32_failed", LINE());
    return 0;
}

int test_assert_ne_int32_passed() {
    int exp = 10, res = 0;
    ASSERT_NE_INT32(res, exp, "test_assert_ne_int32_passed", LINE());
    return 1;
}

int main() {
    test_LINE_macro_success();
    test_assert_eq_int32();
    test_expect_eq_int32();
    test_expect_ne_int32_passed();
    test_assert_ne_int32_passed();
    test_expect_ne_int32_failed();
    return 0;
}
