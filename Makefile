FILES = Lexer.cpp Parser.cpp codegen.cpp main.cpp
CC = clang++-15
CFLAGS = -g `llvm-config-15 --cxxflags --ldflags --system-libs --libs core`

compiler: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o compiler

Lexer.cpp: Lexer.lex
	flex Lexer.lex

Parser.cpp: Parser.y Lexer.cpp
	bison Parser.y

clean:
	rm -f *.o *~ Lexer.cpp Lexer.hpp Parser.cpp Parser.hpp compiler