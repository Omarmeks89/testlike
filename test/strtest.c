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

void utf8_3bytes_symb_test()
{
    char str[3] = {0xE0, 0xA8, 0x80};
    char curr[3] = {0xE0, 0xA8, 0x80};
    int res = 0, pos = 0;

    res = is_utf8_3byte_symbol(str, curr, &pos, &eq_bytes);
    ASSERT_EQ_INT32(res, 1, "is_3byte_seq", LINE());
    ASSERT_EQ_INT32(pos, 3, "next_pos_after_3byte", LINE());
}

void utf8_3bytes_ne_symb_test()
{
    char str[3] = {0xE0, 0xA8, '\0'};
    char curr[3] = {0xE0, 0xA8, 0x80};
    int res = 0, pos = 0;

    res = is_utf8_3byte_symbol(str, curr, &pos, &eq_bytes);
    ASSERT_EQ_INT32(res, NOTEQS, "3byte_not_equal", LINE());
}

void utf8_4bytes_symb_test()
{
    char str[4] = {0xF0, 0xBF, 0xBF, 0xBF};
    char curr[4] = {0xF0, 0xBF, 0xBF, 0xBF};
    int res = 0, pos = 0;

    res = is_utf8_3byte_symbol(str, curr, &pos, &eq_bytes);
    ASSERT_EQ_INT32(res, 1, "4byte_equal", LINE());
}

void test_utf8_streq_1()
{
    char *smp = "фf";
    char *got = "фf";
    int res = 0;

    res = utf8_streq(smp, got);
    ASSERT_EQ_INT32(res, 2, "utf8_streq_test_1", LINE());
}

void test_utf8_streq_2()
{
    char *smp = "фfF";
    char *got = "фiG";
    int res = 0;

    res = utf8_streq(smp, got);
    ASSERT_EQ_INT32(res, 2, "utf8_streq_test_2", LINE());
}

void test_utf8_streq_3()
{
    char *smp = "фfF";
    char *got = "фfG";
    int res = 0;

    res = utf8_streq(smp, got);
    ASSERT_EQ_INT32(res, 3, "utf8_streq_test_3", LINE());
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
    utf8_3bytes_symb_test();
    utf8_3bytes_ne_symb_test();
    utf8_4bytes_symb_test();

    test_utf8_streq_1();
    test_utf8_streq_2();
    test_utf8_streq_3();
    return 0;
}
