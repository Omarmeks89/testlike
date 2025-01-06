#include "testlike.h"

void locale_info_test()
{
    testlike_strcmp_utf8();
}

void test_2byte_utf8_seq()
{
    char example[2] = {0xC2, 0x80};
    char curr[2] = {0xC2, 0x80};
    int res = -1, i = 0;

    res = is_utf8_2byte_symbol(example, curr, &i, &eq_bytes);
    ASSERT_EQ_INT32(res, 1, "test_2utf8_bs_eq", LINE());
    ASSERT_EQ_INT32(i, 2, "check_byte_ptr", LINE());
}

void test_eq_bytes()
{
    int res = 0;
    char sample[1] = {0x7F};
    char curr[1] = {0x80};

    res = eq_bytes(sample, curr);
    ASSERT_EQ_INT32(res, 1, "test_eq_bytes", LINE());
}

int main()
{
    locale_info_test();
    test_2byte_utf8_seq();
    test_eq_bytes();
    return 0;
}
