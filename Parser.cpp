/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "Parser.y"

#include "Parser.hpp"
#include "Lexer.hpp"
#include "codegen.hpp"

int yyerror(yyscan_t scanner, const char *msg);

#define GET_CODEGEN() static_cast<CodeGenerator *>(yyget_extra(scanner))


#line 82 "Parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "Parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* ";"  */
  YYSYMBOL_COLON = 4,                      /* ":"  */
  YYSYMBOL_COMMA = 5,                      /* ","  */
  YYSYMBOL_LBRACES = 6,                    /* "["  */
  YYSYMBOL_RBRACES = 7,                    /* "]"  */
  YYSYMBOL_LPAREN = 8,                     /* "("  */
  YYSYMBOL_RPAREN = 9,                     /* ")"  */
  YYSYMBOL_LCURVBRACES = 10,               /* "{"  */
  YYSYMBOL_RCURVBRACES = 11,               /* "}"  */
  YYSYMBOL_PLUS = 12,                      /* "+"  */
  YYSYMBOL_MINUS = 13,                     /* "-"  */
  YYSYMBOL_TIMES = 14,                     /* "*"  */
  YYSYMBOL_EQL = 15,                       /* "="  */
  YYSYMBOL_LSS = 16,                       /* "<"  */
  YYSYMBOL_DOUBLE_EQ = 17,                 /* "=="  */
  YYSYMBOL_IFSYM = 18,                     /* "if"  */
  YYSYMBOL_ELSESYM = 19,                   /* "else"  */
  YYSYMBOL_VOIDSYM = 20,                   /* "void"  */
  YYSYMBOL_INTSYM = 21,                    /* "int"  */
  YYSYMBOL_FORSYM = 22,                    /* "for"  */
  YYSYMBOL_RETURNSYM = 23,                 /* "return"  */
  YYSYMBOL_ENDIFSYM = 24,                  /* "endif"  */
  YYSYMBOL_BREAKSYM = 25,                  /* "break"  */
  YYSYMBOL_NUM = 26,                       /* NUM  */
  YYSYMBOL_ID = 27,                        /* ID  */
  YYSYMBOL_YYACCEPT = 28,                  /* $accept  */
  YYSYMBOL_Program = 29,                   /* Program  */
  YYSYMBOL_30_Global_Declaration_list = 30, /* Global-Declaration-list  */
  YYSYMBOL_31_Global_Declaration = 31,     /* Global-Declaration  */
  YYSYMBOL_32_Global_Declaration_initial = 32, /* Global-Declaration-initial  */
  YYSYMBOL_33_Global_Declaration_prime = 33, /* Global-Declaration-prime  */
  YYSYMBOL_34_Var_declaration_prime = 34,  /* Var-declaration-prime  */
  YYSYMBOL_35_Fun_declaration_prime = 35,  /* Fun-declaration-prime  */
  YYSYMBOL_36_Global_Type_specifier = 36,  /* Global-Type-specifier  */
  YYSYMBOL_Params = 37,                    /* Params  */
  YYSYMBOL_38_Param_list = 38,             /* Param-list  */
  YYSYMBOL_Param = 39,                     /* Param  */
  YYSYMBOL_40_Param_prime = 40,            /* Param-prime  */
  YYSYMBOL_41_Local_Declaration_list = 41, /* Local-Declaration-list  */
  YYSYMBOL_42_Local_Declaration = 42,      /* Local-Declaration  */
  YYSYMBOL_43_Compound_stmt = 43,          /* Compound-stmt  */
  YYSYMBOL_44_Statement_list = 44,         /* Statement-list  */
  YYSYMBOL_Statement = 45,                 /* Statement  */
  YYSYMBOL_46_Expression_stmt = 46,        /* Expression-stmt  */
  YYSYMBOL_47_Selection_stmt = 47,         /* Selection-stmt  */
  YYSYMBOL_48_Else_stmt = 48,              /* Else-stmt  */
  YYSYMBOL_49_Iteration_stmt = 49,         /* Iteration-stmt  */
  YYSYMBOL_50_Return_stmt = 50,            /* Return-stmt  */
  YYSYMBOL_51_Return_stmt_prime = 51,      /* Return-stmt-prime  */
  YYSYMBOL_Expression = 52,                /* Expression  */
  YYSYMBOL_B = 53,                         /* B  */
  YYSYMBOL_H = 54,                         /* H  */
  YYSYMBOL_55_Simple_expression_zegond = 55, /* Simple-expression-zegond  */
  YYSYMBOL_56_Simple_expression_prime = 56, /* Simple-expression-prime  */
  YYSYMBOL_C = 57,                         /* C  */
  YYSYMBOL_Relop = 58,                     /* Relop  */
  YYSYMBOL_59_Additive_expression = 59,    /* Additive-expression  */
  YYSYMBOL_60_Additive_expression_prime = 60, /* Additive-expression-prime  */
  YYSYMBOL_61_Additive_expression_zegond = 61, /* Additive-expression-zegond  */
  YYSYMBOL_D = 62,                         /* D  */
  YYSYMBOL_Addop = 63,                     /* Addop  */
  YYSYMBOL_Term = 64,                      /* Term  */
  YYSYMBOL_65_Term_prime = 65,             /* Term-prime  */
  YYSYMBOL_66_Term_zegond = 66,            /* Term-zegond  */
  YYSYMBOL_G = 67,                         /* G  */
  YYSYMBOL_68_Signed_factor = 68,          /* Signed-factor  */
  YYSYMBOL_69_Signed_factor_prime = 69,    /* Signed-factor-prime  */
  YYSYMBOL_70_Signed_factor_zegond = 70,   /* Signed-factor-zegond  */
  YYSYMBOL_Factor = 71,                    /* Factor  */
  YYSYMBOL_72_Var_call_prime = 72,         /* Var-call-prime  */
  YYSYMBOL_73_Var_prime = 73,              /* Var-prime  */
  YYSYMBOL_74_Factor_prime = 74,           /* Factor-prime  */
  YYSYMBOL_75_Factor_zegond = 75,          /* Factor-zegond  */
  YYSYMBOL_Args = 76,                      /* Args  */
  YYSYMBOL_77_Arg_list = 77,               /* Arg-list  */
  YYSYMBOL_78_Arg_list_prime = 78,         /* Arg-list-prime  */
  YYSYMBOL___declaring_pid = 79,           /* __declaring_pid  */
  YYSYMBOL___immediate = 80,               /* __immediate  */
  YYSYMBOL___int_type = 81,                /* __int_type  */
  YYSYMBOL___void_type = 82,               /* __void_type  */
  YYSYMBOL___function_start = 83,          /* __function_start  */
  YYSYMBOL___function_params_end = 84,     /* __function_params_end  */
  YYSYMBOL___function_end = 85,            /* __function_end  */
  YYSYMBOL___pid = 86,                     /* __pid  */
  YYSYMBOL___pop_expression = 87,          /* __pop_expression  */
  YYSYMBOL___assign = 88,                  /* __assign  */
  YYSYMBOL___array = 89,                   /* __array  */
  YYSYMBOL___immediate_val = 90,           /* __immediate_val  */
  YYSYMBOL___save_operator = 91,           /* __save_operator  */
  YYSYMBOL___negate = 92,                  /* __negate  */
  YYSYMBOL___calculate = 93,               /* __calculate  */
  YYSYMBOL___call = 94,                    /* __call  */
  YYSYMBOL___if_condition = 95,            /* __if_condition  */
  YYSYMBOL___if_no_else_end = 96,          /* __if_no_else_end  */
  YYSYMBOL___if_else_begin = 97,           /* __if_else_begin  */
  YYSYMBOL___if_else_end = 98,             /* __if_else_end  */
  YYSYMBOL___for_condition_begin = 99,     /* __for_condition_begin  */
  YYSYMBOL___for_condition_end = 100,      /* __for_condition_end  */
  YYSYMBOL___for_step_end = 101,           /* __for_step_end  */
  YYSYMBOL___for_end = 102                 /* __for_end  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   153

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  75
/* YYNRULES -- Number of rules.  */
#define YYNRULES  113
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  201

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   282


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    57,    57,    58,    58,    59,    60,    61,    61,    62,
      63,    65,    66,    67,    69,    69,    70,    70,    71,    72,
      73,    75,    75,    76,    77,    78,    78,    79,    79,    79,
      79,    79,    80,    81,    82,    83,    84,    85,    87,    88,
      89,    90,    92,    92,    93,    94,    95,    97,    98,    99,
     100,   101,   101,   102,   102,   103,   104,   105,   106,   106,
     107,   107,   108,   109,   110,   111,   111,   112,   112,   112,
     113,   114,   114,   114,   115,   115,   115,   116,   116,   117,
     117,   118,   118,   119,   119,   120,   120,   121,   122,   122,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\";\"", "\":\"",
  "\",\"", "\"[\"", "\"]\"", "\"(\"", "\")\"", "\"{\"", "\"}\"", "\"+\"",
  "\"-\"", "\"*\"", "\"=\"", "\"<\"", "\"==\"", "\"if\"", "\"else\"",
  "\"void\"", "\"int\"", "\"for\"", "\"return\"", "\"endif\"", "\"break\"",
  "NUM", "ID", "$accept", "Program", "Global-Declaration-list",
  "Global-Declaration", "Global-Declaration-initial",
  "Global-Declaration-prime", "Var-declaration-prime",
  "Fun-declaration-prime", "Global-Type-specifier", "Params", "Param-list",
  "Param", "Param-prime", "Local-Declaration-list", "Local-Declaration",
  "Compound-stmt", "Statement-list", "Statement", "Expression-stmt",
  "Selection-stmt", "Else-stmt", "Iteration-stmt", "Return-stmt",
  "Return-stmt-prime", "Expression", "B", "H", "Simple-expression-zegond",
  "Simple-expression-prime", "C", "Relop", "Additive-expression",
  "Additive-expression-prime", "Additive-expression-zegond", "D", "Addop",
  "Term", "Term-prime", "Term-zegond", "G", "Signed-factor",
  "Signed-factor-prime", "Signed-factor-zegond", "Factor",
  "Var-call-prime", "Var-prime", "Factor-prime", "Factor-zegond", "Args",
  "Arg-list", "Arg-list-prime", "__declaring_pid", "__immediate",
  "__int_type", "__void_type", "__function_start", "__function_params_end",
  "__function_end", "__pid", "__pop_expression", "__assign", "__array",
  "__immediate_val", "__save_operator", "__negate", "__calculate",
  "__call", "__if_condition", "__if_no_else_end", "__if_else_begin",
  "__if_else_end", "__for_condition_begin", "__for_condition_end",
  "__for_step_end", "__for_end", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-143)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-103)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      21,  -143,  -143,    11,  -143,    21,    51,    -6,  -143,  -143,
    -143,  -143,  -143,     3,  -143,  -143,  -143,    26,  -143,  -143,
      48,  -143,    33,  -143,    25,    39,    57,  -143,  -143,  -143,
      69,    56,    78,    73,    70,  -143,  -143,    72,  -143,  -143,
      92,    70,  -143,    67,    73,    76,  -143,    12,    20,    20,
      84,    88,    10,    94,  -143,  -143,  -143,    87,    92,  -143,
    -143,  -143,  -143,    96,  -143,    54,    60,    93,  -143,  -143,
    -143,  -143,  -143,    99,    12,  -143,  -143,  -143,  -143,    12,
      12,  -143,  -143,   106,  -143,  -143,    59,  -143,  -143,  -143,
    -143,    18,    65,  -143,    18,    71,  -143,    97,    69,    51,
    -143,   104,  -143,     9,  -143,   107,  -143,  -143,    12,    12,
      12,  -143,  -143,    54,    60,    93,  -143,  -143,    20,    20,
    -143,    60,    93,  -143,  -143,  -143,  -143,  -143,  -143,    18,
    -143,  -143,  -143,    12,    12,  -143,  -143,  -143,   117,   114,
     118,   116,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,  -143,    60,  -143,   119,   120,    92,  -143,  -143,    12,
    -143,  -143,  -143,  -143,  -143,    93,  -143,  -143,   103,    12,
      74,   118,  -143,  -143,  -143,  -143,  -143,  -143,   109,  -143,
      12,  -143,    60,  -143,  -143,    92,   127,  -143,    54,   108,
      12,  -143,  -143,  -143,  -143,  -143,  -143,   122,    92,  -143,
    -143
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,    93,    92,     0,     2,     4,    94,     0,    13,    12,
       1,     3,    10,     0,     5,     8,     7,     0,    90,    91,
       0,     6,     0,    15,     0,     0,     0,    90,    95,     9,
      20,     0,     0,    17,    22,    96,    19,     0,    14,    92,
      26,    22,    11,     0,    17,     0,    34,     0,     0,     0,
       0,     0,     0,     0,   101,    97,    28,     0,    26,    27,
      29,    30,    31,     0,    42,    52,    59,    66,    73,    21,
      90,    16,    90,     0,     0,   101,    97,    71,   103,     0,
       0,    40,    39,     0,    33,    84,    82,    24,    25,    98,
      49,     0,     0,    57,     0,     0,    64,     0,    20,     0,
      83,     0,    76,    80,    72,     0,    98,    41,     0,    86,
       0,    43,    46,    52,    59,    66,    70,    32,     0,     0,
     104,    59,    66,    69,    53,    54,   104,    60,    61,     0,
      18,    23,    74,     0,    86,    75,    78,   106,     0,     0,
      89,     0,    85,    99,    50,    56,    63,    67,   103,    51,
      55,    62,    59,   104,     0,     0,     0,   110,   100,     0,
      87,   105,    44,    68,    58,    66,   100,   105,   108,     0,
      66,    89,    81,    65,    79,    77,   107,    35,     0,   111,
       0,    45,    59,    88,    36,     0,     0,    99,    52,     0,
       0,    47,    48,   109,    98,    37,   112,     0,     0,   113,
      38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -143,  -143,   129,  -143,  -143,  -143,    36,  -143,  -143,  -143,
      95,  -143,    38,   100,  -143,   111,    79,  -142,  -143,  -143,
    -143,  -143,  -143,  -143,   -47,  -143,  -143,  -143,  -143,  -109,
    -143,  -143,  -143,  -143,  -102,  -143,    44,  -143,  -143,  -106,
      15,  -143,  -143,   -42,  -143,  -143,  -143,  -143,     6,  -143,
     -26,   -17,  -143,   110,  -143,  -143,  -143,  -143,    75,  -104,
     -41,   -19,    77,   -64,     0,  -118,   -14,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,     5,     6,    14,    15,    16,     7,    25,
      38,    44,    33,    40,    41,    56,    57,    58,    59,    60,
     177,    61,    62,    82,    63,   111,   181,    64,   112,    90,
      91,   120,   113,    65,    93,    94,   121,   114,    66,    96,
     122,   115,    67,   123,   135,   136,   116,    68,   141,   142,
     160,    21,    22,     9,     8,    17,    31,    42,    86,   117,
     162,   170,    85,    95,   104,   149,   172,   156,   184,   178,
     195,   169,   186,   197,   200
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      73,    92,   138,    97,   144,    83,    77,    78,   152,   146,
      30,    10,   145,    81,   168,   133,   151,   134,    47,   150,
      47,    18,    48,    49,    48,    49,    74,   101,    74,    19,
     118,   119,   105,   106,    20,   165,    54,    55,    54,    55,
      26,     1,     2,   189,    75,    76,    75,    76,    28,    92,
     164,    97,    27,    98,    12,    99,   199,    13,    97,   173,
      29,   139,   140,   143,   182,   108,    34,   109,    23,    24,
    -102,  -102,  -102,  -102,   110,    32,   147,   148,    37,   192,
     188,   124,   125,   127,   128,    36,   154,   140,  -102,   180,
     196,    39,    79,    43,    70,    46,    80,    84,    87,    89,
      47,    97,    34,    72,    48,    49,    97,  -102,   100,   107,
      50,   129,   171,   132,    51,    52,   137,    53,    54,    55,
     157,   158,   179,   159,    92,   161,   166,   176,   185,   167,
     190,   198,   193,   187,    11,   131,   130,    88,   126,    71,
     155,    69,    35,   194,   153,   183,   191,   174,   163,    45,
       0,   103,   102,   175
};

