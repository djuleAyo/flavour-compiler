CC= gcc -g -pg -Wall -Wextra -Iinclude

SRC= $(shell ls src/*.c)
OBJECTS= $(shell ls src/*.c | sed s/src/build/ | sed s/[.]c/.o/)
TESTS= $(shell ls test/*Test.c)

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
	lex $^

#tests##################################
test-%: $(OBJECTS) test/%Test.o
	$(CC) -o test/$* $^

test/%Test.o: test/%Test.c 
	$(CC) -c -o test/$*Test.o -MMD $^
	
-include $(OBJECTS:.o=.d)
-include $(TESTS:.c=.d)
-include lex.yy.d
-include parser.tab.d
.PHONY: clean

clean:
	rm ./**/*.[od] ./**/a.out flavour parser.tab.*  ./**/*~ lex.yy.* build/* parser.output
