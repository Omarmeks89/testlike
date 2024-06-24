# for WF
build: int_test double_test ptr_test

ptr_test: ctest.h
	gcc -g -Wall -Wextra -Werror -Wformat -std=c89 -lm test/expect_ptr_test.c -o test_ptr

int_test: ctest.h
	gcc -g -Wall -Wextra -Werror -Wformat -std=c89 -lm test/assert_test.c -o test_int32

double_test: ctest.h
	gcc -g -Wall -Wextra -Werror -Wformat -std=c89 -lm test/assert_dbl_test.c -o test_dbl

clear:
	rm -rf *.o test_*
