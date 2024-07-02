#include <stdio.h>

#include "../ctest.h"

/* try to make crash with a long string */
int test_very_big_string_overflow() {
    int exp = 0, res = 0;
    ASSERT_EQ_INT32(res, exp, "test_assert_eq_dbl_success_gyfueruygrgyuifretrfgufrewthuioeg789543876543gyhufreuvcvghcewtfrevghjrewtffthrewhgvtyytfrevghjcretfcrvgherwjtffghfreuygfrehjfrhgfrg", LINE());
    return 0;
}

int main() {
    test_very_big_string_overflow();
    return 0;
}
