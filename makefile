CC= gcc -g -pg -Wall -Wextra -Iinclude

SRC= $(shell ls src/*.c | sed s/.*Test.c//)

#redosled liste zavisnosti je bitan
flavour: $(SRC:build=src,.c=.o) parser.tab.o lex.yy.o
	$(CC) -o $@ $^

src/%.o: src/%.c
	$(CC) -c $^ -o build/$*.o

#parser.tab.o:	parser.tab.c
#	$(CC) -c $^

parser.tab.c: parser.y
	bison -d -v $^

#lex.yy.o: lex.yy.c
#	$(CC) -c $^

lex.yy.c: lex.lex
	flex $^


.PHONY: clean

clean:
	rm *.o a.out flavour parser.tab.*  *~ lex.yy.* gmon.out parser.output *TAGS GPATH
