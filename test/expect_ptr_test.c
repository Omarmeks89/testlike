#include "ctest.h"

int main() {
    int * null_ptr = NULL;
    int * any_addr_ptr = (void *) 0x00ffabef;
    int res = -1;

    EXPECT_EQ_PTR_NULL(null_ptr, "null_ptr_test_1", &res, LINE());
    EXPECT_EQ_PTR_NULL(any_addr_ptr, "null_ptr_test_failed_2", &res, LINE());
    EXPECT_NE_PTR_NULL(any_addr_ptr, "not_null_ptr_3", &res, LINE());
    EXPECT_NE_PTR_NULL(null_ptr, "not_null_ptr_failed_4", &res, LINE());
    return 0;
}
