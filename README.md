![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

# ctest
utility for testing programs in C.

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
    double expected = 10.0, res = 0.0;
    res = func_that_return_double();
    ASSERT_EQ_DBL(res, exp_, DBL_e_2, "wished_test_name", LINE());
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
