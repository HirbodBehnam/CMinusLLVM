%{
#include "Parser.hpp"
#include "Lexer.hpp"
#include "codegen.hpp"

int yyerror(yyscan_t scanner, const char *msg);

#define GET_CODEGEN() static_cast<CodeGenerator *>(yyget_extra(scanner))

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
Global-Declaration-initial: Global-Type-specifier ID __declaring_pid ;
Global-Declaration-prime: Fun-declaration-prime | Var-declaration-prime ;
Var-declaration-prime: LBRACES NUM __immediate RBRACES SEMICOLON { GET_CODEGEN()->array_declared(); }
                     | SEMICOLON                                 { GET_CODEGEN()->variable_declared(); }
                     ;
Fun-declaration-prime: __function_start LPAREN Params RPAREN __function_params_end Compound-stmt __function_end ;
Global-Type-specifier: INTSYM  __int_type
                     | VOIDSYM __void_type
                     ;
Params: INTSYM ID __declaring_pid Param-prime Param-list | VOIDSYM ;
Param-list: COMMA Param Param-list | ;
Param: INTSYM ID __declaring_pid Param-prime ;
Param-prime: LBRACES RBRACES { GET_CODEGEN()->array_param(); }
           |                 { GET_CODEGEN()->int_param(); }
           ;
Local-Declaration-list: Local-Declaration Local-Declaration-list | ;
Local-Declaration: INTSYM __int_type ID __declaring_pid Var-declaration-prime ;
Compound-stmt: LCURVBRACES Local-Declaration-list Statement-list RCURVBRACES ;
Statement-list: Statement Statement-list | ;
Statement: Expression-stmt | Compound-stmt | Selection-stmt | Iteration-stmt | Return-stmt ;
Expression-stmt: Expression SEMICOLON __pop_expression
               | BREAKSYM SEMICOLON
               | SEMICOLON ;
Selection-stmt: IFSYM LPAREN Expression RPAREN Statement Else-stmt ;
Else-stmt: ENDIFSYM | ELSESYM Statement ENDIFSYM ;
Iteration-stmt: FORSYM LPAREN Expression SEMICOLON Expression SEMICOLON Expression RPAREN Statement ;
Return-stmt: RETURNSYM Return-stmt-prime ;
Return-stmt-prime: SEMICOLON            { GET_CODEGEN()->insert_return(true); }
                 | Expression SEMICOLON { GET_CODEGEN()->insert_return(false); }
                 ;
Expression: Simple-expression-zegond | ID __pid B ;
B: EQL Expression __assign
 | LBRACES Expression RBRACES __array H
 | Simple-expression-prime
 ;
H: EQL Expression __assign
 | G D C ;
Simple-expression-zegond: Additive-expression-zegond C ;
Simple-expression-prime: Additive-expression-prime C ;
C: Relop Additive-expression __calculate | ;
Relop: __save_operator LSS | __save_operator DOUBLE_EQ ;
Additive-expression: Term D ;
Additive-expression-prime: Term-prime D ;
Additive-expression-zegond: Term-zegond D ;
D: Addop Term __calculate D | ;
Addop: __save_operator PLUS | __save_operator MINUS ;
Term: Signed-factor G ;
Term-prime: Signed-factor-prime G ;
Term-zegond: Signed-factor-zegond G ;
G: __save_operator TIMES Signed-factor __calculate G | ;
Signed-factor: PLUS Factor | MINUS Factor __negate | Factor ;
Signed-factor-prime: Factor-prime ;
Signed-factor-zegond: PLUS Factor | MINUS Factor | Factor-zegond ;
Factor: LPAREN Expression RPAREN | ID __pid Var-call-prime | NUM __immediate_val ;
Var-call-prime: LPAREN Args RPAREN __call | Var-prime ;
Var-prime: LBRACES Expression RBRACES __array | ;
Factor-prime: LPAREN Args RPAREN __call | ;
Factor-zegond: LPAREN Expression RPAREN | NUM __immediate_val ;
Args: Arg-list | ;
Arg-list: Expression Arg-list-prime ;
Arg-list-prime: COMMA Expression Arg-list-prime | ;

__declaring_pid: { GET_CODEGEN()->declaring_pid(yylval.id); } ;
__immediate: { GET_CODEGEN()->immediate(yylval.num); } ;
__int_type: { GET_CODEGEN()->int_type(); } ;
__void_type: { GET_CODEGEN()->void_type(); } ;
__function_start: { GET_CODEGEN()->function_start(); } ;
__function_params_end: { GET_CODEGEN()->function_params_end(); } ;
__function_end: { GET_CODEGEN()->function_end(); };
__pid: { GET_CODEGEN()->pid(yylval.id); } ;
__pop_expression: { GET_CODEGEN()->pop_expression(); } ;
__assign: { GET_CODEGEN()->assign(); } ;
__array: { GET_CODEGEN()->array(); } ;
__immediate_val: { GET_CODEGEN()->immediate_val(yylval.num); } ;
__save_operator: { GET_CODEGEN()->save_operator(static_cast<CodeGenerator::Operator>(yychar)); } ;
__negate: { GET_CODEGEN()->negate(); } ;
__calculate: { GET_CODEGEN()->calculate(); } ;
__call: { GET_CODEGEN()->call(); } ;
%%