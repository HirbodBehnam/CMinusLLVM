n=\e[0m
g=\e[1;32m

FILES = Lexer.cpp Parser.cpp codegen.cpp main.cpp
CC = clang++-15
CFLAGS = `llvm-config-15 --cxxflags --ldflags --system-libs --libs core` -std=c++17 -ggdb -O0

all: $(FILES)
	$(CC) $(CFLAGS) $(FILES) -o compiler

Lexer.cpp: Lexer.lex
	flex Lexer.lex

Parser.cpp: Parser.y Lexer.cpp
	bison Parser.y

clean:
	rm -f *.o *~ Lexer.cpp Lexer.hpp Parser.cpp Parser.hpp compiler

verify:
	./compiler input.txt output.ll
	clang-15 output.ll
	./a.out > output.txt || true
	diff --strip-trailing-cr -u output.txt expected.txt 1>&2

verify-all: all
	for test in tests/*; do		\
		echo "TESTING $$test";	\
		cp $$test/* .;			\
		make verify || exit 1;	\
	done;						\
	echo "$gAll tests passed!$n";