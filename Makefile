FILES = Lexer.cpp Parser.cpp main.cpp
CC = g++
CFLAGS = -g -ansi

compiler: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o compiler

Lexer.cpp: Lexer.lex
	flex Lexer.lex

Parser.cpp: Parser.y Lexer.cpp
	bison Parser.y

clean:
	rm -f *.o *~ Lexer.cpp Lexer.hpp Parser.cpp Parser.hpp compiler