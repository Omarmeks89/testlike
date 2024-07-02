#include "testlike.h"

int main() {
    int * null_ptr = NULL;
    int * any_addr_ptr = (void *) 0x00ffabef;

    ASSERT_EQ_PTR_NULL(null_ptr, "null_ptr_test_1", LINE());
    ASSERT_NE_PTR_NULL(any_addr_ptr, "null_ptr_test_2", LINE());
    EXPECT_EQ_PTR_NULL(null_ptr, "expect_null_ptr_test_3", LINE());
    EXPECT_NE_PTR_NULL(any_addr_ptr, "not_null_ptr_test_4", LINE());
    return 0;
}
