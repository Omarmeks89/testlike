build: int_test double_test

int_test: ctest.h
	gcc -g -Wall -Wextra -Werror -Wformat -std=c99 -lm test/assert_test.c -o test_int32

double_test: ctest.h
	gcc -g -Wall -Wextra -Werror -Wformat -std=c99 -lm test/assert_dbl_test.c -o test_dbl

clear:
	rm -rf *.o test_*
