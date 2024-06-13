# ctest
utility for testing programs in C (and C++ a bit later).

Currently provides several macros for checking return values of type int32 and double64. Usage example:
```C
int test_assert_eq_dbl_success() {
    double exp_ = 10.0, res = 10.0;
    ASSERT_EQ_DBL(res, exp_, DBL_e_2, test_assert_eq_dbl_success, LINE());
    return 0;
}


int test_assert_eq_int32() {
    int exp = 10, res = 10;
    ASSERT_EQ_INT32(res, exp, test_assert_eq_int32, LINE());
    return 1;
}
```
There is an exmaple of simple test scenario.

You can set expected value, name of function, line number and floating point values precision.

Macros with prefix `ASSERT` will abort execution if testcase failed.
Macros with prefix `EXPECT` will continue execution.
Marcos `LINE` will return current line in file.

Also `ctest.h` provide several epsilons for using with floating point values.

Below is an example of tests execution and test messages on success and on fail:
```bash
test_assert_eq_dbl_success       [EXPECTED:  10.000000, GOT:  10.000000, EPS.: 0.010000000]  PASSED.
test_assert_ne_dbl_passed        [EXPECTED:  10.011000, GOT:  10.000000, EPS.: 0.010000000]  PASSED.
test_expect_eq_dbl_passed        [EXPECTED:  10.010000, GOT:  10.010000, EPS.: 0.010000000]  PASSED.
test_expect_ne_dbl_passed        [EXPECTED:  10.000001, GOT:  10.000000, EPS.: 0.000001000]  PASSED.
test_expect_ne_dbl_failed        (LINE:     43) [EXPECTED:  10.000001, GOT:  10.000000, EPS.: 0.000001000]  FAILED.
test_assert_ne_dbl_failed        (LINE:     19) [EXPECTED:  10.001000, GOT:  10.000000, EPS.: 0.010000000]  FAILED.
```

Next one (for int32 values):
```bash
test_LINE_macro_success          [EXPECTED:        6, GOT:        6]                          PASSED.
test_assert_eq_int32             [EXPECTED:       10, GOT:       10]                          PASSED.
test_expect_eq_int32             [EXPECTED:       10, GOT:       10]                          PASSED.
test_expect_ne_int32_passed      [EXPECTED:       10, GOT:        8]                          PASSED.
test_assert_ne_int32_passed      [EXPECTED:       10, GOT:        0]                          PASSED.
test_expect_ne_int32_failed      (LINE:     33) [EXPECTED:       10, GOT:       10]                          FAILED.
test_assert_ne_int32_failed      (LINE:     45) [EXPECTED:       10, GOT:       10]                          FAILED.
```

### compiler version and OS
```bash
gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
Copyright (C) 2021 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### tests

You can compile and run base test:
```bash
make
```

