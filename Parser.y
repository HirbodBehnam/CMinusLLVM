%{

#include "Parser.hpp"
#include "Lexer.hpp"

int yyerror(yyscan_t scanner, const char *msg);

%}

%code requires {
  typedef void* yyscan_t;
}

%require "3.2"
%output  "Parser.cpp"
%defines "Parser.hpp"

%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { yyscan_t scanner }

%union {
    int num;
    char *id;
}

%token SEMICOLON    ";"
%token COLON        ":"
%token COMMA        ","
%token LBRACES      "["
%token RBRACES      "]"
%token LPAREN       "("
%token RPAREN       ")"
%token LCURVBRACES  "{"
%token RCURVBRACES  "}"
%token PLUS         "+"
%token MINUS        "-"
%token TIMES        "*"
%token EQL          "="
%token LSS          "<"
%token DOUBLE_EQ    "=="
%token IFSYM        "if"
%token ELSESYM      "else"
%token VOIDSYM      "void"
%token INTSYM       "int"
%token FORSYM       "for"
%token RETURNSYM    "return"
%token ENDIFSYM     "endif"
%token BREAKSYM     "break"
%token <num> NUM
%token <id> ID

%%

Program: Global-Declaration-list ;
Global-Declaration-list: Global-Declaration Global-Declaration-list | ;
Global-Declaration: Global-Declaration-initial Global-Declaration-prime ;
Global-Declaration-initial: Global-Type-specifier ID ;
Global-Declaration-prime: Fun-declaration-prime | Var-declaration-prime ;
Var-declaration-prime: LBRACES NUM RBRACES SEMICOLON | SEMICOLON ;
Fun-declaration-prime: LPAREN Params RPAREN Compound-stmt ;
Global-Type-specifier: INTSYM | VOIDSYM ;
Params: INTSYM ID Param-prime Param-list | VOIDSYM ;
Param-list: COMMA Param Param-list | ;
Param: INTSYM ID Param-prime ;
Param-prime: LBRACES RBRACES | ;
Local-Declaration-list: Local-Declaration Local-Declaration-list | ;
Local-Declaration: INTSYM ID Var-declaration-prime ;
Compound-stmt: LCURVBRACES Local-Declaration-list Statement-list RCURVBRACES ;
Statement-list: Statement Statement-list | ;
Statement: Expression-stmt | Compound-stmt | Selection-stmt | Iteration-stmt | Return-stmt ;
Expression-stmt: Expression SEMICOLON | BREAKSYM SEMICOLON | SEMICOLON ;
Selection-stmt: IFSYM LPAREN Expression RPAREN Statement Else-stmt ;
Else-stmt: ENDIFSYM | ELSESYM Statement ENDIFSYM ;
Iteration-stmt: FORSYM LPAREN Expression SEMICOLON Expression SEMICOLON Expression RPAREN Statement ;
Return-stmt: RETURNSYM Return-stmt-prime ;
Return-stmt-prime: SEMICOLON | Expression SEMICOLON ;
Expression: Simple-expression-zegond | ID B ;
B: EQL Expression | LBRACES Expression RBRACES H | Simple-expression-prime ;
H: EQL Expression | G D C ;
Simple-expression-zegond: Additive-expression-zegond C ;
Simple-expression-prime: Additive-expression-prime C ;
C: Relop Additive-expression | ;
Relop: LSS | DOUBLE_EQ ;
Additive-expression: Term D ;
Additive-expression-prime: Term-prime D ;
Additive-expression-zegond: Term-zegond D ;
D: Addop Term D | ;
Addop: PLUS | MINUS ;
Term: Signed-factor G ;
Term-prime: Signed-factor-prime G ;
Term-zegond: Signed-factor-zegond G ;
G: TIMES Signed-factor G | ;
Signed-factor: PLUS Factor | MINUS Factor | Factor ;
Signed-factor-prime: Factor-prime ;
Signed-factor-zegond: PLUS Factor | MINUS Factor | Factor-zegond ;
Factor: LPAREN Expression RPAREN | ID Var-call-prime | NUM ;
Var-call-prime: LPAREN Args RPAREN | Var-prime ;
Var-prime: LBRACES Expression RBRACES | ;
Factor-prime: LPAREN Args RPAREN | ;
Factor-zegond: LPAREN Expression RPAREN | NUM ;
Args: Arg-list | ;
Arg-list: Expression Arg-list-prime ;
Arg-list-prime: COMMA Expression Arg-list-prime | ;

%%