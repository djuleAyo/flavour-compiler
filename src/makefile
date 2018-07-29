CC= gcc -g -Wall -Wextra -I../include

TESTS= stack.test pair.test basic_interface.test hash.test

tests: $(TESTS)

sym_table.test: sym_data.c basic_interface.c pair.c hash.c stack.c sym_table.c sym_tableTest.c
	$(CC) -o sym_table.test $^

#this is both unit and integration test so we depend on stack as well
hash.test: pair.c stack.c
	$(CC) -o hash hash.c hashTest.c $^


#%.test: 
#	$(CC) -o $* $*.c $*Test.c

hash.test: 
