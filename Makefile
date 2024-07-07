FILES = Lexer.c Parser.c main.c
CC = g++
CFLAGS = -g -ansi

compiler: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o compiler

Lexer.c: Lexer.lex
	flex Lexer.lex

Parser.c: Parser.y Lexer.c
	bison Parser.y

clean:
	rm -f *.o *~ Lexer.c Lexer.h Parser.c Parser.h test