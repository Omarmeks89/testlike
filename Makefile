C=gcc
FLDEBUG=-g -Wall -Wextra -Werror -Wformat
STD=c89

# from cli
QUIET?=

SOURCE=ctest.h

build: int_test double_test ptr_test crash_test

ptr_test: $(SOURCE)
	$(C) $(FLDEBUG) $(QUIET) -std=$(STD) -lm test/expect_ptr_test.c -o test_ptr

int_test: $(SOURCE)
	$(C) $(FLDEBUG) $(QUIET) -std=$(STD) -lm test/assert_test.c -o test_int32

double_test: $(SOURCE)
	$(C) $(FLDEBUG) $(QUIET) -std=$(STD) -lm test/assert_dbl_test.c -o test_dbl

crash_test: $(SOURCE)
	$(C) $(FLDEBUG) $(QUIET) -std=$(STD) -lm test/crash_test.c -o test_crash

clear:
	rm -rf *.o test_*
