#include "Parser.h"
#include "Lexer.h"

#include <stdio.h>

void parse_input(const char *filename) {
    yyscan_t scanner;

    // Open the file
    FILE *input_file = fopen(filename, "r");
    if (input_file == NULL) {
        printf("Cannot open file %s\n", filename);
        exit(1);
    }

    if (yylex_init(&scanner)) {
        puts("Shash in init");
        exit(1);
    }

    yyset_in(input_file, scanner);

    if (yyparse(scanner)) {
        puts("Shash in parse");
        exit(1);
    }

    yylex_destroy(scanner);
    fclose(input_file);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        puts("Please pass the filename as the first argument.");
        return 1;
    }
    parse_input(argv[1]);
    return 0;
}