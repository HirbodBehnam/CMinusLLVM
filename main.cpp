#include "Parser.hpp"
#include "Lexer.hpp"
#include "codegen.hpp"

#include <iostream>

void parse_input(const char *filename) {
    yyscan_t scanner;

    // Open the file
    FILE *input_file = fopen(filename, "r");
    if (input_file == nullptr) {
        std::cerr << "Cannot open file " << filename << std::endl;
        exit(1);
    }

    if (yylex_init(&scanner)) {
        std::cerr << "Shash in init" << std::endl;
        exit(1);
    }

    yyset_in(input_file, scanner);

    // Create the codegen stuff
    CodeGenerator code_generator(scanner);
    yyset_extra(&code_generator, scanner);

    // Parse the input
    if (yyparse(scanner)) {
        std::cerr << "Shash in parse" << std::endl;
        exit(1);
    }

    code_generator.print_code();

    yylex_destroy(scanner);
    fclose(input_file);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Please pass the filename as the first argument." << std::endl;
        return 1;
    }
    parse_input(argv[1]);
    return 0;
}