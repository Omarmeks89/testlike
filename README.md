![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

# ctest
utility for testing programs in C.

### version
`v0.0.3a`

### installation
```bash
git clone git@github.com:Omarmeks89/ctest.git
```

You can `cp` ctest.h into your project directory and
include it like "../ctest.h"
or make a softlink and use in by name:
```bash
sudo ln -s $(pwd)/ctest.h /usr/include/ctest.h
```

### build tests

You can compile and run base test:
```bash
make
```

### compiler version and OS
```bash
gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
```

Currently provides several macros for checking return values of type int32 and double64. Usage example:
```C
void test_assert_eq_dbl_success() {
    double exp = 10.0, res = 0.0;
    res = func_that_return_double();
    ASSERT_EQ_DBL(res, exp, DBL_e_2, "wished_test_name", LINE());
}


void test_expect_eq_int32() {
    int exp = 10, res = 0;
    res = func_that_return_int32();
    EXPECT_EQ_INT32(res, exp, "wished_test_name", LINE());
    return 1;
}

int main() {
    test_expect_eq_int32();
    test_assert_eq_dbl_success();
    return 0;
}
```
Below is output example (for double):
```bash
test_assert_eq_dbl_success                                       [EXP.: 10.000000, GOT: 10.000000, EPS.: 0.010000]           PASSED.
test_assert_ne_dbl_passed                                                 [10.011000 != 10.000000. EPS.: 0.010000]           PASSED.
test_expect_eq_dbl_passed                                        [EXP.: 10.010000, GOT: 10.010000, EPS.: 0.010000]           PASSED.
test_expect_ne_dbl_passed                                                 [10.000001 != 10.000000. EPS.: 0.000001]           PASSED.
test_expect_ne_dbl_failed               (LINE 34)                         [10.000001 == 10.000000. EPS.: 0.000001]           FAILED.
```

(for int32):
```bash
test_assert_eq_int32                                                                           [EXP.: 10, GOT: 10]           PASSED.
test_expect_eq_int32                                                                           [EXP.: 10, GOT: 10]           PASSED.
test_expect_ne_int32_passed                                                                              [10 != 8]           PASSED.
test_assert_ne_int32_passed                                                                              [10 != 0]           PASSED.
test_expect_ne_int32_failed             (LINE 31)                                                       [10 == 10]           FAILED.
```

(for pointers):
```bash
test_assert_eq_dbl_success                                       [EXP.: 10.000000, GOT: 10.000000, EPS.: 0.010000]           PASSED.
test_assert_ne_dbl_passed                                                 [10.011000 != 10.000000. EPS.: 0.010000]           PASSED.
test_expect_eq_dbl_passed                                        [EXP.: 10.010000, GOT: 10.010000, EPS.: 0.010000]           PASSED.
test_expect_ne_dbl_passed                                                 [10.000001 != 10.000000. EPS.: 0.000001]           PASSED.
test_expect_ne_dbl_failed               (LINE 34)                         [10.000001 == 10.000000. EPS.: 0.000001]           FAILED.
```

## ABOUT
Minimal utility for simple test cases. Can be integrated directly into code (instead of assert) or used in separate test functions. String comparison (UTF-8) and support for table tests will be added in future versions.

If you use `QUIET=-DQUIET' when compiling tests, only error messages will be output.


It consists of only one header file and does not require third-party libraries. Note that the `math` library is used. Take this into account when compiling tests.

### Usage

`ASSERT` will break execution if testcase failed:
```bash
ASSERT_EQ_INT32(result, expected_value, test_title, line_number);
```

You can use macro `LINE()` to set line number.

```bash
ASSERT_EQ_DBL(result, expected_value, epsilon, test_title, line_number);
```

`ccheck` provide several epsilons:
```C
#define DBL_e_9 1e-9
#define DBL_e_8 1e-8
#define DBL_e_7 1e-7
#define DBL_e_6 1e-6
#define DBL_e_5 1e-5
#define DBL_e_4 1e-4
#define DBL_e_3 1e-3
#define DBL_e_2 1e-2
#define DBL_e_1 1e-1
```

`NE` (not equal) may be useful if you wish to check pointer is not NULL:
```bash
ASSERT_NE_PTR_NULL(pointer, test_title, line_number);
```

`EXPECT` will not break execution and you can see all results. `ASSERT` and `EXPECT`
use the same arguments in same order.
