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

void test_2byte_utf8_seq_2()
{
    char *example = "а";
    char *curr = "а";
    int res = -1, i = 0;

    res = is_utf8_2byte_symbol(example, curr, &i, &eq_bytes);
    ASSERT_EQ_INT32(res, 1, "test_2utf8_russian", LINE());
}

void test_detect_utf16_surrogate()
{
    char example[2] = {0xDF, 0x00};
    char curr[2] = {0xDF, 0x00};
    int res = -1, i = 0;

    res = is_utf8_2byte_symbol(example, curr, &i, &eq_bytes);
    ASSERT_EQ_INT32(res, NOTUTF, "test_utf16_is_notutf8", LINE());
}

void test_eq_bytes()
{
    int res = 0;
    char sample[1] = {0x7F};
    char curr[1] = {0x80};
    char valid_curr[1] = {0x7F};

    res = eq_bytes(sample, curr);
    ASSERT_EQ_INT32(res, 1, "test_eq_bytes", LINE());

    res = eq_bytes(sample, valid_curr);
    ASSERT_EQ_INT32(res, 0, "test_eq_valid_bytes", LINE());
}

void test_2byte_utf8_ne()
{
    char example[2] = {0xC2, 0xBF};
    char curr[2] = {0xC2, 0x80};
    int res = -1, i = 0;

    res = is_utf8_2byte_symbol(example, curr, &i, &eq_bytes);
    ASSERT_EQ_INT32(res, NOTEQS, "test_2utf8_bs_not_equal", LINE());
}

/** test check that we can encode
 * valid UTF* symbol from bytes
 */
void utf8_encoder_test()
{
    char str[3] = {0xE0, 0xA8, 0x80};
    char curr[3] = {0xE0, 0xA8, 0x80};
    int res = 0;
    wchar_t symb = 0;

    res = encode_utf8_symbol(str, curr, &symb, 3, &eq_bytes);
    ASSERT_EQ_INT32(res, 0, "encode_3byte_seq", LINE());

    if (symb != 0xE0A880)
        res = 1;

    ASSERT_EQ_INT32(res, 0, "check_encoded_3byte_seq", LINE());
}

void utf8_encoder_noteqs_test()
{
    char str[3] = {0xE0, 0xA8, 0x80};
    char curr[3] = {0xE0, 0xA0, 0x80};
    int res = 0;
    wchar_t symb = 0;

    res = encode_utf8_symbol(str, curr, &symb, 3, &eq_bytes);
    ASSERT_EQ_INT32(res, NOTEQS, "3byte_seq_ne", LINE());
}

int main()
{
    locale_info_test();
    test_2byte_utf8_seq();
    test_eq_bytes();
    test_detect_utf16_surrogate();
    test_2byte_utf8_ne();
    test_2byte_utf8_seq_2();
    
    utf8_encoder_test();
    utf8_encoder_noteqs_test();
    return 0;
}
