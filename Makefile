C=gcc
FLDEBUG=-g -Wall -Wextra -Werror -Wformat
STD=c89

QUIET?=
ESTRM?=2
MSTRM?=1

SOURCE=testlike.h
OUT_STREAMS=-DESTRM=$(ESTRM) -DMSTRM=$(MSTRM) 

.PHONY: all clean

# $@ -> current target name
all: test test_int test_dbl test_str

test: test_ptr.o
	$(C) -lm -o test_ptr test_ptr.o

test_ptr.o: $(SOURCE) test/expect_ptr_test.c
	$(C) $(FLDEBUG) $(QUIET) $(OUT_STREAMS) -std=$(STD) -c -o $@ test/expect_ptr_test.c 

test_int: test_int.o
	$(C) -lm -o test_int test_int.o

test_int.o: $(SOURCE) test/assert_test.c
	$(C) $(FLDEBUG) $(QUIET) $(OUT_STREAMS) -std=$(STD) -c -o $@ test/assert_test.c

test_dbl: test_dbl.o
	$(C) -lm -o $@ test_dbl.o

test_dbl.o: $(SOURCE) test/assert_dbl_test.c
	$(C) $(FLDEBUG) $(QUIET) $(OUT_STREAMS) -std=$(STD) -c -o $@ test/assert_dbl_test.c

test_str: test_str.o
	$(C) -o $@ test_str.o

test_str.o: $(SOURCE) test/strtest.c
	$(C) $(FLDEBUG) $(QUIET) $(OUT_STREAMS) -std=$(STD) -c -o $@ test/strtest.c

clean:
	rm -rf *.o test_* && clear
