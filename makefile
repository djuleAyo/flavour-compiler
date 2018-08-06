CC= gcc -g -pg -Wall -Wextra -Iinclude

SRC= $(shell ls src/*.c)
OBJECTS= $(shell ls src/*.c | sed s/src/build/ | sed s/[.]c/.o/)
TESTS= $(shell ls test/*Test.c)
MODULES= $(shell cd src; ls *.c | sed s/[.]c/.d/)

flavour: $(OBJECTS) parser.tab.o lex.yy.o
	$(CC) $^ -o flavour

compile: $(OBJECTS)

build/%.o : src/%.c
	$(CC) -c -o build/$*.o $< -MMD

parser.tab.o: parser.tab.c
	$(CC) -c -MMD $^

parser.tab.c: parser.y
	bison $^ -d -v

lex.yy.o: lex.yy.c
	$(CC) -c -MMD $^

lex.yy.c: lex.lex
	flex $^

#tests##################################
test-%: test/%Test.o
	python ./compile-dependencies.py $*

test/%Test.o: test/%Test.c
	$(CC) -c -MMD $^

#module################################
module-%:
	touch include/$*.h
	echo \#ifndef _$*_H > include/$*.h
	echo \#define _$*_H >> include/$*.h
	echo \#endif >> include/$*.h

	touch src/$*.c
	echo \#include \"$*.h\" > src/$*.c
	echo \#include \"flavour.h\" >> src/$*.c
	touch test/$*Test.c
	echo \#include \"$*.h\" > test/$*Test.c
	echo int main\(\) {} >> test/$*Test.c




-include $(OBJECTS:.o=.d)
-include $(TESTS:.c=.d)
-include lex.yy.d
-include parser.tab.d
.PHONY: clean

clean:
	rm ./**/*.[od] ./**/a.out flavour parser.tab.*  ./**/*~ lex.yy.* build/* parser.output ./**/*.gch *.[do] *~ ./**/*.d1 GPATH GTAGS GRTAGS
