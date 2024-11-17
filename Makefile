C=gcc
FLDEBUG=-g -Wall -Wextra -Werror -Wformat
STD=c89

QUIET?=
ESTRM?=2
MSTRM?=1

SOURCE=testlike.h
OUT_STREAMS=-DESTRM=$(ESTRM) -DMSTRM=$(MSTRM) 

build: int_test double_test ptr_test str_test

ptr_test: $(SOURCE)
	$(C) $(FLDEBUG) $(QUIET) $(OUT_STREAMS) -std=$(STD) -lm test/expect_ptr_test.c -o test_ptr

int_test: $(SOURCE)
	$(C) $(FLDEBUG) $(QUIET) $(OUT_STREAMS) -std=$(STD) -lm test/assert_test.c -o test_int32

double_test: $(SOURCE)
	$(C) $(FLDEBUG) $(QUIET) $(OUT_STREAMS) -std=$(STD) -lm test/assert_dbl_test.c -o test_dbl

str_test: $(SOURCE)
	$(C) $(FLDEBUG) $(QUIET) $(OUT_STREAMS) -std=$(STD) test/strtest.c -o string_test

clear:
	rm -rf *.o test_*
