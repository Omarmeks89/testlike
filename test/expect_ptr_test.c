#include "ctest.h"

int main() {
    int * null_ptr = NULL;
    int * any_addr_ptr = (void *) 0x00ffabef;

    ASSERT_EQ_PTR_NULL(null_ptr, "null_ptr_test_1", LINE());
    ASSERT_NE_PTR_NULL(any_addr_ptr, "null_ptr_test_failed_2", LINE());
    EXPECT_EQ_PTR_NULL(null_ptr, "null_ptr_test_1", LINE());
    EXPECT_NE_PTR_NULL(any_addr_ptr, "null_ptr_test_failed_2", LINE());
    return 0;
}
