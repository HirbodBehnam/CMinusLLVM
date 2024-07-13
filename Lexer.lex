%{
#include "Parser.hpp"
%}

%option outfile="Lexer.cpp" header-file="Lexer.hpp"
%option warn nodefault
%option reentrant noyywrap yylineno
%option bison-bridge

digit         [0-9]
letter        [a-zA-Z]


/* Used https://stackoverflow.com/a/2130124/4213397 */

%x C_COMMENT

%%
";"                  { return SEMICOLON;  }
":"                  { return COLON;      }
","                  { return COMMA;      }
"["                  { return LBRACES;    }
"]"                  { return RBRACES;    }
"("                  { return LPAREN;     }
")"                  { return RPAREN;     }
"{"                  { return LCURVBRACES;}
"}"                  { return RCURVBRACES;}
"+"                  { return PLUS;       }
"-"                  { return MINUS;      }
"*"                  { return TIMES;      }
"="                  { return EQL;        }
"<"                  { return LSS;        }
"=="                 { return DOUBLE_EQ;  }
"if"                 { return IFSYM;      }
"else"               { return ELSESYM;    }
"void"               { return VOIDSYM;    }
"int"                { return INTSYM;     }
"for"                { return FORSYM;     }
"return"             { return RETURNSYM;  }
"endif"              { return ENDIFSYM;   }
"break"              { return BREAKSYM;   }
{letter}({letter}|{digit})* {
                       yylval->id = yytext;
                       return ID;      }
{digit}+             { yylval->num = atoi(yytext);
                       return NUM;     }
[ \t\n\r]            /* skip whitespace */

"/*"                 { BEGIN(C_COMMENT); }
<C_COMMENT>"*/"      { BEGIN(INITIAL); }
<C_COMMENT>\n        { }
<C_COMMENT>.         { }
.                    { printf("Unknown character [%c]\n",yytext[0]); }
%%

int yyerror(yyscan_t scanner, const char *msg) {
    printf("Shash bozorg: %s (token %s line %d)\n", msg, yyget_text(scanner), yyget_lineno(scanner));
    return 0;
}