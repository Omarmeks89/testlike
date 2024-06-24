#include "ctest.h"

int main() {
    int * null_ptr = NULL;
    int * any_addr_ptr = (void *) 0x00ffabef;
    int res = -1;

    EXPECT_EQ_PTR_NULL(null_ptr, null_ptr, null_ptr_test_1, &res, LINE());
    if (res != 1)
        return 1;

    EXPECT_NE_PTR_NULL(any_addr_ptr, any_addr_ptr, not_null_ptr_1, &res, LINE());
    if (res != 1)
        return 1;
    return 0;
}