static const yytype_int16 yycheck[] =
{
      47,    65,   106,    67,   113,    52,    48,    49,   126,   115,
      27,     0,   114,     3,   156,     6,   122,     8,     8,   121,
       8,    27,    12,    13,    12,    13,     8,    74,     8,    26,
      12,    13,    79,    80,     8,   153,    26,    27,    26,    27,
       7,    20,    21,   185,    26,    27,    26,    27,     9,   113,
     152,   115,    27,    70,     3,    72,   198,     6,   122,   165,
       3,   108,   109,   110,   170,     6,    10,     8,    20,    21,
      16,    17,    12,    13,    15,     6,   118,   119,     5,   188,
     182,    16,    17,    12,    13,     7,   133,   134,    14,    15,
     194,    21,     8,    21,    27,     3,     8,     3,    11,     3,
       8,   165,    10,    27,    12,    13,   170,    14,     9,     3,
      18,    14,   159,     9,    22,    23,     9,    25,    26,    27,
       3,     7,   169,     5,   188,     9,     7,    24,    19,     9,
       3,     9,    24,   180,     5,    99,    98,    58,    94,    44,
     134,    41,    31,   190,   129,   171,   187,   166,   148,    39,
      -1,    76,    75,   167
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    20,    21,    29,    30,    31,    32,    36,    82,    81,
       0,    30,     3,     6,    33,    34,    35,    83,    27,    26,
       8,    79,    80,    20,    21,    37,     7,    27,     9,     3,
      79,    84,     6,    40,    10,    43,     7,     5,    38,    21,
      41,    42,    85,    21,    39,    81,     3,     8,    12,    13,
      18,    22,    23,    25,    26,    27,    43,    44,    45,    46,
      47,    49,    50,    52,    55,    61,    66,    70,    75,    41,
      27,    38,    27,    52,     8,    26,    27,    71,    71,     8,
       8,     3,    51,    52,     3,    90,    86,    11,    44,     3,
      57,    58,    91,    62,    63,    91,    67,    91,    79,    79,
       9,    52,    90,    86,    92,    52,    52,     3,     6,     8,
      15,    53,    56,    60,    65,    69,    74,    87,    12,    13,
      59,    64,    68,    71,    16,    17,    64,    12,    13,    14,
      40,    34,     9,     6,     8,    72,    73,     9,    87,    52,
      52,    76,    77,    52,    57,    62,    67,    71,    71,    93,
      62,    67,    93,    68,    52,    76,    95,     3,     7,     5,
      78,     9,    88,    92,    62,    93,     7,     9,    45,    99,
      89,    52,    94,    67,    89,    94,    24,    48,    97,    52,
      15,    54,    67,    78,    96,    19,   100,    52,    62,    45,
       3,    88,    57,    24,    52,    98,    87,   101,     9,    45,
     102
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    28,    29,    30,    30,    31,    32,    33,    33,    34,
      34,    35,    36,    36,    37,    37,    38,    38,    39,    40,
      40,    41,    41,    42,    43,    44,    44,    45,    45,    45,
      45,    45,    46,    46,    46,    47,    48,    48,    49,    50,
      51,    51,    52,    52,    53,    53,    53,    54,    54,    55,
      56,    57,    57,    58,    58,    59,    60,    61,    62,    62,
      63,    63,    64,    65,    66,    67,    67,    68,    68,    68,
      69,    70,    70,    70,    71,    71,    71,    72,    72,    73,
      73,    74,    74,    75,    75,    76,    76,    77,    78,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     3,     1,     1,     5,
       1,     7,     2,     2,     5,     1,     3,     0,     4,     2,
       0,     2,     0,     5,     4,     2,     0,     1,     1,     1,
       1,     1,     3,     2,     1,     7,     2,     5,    15,     2,
       1,     2,     1,     3,     3,     5,     1,     3,     3,     2,
       2,     3,     0,     2,     2,     2,     2,     2,     4,     0,
       2,     2,     2,     2,     2,     5,     0,     2,     3,     1,
       1,     2,     3,     1,     3,     3,     2,     4,     1,     4,
       0,     4,     0,     3,     2,     1,     0,     2,     3,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, yyscan_t scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, yyscan_t scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, yyscan_t scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, yyscan_t scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 9: /* Var-declaration-prime: "[" NUM __immediate "]" ";"  */
#line 62 "Parser.y"
                                                                 { GET_CODEGEN()->array_declared(); }
#line 1327 "Parser.cpp"
    break;

  case 10: /* Var-declaration-prime: ";"  */
#line 63 "Parser.y"
                                                                 { GET_CODEGEN()->variable_declared(); }
#line 1333 "Parser.cpp"
    break;

  case 19: /* Param-prime: "[" "]"  */
#line 72 "Parser.y"
                             { GET_CODEGEN()->array_param(); }
#line 1339 "Parser.cpp"
    break;

  case 20: /* Param-prime: %empty  */
#line 73 "Parser.y"
                             { GET_CODEGEN()->int_param(); }
#line 1345 "Parser.cpp"
    break;

  case 33: /* Expression-stmt: "break" ";"  */
#line 81 "Parser.y"
                                      { GET_CODEGEN()->insert_break(); }
#line 1351 "Parser.cpp"
    break;

  case 40: /* Return-stmt-prime: ";"  */
#line 89 "Parser.y"
                                        { GET_CODEGEN()->insert_return(true); }
#line 1357 "Parser.cpp"
    break;

  case 41: /* Return-stmt-prime: Expression ";"  */
#line 90 "Parser.y"
                                        { GET_CODEGEN()->insert_return(false); }
#line 1363 "Parser.cpp"
    break;

  case 90: /* __declaring_pid: %empty  */
#line 124 "Parser.y"
                 { GET_CODEGEN()->declaring_pid(yylval.id); }
#line 1369 "Parser.cpp"
    break;

  case 91: /* __immediate: %empty  */
#line 125 "Parser.y"
             { GET_CODEGEN()->immediate(yylval.num); }
#line 1375 "Parser.cpp"
    break;

  case 92: /* __int_type: %empty  */
#line 126 "Parser.y"
            { GET_CODEGEN()->int_type(); }
#line 1381 "Parser.cpp"
    break;

  case 93: /* __void_type: %empty  */
#line 127 "Parser.y"
             { GET_CODEGEN()->void_type(); }
#line 1387 "Parser.cpp"
    break;

  case 94: /* __function_start: %empty  */
#line 128 "Parser.y"
                  { GET_CODEGEN()->function_start(); }
#line 1393 "Parser.cpp"
    break;

  case 95: /* __function_params_end: %empty  */
#line 129 "Parser.y"
                       { GET_CODEGEN()->function_params_end(); }
#line 1399 "Parser.cpp"
    break;

  case 96: /* __function_end: %empty  */
#line 130 "Parser.y"
                { GET_CODEGEN()->function_end(); }
#line 1405 "Parser.cpp"
    break;

  case 97: /* __pid: %empty  */
#line 131 "Parser.y"
       { GET_CODEGEN()->pid(yylval.id); }
#line 1411 "Parser.cpp"
    break;

  case 98: /* __pop_expression: %empty  */
#line 132 "Parser.y"
                  { GET_CODEGEN()->pop_expression(); }
#line 1417 "Parser.cpp"
    break;

  case 99: /* __assign: %empty  */
#line 133 "Parser.y"
          { GET_CODEGEN()->assign(); }
#line 1423 "Parser.cpp"
    break;

  case 100: /* __array: %empty  */
#line 134 "Parser.y"
         { GET_CODEGEN()->array(); }
#line 1429 "Parser.cpp"
    break;

  case 101: /* __immediate_val: %empty  */
#line 135 "Parser.y"
                 { GET_CODEGEN()->immediate_val(yylval.num); }
#line 1435 "Parser.cpp"
    break;

  case 102: /* __save_operator: %empty  */
#line 136 "Parser.y"
                 { GET_CODEGEN()->save_operator(static_cast<CodeGenerator::Operator>(yychar)); }
#line 1441 "Parser.cpp"
    break;

  case 103: /* __negate: %empty  */
#line 137 "Parser.y"
          { GET_CODEGEN()->negate(); }
#line 1447 "Parser.cpp"
    break;

  case 104: /* __calculate: %empty  */
#line 138 "Parser.y"
             { GET_CODEGEN()->calculate(); }
#line 1453 "Parser.cpp"
    break;

  case 105: /* __call: %empty  */
#line 139 "Parser.y"
        { GET_CODEGEN()->call(); }
#line 1459 "Parser.cpp"
    break;

  case 106: /* __if_condition: %empty  */
#line 140 "Parser.y"
                { GET_CODEGEN()->if_condition(); }
#line 1465 "Parser.cpp"
    break;

  case 107: /* __if_no_else_end: %empty  */
#line 141 "Parser.y"
                  { GET_CODEGEN()->if_no_else_end(); }
#line 1471 "Parser.cpp"
    break;

  case 108: /* __if_else_begin: %empty  */
#line 142 "Parser.y"
                 { GET_CODEGEN()->if_else_begin(); }
#line 1477 "Parser.cpp"
    break;

  case 109: /* __if_else_end: %empty  */
#line 143 "Parser.y"
               { GET_CODEGEN()->if_else_end(); }
#line 1483 "Parser.cpp"
    break;

  case 110: /* __for_condition_begin: %empty  */
#line 144 "Parser.y"
                       { GET_CODEGEN()->for_condition_begin(); }
#line 1489 "Parser.cpp"
    break;

  case 111: /* __for_condition_end: %empty  */
#line 145 "Parser.y"
                     { GET_CODEGEN()->for_condition_end(); }
#line 1495 "Parser.cpp"
    break;

  case 112: /* __for_step_end: %empty  */
#line 146 "Parser.y"
                { GET_CODEGEN()->for_step_end(); }
#line 1501 "Parser.cpp"
    break;

  case 113: /* __for_end: %empty  */
#line 147 "Parser.y"
           { GET_CODEGEN()->for_end(); }
#line 1507 "Parser.cpp"
    break;


#line 1511 "Parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 148 "Parser.y"
