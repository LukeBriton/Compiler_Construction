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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 11 "MyBison.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "declare.h"
int arg_num = 0;    // 可以方便 arg_pass
// int para_num = 0;// 方便 para_declaration -> 被 symtab.cpp Index_para 取代
int is_main = 0;    // 只在返回时有用，为 0 是一般 func，为 1 是 main。
int scope = 0;      // scope 为当前作用域序号，从 0 开始，0 即为默认函数作用域。
int if_num = 0;
int if_nested = 0;
int loop_num = 0;
int loop_nested = 0;

#line 87 "MyBison.tab.c"

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

#include "MyBison.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTLIT = 3,                     /* INTLIT  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_PRINTLN_INT = 5,                /* PRINTLN_INT  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_BREAK = 9,                      /* BREAK  */
  YYSYMBOL_CONTINUE = 10,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_MAIN = 12,                      /* MAIN  */
  YYSYMBOL_INT = 13,                       /* INT  */
  YYSYMBOL_VOID = 14,                      /* VOID  */
  YYSYMBOL_THEN = 15,                      /* THEN  */
  YYSYMBOL_16_ = 16,                       /* '='  */
  YYSYMBOL_LOR = 17,                       /* LOR  */
  YYSYMBOL_LAND = 18,                      /* LAND  */
  YYSYMBOL_19_ = 19,                       /* '|'  */
  YYSYMBOL_20_ = 20,                       /* '^'  */
  YYSYMBOL_21_ = 21,                       /* '&'  */
  YYSYMBOL_EQN = 22,                       /* EQN  */
  YYSYMBOL_LGTE = 23,                      /* LGTE  */
  YYSYMBOL_24_ = 24,                       /* '+'  */
  YYSYMBOL_25_ = 25,                       /* '-'  */
  YYSYMBOL_26_ = 26,                       /* '*'  */
  YYSYMBOL_27_ = 27,                       /* '/'  */
  YYSYMBOL_28_ = 28,                       /* '%'  */
  YYSYMBOL_UMINUS = 29,                    /* UMINUS  */
  YYSYMBOL_30_ = 30,                       /* '!'  */
  YYSYMBOL_31_ = 31,                       /* '~'  */
  YYSYMBOL_32_ = 32,                       /* '('  */
  YYSYMBOL_33_ = 33,                       /* ')'  */
  YYSYMBOL_34_ = 34,                       /* ','  */
  YYSYMBOL_35_ = 35,                       /* '{'  */
  YYSYMBOL_36_ = 36,                       /* '}'  */
  YYSYMBOL_37_ = 37,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_program = 39,                   /* program  */
  YYSYMBOL_40_1 = 40,                      /* $@1  */
  YYSYMBOL_procedure = 41,                 /* procedure  */
  YYSYMBOL_42_2 = 42,                      /* $@2  */
  YYSYMBOL_43_3 = 43,                      /* $@3  */
  YYSYMBOL_44_4 = 44,                      /* $@4  */
  YYSYMBOL_45_5 = 45,                      /* $@5  */
  YYSYMBOL_46_6 = 46,                      /* $@6  */
  YYSYMBOL_47_7 = 47,                      /* $@7  */
  YYSYMBOL_paralist = 48,                  /* paralist  */
  YYSYMBOL_compound_statement = 49,        /* compound_statement  */
  YYSYMBOL_50_8 = 50,                      /* $@8  */
  YYSYMBOL_51_9 = 51,                      /* $@9  */
  YYSYMBOL_stmts = 52,                     /* stmts  */
  YYSYMBOL_declaration = 53,               /* declaration  */
  YYSYMBOL_declarators = 54,               /* declarators  */
  YYSYMBOL_declarator = 55,                /* declarator  */
  YYSYMBOL_if_statement = 56,              /* if_statement  */
  YYSYMBOL_57_10 = 57,                     /* $@10  */
  YYSYMBOL_if_true = 58,                   /* if_true  */
  YYSYMBOL_59_11 = 59,                     /* $@11  */
  YYSYMBOL_60_12 = 60,                     /* $@12  */
  YYSYMBOL_loop = 61,                      /* loop  */
  YYSYMBOL_62_13 = 62,                     /* $@13  */
  YYSYMBOL_63_14 = 63,                     /* $@14  */
  YYSYMBOL_stmt = 64,                      /* stmt  */
  YYSYMBOL_arglist = 65,                   /* arglist  */
  YYSYMBOL_exp = 66                        /* exp  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   239

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  144

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   275


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
       2,     2,     2,    30,     2,     2,     2,    28,    21,     2,
      32,    33,    26,    24,    34,    25,     2,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    37,
       2,    16,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    20,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,    19,    36,    31,     2,     2,     2,
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
      15,    17,    18,    22,    23,    29
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   118,   118,   118,   119,   131,   131,   132,   132,   133,
     133,   134,   134,   135,   135,   136,   136,   158,   159,   163,
     164,   164,   164,   171,   172,   197,   200,   201,   204,   205,
     212,   213,   213,   217,   217,   217,   220,   220,   220,   223,
     224,   225,   226,   227,   228,   229,   236,   237,   245,   259,
     260,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   295,   306
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
  "\"end of file\"", "error", "\"invalid token\"", "INTLIT", "ID",
  "PRINTLN_INT", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "RETURN",
  "MAIN", "INT", "VOID", "THEN", "'='", "LOR", "LAND", "'|'", "'^'", "'&'",
  "EQN", "LGTE", "'+'", "'-'", "'*'", "'/'", "'%'", "UMINUS", "'!'", "'~'",
  "'('", "')'", "','", "'{'", "'}'", "';'", "$accept", "program", "$@1",
  "procedure", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "paralist",
  "compound_statement", "$@8", "$@9", "stmts", "declaration",
  "declarators", "declarator", "if_statement", "$@10", "if_true", "$@11",
  "$@12", "loop", "$@13", "$@14", "stmt", "arglist", "exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-69)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-12)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -69,    33,    29,   -69,     2,    -3,   -69,   -69,   -29,   -21,
     -19,    14,    -1,    46,    40,    76,   143,   -69,   115,    76,
     114,   146,    54,   130,   114,   114,    60,   129,   -69,   -69,
     114,   153,   154,   -69,   -69,   114,   -69,    13,   -69,   214,
     215,   -69,    -7,   188,   190,   191,   184,   187,     4,   221,
     -69,    13,   -69,     7,   -69,   219,   -69,   -69,   -69,   194,
       4,     4,     4,     4,   -69,   -69,   -69,   -69,   196,     4,
       4,     4,     4,    58,   213,   -69,   195,   -69,   221,   -69,
     -69,   -69,    79,   197,   100,   118,   152,     4,     4,   -69,
     -69,   -69,   135,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   -69,     4,   -69,   -69,    13,
     114,   -69,   198,     4,   199,   200,   152,   201,   -69,   163,
     173,   182,    87,   189,    26,   105,    30,    30,   -69,   -69,
     -69,   152,   -69,   -69,   -69,   -69,   -69,   -69,   204,   -69,
      13,    13,   -69,   -69
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     4,     3,     0,     0,
       0,     9,     0,     5,     0,     0,     0,    13,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    10,    17,
       0,     0,     0,    14,     6,     0,    19,     0,    12,     0,
       0,     8,     0,     0,     0,     0,     0,     0,     0,     0,
      40,    21,    39,     0,    41,    30,    42,    23,    18,     0,
       0,     0,     0,     0,    36,    43,    44,    67,    69,     0,
       0,     0,     0,     0,    28,    26,     0,    24,     0,    25,
      31,    15,     0,     0,    49,     0,    33,     0,     0,    63,
      64,    65,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    47,     0,    22,    27,     0,
       0,    45,     0,     0,     0,     0,    37,     0,    66,    62,
      61,    60,    59,    58,    57,    56,    54,    55,    51,    52,
      53,    29,    32,    16,    48,    50,    46,    34,     0,    68,
       0,     0,    35,    38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -69,   -69,   -69,   230,   -69,   -69,   -69,   -69,   -69,   -69,
     220,   -20,   -69,   -69,   -69,   -69,   -69,   160,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -49,   -68,   -32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     6,    18,    19,    14,    15,    24,   110,
      22,    50,    37,    76,    51,    52,    53,    75,    54,   109,
      55,   115,   140,    56,    87,   138,    57,    83,    84
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,    10,    77,    11,    33,    34,     8,    67,    68,    60,
      38,    12,    16,    13,     9,    41,    73,    42,    43,    44,
     117,    45,    46,    47,    48,    61,    49,   -11,    82,    69,
      85,    86,    17,     3,    70,    71,    72,    89,    90,    91,
      92,    78,     4,     5,    79,   135,     4,     5,    27,    99,
     100,   101,   102,   103,   104,   116,   102,   103,   104,    -7,
     132,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,    20,   131,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,    30,    31,    21,
     133,   142,   143,    35,    31,   105,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,    97,    98,
      99,   100,   101,   102,   103,   104,   111,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   100,
     101,   102,   103,   104,   113,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,    23,    25,    27,
      29,   114,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,    32,    36,    39,    40,   118,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,    96,    97,    98,    99,   100,   101,   102,   103,
     104,    98,    99,   100,   101,   102,   103,   104,    58,    59,
      62,    65,    63,    64,    66,    74,    80,    81,    88,   106,
     112,   107,     7,   137,   139,   134,   136,   141,   108,    26
};

static const yytype_uint8 yycheck[] =
{
      20,     4,    51,    32,    24,    25,     4,     3,     4,    16,
      30,    32,    13,    32,    12,    35,    48,     4,     5,     6,
      88,     8,     9,    10,    11,    32,    13,    13,    60,    25,
      62,    63,    33,     0,    30,    31,    32,    69,    70,    71,
      72,    34,    13,    14,    37,   113,    13,    14,    35,    23,
      24,    25,    26,    27,    28,    87,    26,    27,    28,    13,
     109,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,    33,   106,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    33,    34,    13,
     110,   140,   141,    33,    34,    37,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    21,    22,
      23,    24,    25,    26,    27,    28,    37,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    24,
      25,    26,    27,    28,    34,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,     4,    33,    35,
       4,    33,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    34,    36,    13,    13,    33,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    22,    23,    24,    25,    26,    27,    28,     4,     4,
      32,    37,    32,    32,    37,     4,     7,    33,    32,    16,
      33,    36,     2,    33,    33,    37,    37,    33,    78,    19
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    39,    40,     0,    13,    14,    41,    41,     4,    12,
       4,    32,    32,    32,    44,    45,    13,    33,    42,    43,
      33,    13,    48,     4,    46,    33,    48,    35,    49,     4,
      33,    34,    34,    49,    49,    33,    36,    50,    49,    13,
      13,    49,     4,     5,     6,     8,     9,    10,    11,    13,
      49,    52,    53,    54,    56,    58,    61,    64,     4,     4,
      16,    32,    32,    32,    32,    37,    37,     3,     4,    25,
      30,    31,    32,    66,     4,    55,    51,    64,    34,    37,
       7,    33,    66,    65,    66,    66,    66,    62,    32,    66,
      66,    66,    66,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    37,    16,    36,    55,    57,
      47,    37,    33,    34,    33,    59,    66,    65,    33,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    64,    49,    37,    65,    37,    33,    63,    33,
      60,    33,    64,    64
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    40,    39,    39,    42,    41,    43,    41,    44,
      41,    45,    41,    46,    41,    47,    41,    48,    48,    49,
      50,    51,    49,    52,    52,    53,    54,    54,    55,    55,
      56,    57,    56,    59,    60,    58,    62,    63,    61,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    65,
      65,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     0,     6,     0,     7,     0,
       6,     0,     7,     0,     6,     0,    11,     2,     4,     2,
       0,     0,     5,     1,     2,     2,     2,     3,     1,     3,
       1,     0,     4,     0,     0,     7,     0,     0,     7,     1,
       1,     1,     1,     2,     2,     4,     5,     3,     5,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     3,     1,     4,     1
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
        yyerror (YY_("syntax error: cannot back up")); \
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
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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
      yychar = yylex ();
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
  case 2: /* $@1: %empty  */
#line 118 "MyBison.y"
          { genpreamble(); }
#line 1245 "MyBison.tab.c"
    break;

  case 3: /* program: $@1 procedure  */
#line 118 "MyBison.y"
                                            {}
#line 1251 "MyBison.tab.c"
    break;

  case 4: /* program: program procedure  */
#line 119 "MyBison.y"
                                            {}
#line 1257 "MyBison.tab.c"
    break;

  case 5: /* $@2: %empty  */
#line 131 "MyBison.y"
                          { is_main = 0; genfuncpreamble((yyvsp[-1].s), P_VOID); }
#line 1263 "MyBison.tab.c"
    break;

  case 6: /* procedure: VOID ID '(' $@2 ')' compound_statement  */
#line 131 "MyBison.y"
                                                                                                                          {genfuncpostamble();}
#line 1269 "MyBison.tab.c"
    break;

  case 7: /* $@3: %empty  */
#line 132 "MyBison.y"
                          { is_main = 0; genfuncpreamble((yyvsp[-1].s), P_VOID); /*para_num = 0;*/ }
#line 1275 "MyBison.tab.c"
    break;

  case 8: /* procedure: VOID ID '(' $@3 paralist ')' compound_statement  */
#line 132 "MyBison.y"
                                                                                                                          {genfuncpostamble();}
#line 1281 "MyBison.tab.c"
    break;

  case 9: /* $@4: %empty  */
#line 133 "MyBison.y"
                         { is_main = 0; genfuncpreamble((yyvsp[-1].s), P_INT); }
#line 1287 "MyBison.tab.c"
    break;

  case 10: /* procedure: INT ID '(' $@4 ')' compound_statement  */
#line 133 "MyBison.y"
                                                                                                                          {genfuncpostamble();}
#line 1293 "MyBison.tab.c"
    break;

  case 11: /* $@5: %empty  */
#line 134 "MyBison.y"
                         { is_main = 0; genfuncpreamble((yyvsp[-1].s), P_INT); /*para_num = 0;*/ }
#line 1299 "MyBison.tab.c"
    break;

  case 12: /* procedure: INT ID '(' $@5 paralist ')' compound_statement  */
#line 134 "MyBison.y"
                                                                                                                          {genfuncpostamble();}
#line 1305 "MyBison.tab.c"
    break;

  case 13: /* $@6: %empty  */
#line 135 "MyBison.y"
                               { is_main = 1; genmainpreamble(); }
#line 1311 "MyBison.tab.c"
    break;

  case 14: /* procedure: INT MAIN '(' ')' $@6 compound_statement  */
#line 135 "MyBison.y"
                                                                                        {}
#line 1317 "MyBison.tab.c"
    break;

  case 15: /* $@7: %empty  */
#line 136 "MyBison.y"
                                                 { is_main = 1; genmainpreamble(); para_declaration((yyvsp[-4].s)); para_declaration((yyvsp[-1].s)); }
#line 1323 "MyBison.tab.c"
    break;

  case 16: /* procedure: INT MAIN '(' INT ID ',' INT ID ')' $@7 compound_statement  */
#line 136 "MyBison.y"
                                                                                                                                                    {}
#line 1329 "MyBison.tab.c"
    break;

  case 17: /* paralist: INT ID  */
#line 158 "MyBison.y"
                  { /*para_num++;*/ /*printf("%s\n", $2);*/ para_declaration((yyvsp[0].s));/*, para_num);*/ /*printf("%d\n", findlocal($2));*/ }
#line 1335 "MyBison.tab.c"
    break;

  case 18: /* paralist: paralist ',' INT ID  */
#line 159 "MyBison.y"
                               { /*para_num++;*/ /*printf("%s\n", $4);*/ para_declaration((yyvsp[0].s));/*, para_num);*/ /*printf("%d\n", findlocal($4));*/ }
#line 1341 "MyBison.tab.c"
    break;

  case 19: /* compound_statement: '{' '}'  */
#line 163 "MyBison.y"
                            {}
#line 1347 "MyBison.tab.c"
    break;

  case 20: /* $@8: %empty  */
#line 164 "MyBison.y"
           { scope++; pass_scope(scope); /*printf("%d\n", scope);*/ }
#line 1353 "MyBison.tab.c"
    break;

  case 21: /* $@9: %empty  */
#line 164 "MyBison.y"
                                                                            { scope--; pass_scope(scope); /*printf("%d\n", scope);*/ }
#line 1359 "MyBison.tab.c"
    break;

  case 22: /* compound_statement: '{' $@8 stmts $@9 '}'  */
#line 164 "MyBison.y"
                                                                                                                                                  {}
#line 1365 "MyBison.tab.c"
    break;

  case 23: /* stmts: stmt  */
#line 171 "MyBison.y"
                        {}
#line 1371 "MyBison.tab.c"
    break;

  case 24: /* stmts: stmts stmt  */
#line 172 "MyBison.y"
                        {}
#line 1377 "MyBison.tab.c"
    break;

  case 25: /* declaration: declarators ';'  */
#line 197 "MyBison.y"
                                            {}
#line 1383 "MyBison.tab.c"
    break;

  case 26: /* declarators: INT declarator  */
#line 200 "MyBison.y"
                                            {}
#line 1389 "MyBison.tab.c"
    break;

  case 27: /* declarators: declarators ',' declarator  */
#line 201 "MyBison.y"
                                            {}
#line 1395 "MyBison.tab.c"
    break;

  case 28: /* declarator: ID  */
#line 204 "MyBison.y"
                            { var_declaration((yyvsp[0].s)); }
#line 1401 "MyBison.tab.c"
    break;

  case 29: /* declarator: ID '=' exp  */
#line 205 "MyBison.y"
                            { var_declaration((yyvsp[-2].s)); assignment_statement((yyvsp[-2].s), (yyvsp[0].a)); }
#line 1407 "MyBison.tab.c"
    break;

  case 30: /* if_statement: if_true  */
#line 212 "MyBison.y"
                                  { printf("\n$if_end_%d:\n", if_nested); if_nested --; }
#line 1413 "MyBison.tab.c"
    break;

  case 31: /* $@10: %empty  */
#line 213 "MyBison.y"
                            { /*printf("if_false_%d:\n\n\n", ++if_false_num);*/ }
#line 1419 "MyBison.tab.c"
    break;

  case 32: /* if_statement: if_true ELSE $@10 stmt  */
#line 213 "MyBison.y"
                                                                                       { printf("\n$if_end_%d:\n", if_nested); if_nested --; /*printf("false\n");*/ }
#line 1425 "MyBison.tab.c"
    break;

  case 33: /* $@11: %empty  */
#line 217 "MyBison.y"
                          { if_num ++; if_nested = if_num; condition((yyvsp[0].a), 1, if_nested); }
#line 1431 "MyBison.tab.c"
    break;

  case 34: /* $@12: %empty  */
#line 217 "MyBison.y"
                                                                                              { /*printf("true\n");*/ }
#line 1437 "MyBison.tab.c"
    break;

  case 35: /* if_true: IF '(' exp $@11 ')' $@12 stmt  */
#line 217 "MyBison.y"
                                                                                                                             { printf("j $if_end_%d\n", if_nested); printf("\n$if_false_%d:\n", if_nested); }
#line 1443 "MyBison.tab.c"
    break;

  case 36: /* $@13: %empty  */
#line 220 "MyBison.y"
                 { loop_num ++; loop_nested = loop_num; printf("\n$loop_%d:\n", loop_nested); }
#line 1449 "MyBison.tab.c"
    break;

  case 37: /* $@14: %empty  */
#line 220 "MyBison.y"
                                                                                                    { condition((yyvsp[0].a), 2, loop_nested); }
#line 1455 "MyBison.tab.c"
    break;

  case 38: /* loop: WHILE '(' $@13 exp $@14 ')' stmt  */
#line 220 "MyBison.y"
                                                                                                                                                { printf("j $loop_%d\n", loop_nested); printf("\n$loop_end_%d:\n", loop_nested); loop_nested --; }
#line 1461 "MyBison.tab.c"
    break;

  case 39: /* stmt: declaration  */
#line 223 "MyBison.y"
                            {}
#line 1467 "MyBison.tab.c"
    break;

  case 40: /* stmt: compound_statement  */
#line 224 "MyBison.y"
                            {}
#line 1473 "MyBison.tab.c"
    break;

  case 41: /* stmt: if_statement  */
#line 225 "MyBison.y"
                            {}
#line 1479 "MyBison.tab.c"
    break;

  case 42: /* stmt: loop  */
#line 226 "MyBison.y"
                            {}
#line 1485 "MyBison.tab.c"
    break;

  case 43: /* stmt: BREAK ';'  */
#line 227 "MyBison.y"
                            { printf("\nj $loop_end_%d\n", loop_nested); }
#line 1491 "MyBison.tab.c"
    break;

  case 44: /* stmt: CONTINUE ';'  */
#line 228 "MyBison.y"
                            { printf("\nj $loop_%d\n", loop_nested); }
#line 1497 "MyBison.tab.c"
    break;

  case 45: /* stmt: ID '=' exp ';'  */
#line 229 "MyBison.y"
                            { assignment_statement((yyvsp[-3].s), (yyvsp[-1].a)); }
#line 1503 "MyBison.tab.c"
    break;

  case 46: /* stmt: PRINTLN_INT '(' exp ')' ';'  */
#line 236 "MyBison.y"
                                   { println_int_statement((yyvsp[-2].a)); }
#line 1509 "MyBison.tab.c"
    break;

  case 47: /* stmt: RETURN exp ';'  */
#line 237 "MyBison.y"
                            {
        return_statement((yyvsp[-1].a));
        if (is_main == 1)
            exit_syscall();
        else if (is_main == 0)
            genfuncpostamble();
        }
#line 1521 "MyBison.tab.c"
    break;

  case 48: /* stmt: ID '(' arglist ')' ';'  */
#line 245 "MyBison.y"
                              {
        // Check that this identifier exists
        int func = findfunc((yyvsp[-4].s));
        if (func == -1)
            yyerror("Unknown function %s", (yyvsp[-4].s));
        // printf("%s\n", $1);
        arglist_buf(arg_num);
        arg_num = 0;
        arglist_output();
        func_call((yyvsp[-4].s));
        }
#line 1537 "MyBison.tab.c"
    break;

  case 49: /* arglist: exp  */
#line 259 "MyBison.y"
              { arg_num++; /*printf("%d\n", arg_num);*/ /*printf("%d\n", $1->v.intvalue);*/ arg_pass((yyvsp[0].a)); }
#line 1543 "MyBison.tab.c"
    break;

  case 50: /* arglist: exp ',' arglist  */
#line 260 "MyBison.y"
                          { arg_num++; /*printf("%d\n", arg_num);*/ /*printf("%d\n", $1->v.intvalue);*/ arg_pass((yyvsp[-2].a)); }
#line 1549 "MyBison.tab.c"
    break;

  case 51: /* exp: exp '*' exp  */
#line 271 "MyBison.y"
                  { (yyval.a) = mkastnode('*', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1555 "MyBison.tab.c"
    break;

  case 52: /* exp: exp '/' exp  */
#line 272 "MyBison.y"
                  { (yyval.a) = mkastnode('/', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1561 "MyBison.tab.c"
    break;

  case 53: /* exp: exp '%' exp  */
#line 273 "MyBison.y"
                  { (yyval.a) = mkastnode('%', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1567 "MyBison.tab.c"
    break;

  case 54: /* exp: exp '+' exp  */
#line 274 "MyBison.y"
                  { (yyval.a) = mkastnode('+', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1573 "MyBison.tab.c"
    break;

  case 55: /* exp: exp '-' exp  */
#line 275 "MyBison.y"
                  { (yyval.a) = mkastnode('-', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1579 "MyBison.tab.c"
    break;

  case 56: /* exp: exp LGTE exp  */
#line 276 "MyBison.y"
                   { (yyval.a) = mkastnode((yyvsp[-1].fn), (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1585 "MyBison.tab.c"
    break;

  case 57: /* exp: exp EQN exp  */
#line 277 "MyBison.y"
                  { (yyval.a) = mkastnode((yyvsp[-1].fn), (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1591 "MyBison.tab.c"
    break;

  case 58: /* exp: exp '&' exp  */
#line 278 "MyBison.y"
                  { (yyval.a) = mkastnode('&', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1597 "MyBison.tab.c"
    break;

  case 59: /* exp: exp '^' exp  */
#line 279 "MyBison.y"
                  { (yyval.a) = mkastnode('^', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1603 "MyBison.tab.c"
    break;

  case 60: /* exp: exp '|' exp  */
#line 280 "MyBison.y"
                  { (yyval.a) = mkastnode('|', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1609 "MyBison.tab.c"
    break;

  case 61: /* exp: exp LAND exp  */
#line 281 "MyBison.y"
                   { (yyval.a) = mkastnode(A_LAND, (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1615 "MyBison.tab.c"
    break;

  case 62: /* exp: exp LOR exp  */
#line 282 "MyBison.y"
                  { (yyval.a) = mkastnode(A_LOR, (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1621 "MyBison.tab.c"
    break;

  case 63: /* exp: '-' exp  */
#line 283 "MyBison.y"
                           { (yyval.a) = mkastunary(A_UMINUS, (yyvsp[0].a), 0); }
#line 1627 "MyBison.tab.c"
    break;

  case 64: /* exp: '!' exp  */
#line 284 "MyBison.y"
              { (yyval.a) = mkastunary('!', (yyvsp[0].a), 0); }
#line 1633 "MyBison.tab.c"
    break;

  case 65: /* exp: '~' exp  */
#line 285 "MyBison.y"
              { (yyval.a) = mkastunary('~', (yyvsp[0].a), 0); }
#line 1639 "MyBison.tab.c"
    break;

  case 66: /* exp: '(' exp ')'  */
#line 286 "MyBison.y"
                  { (yyval.a) = (yyvsp[-1].a); }
#line 1645 "MyBison.tab.c"
    break;

  case 67: /* exp: INTLIT  */
#line 287 "MyBison.y"
             { (yyval.a) = mkastleaf(A_INTLIT, (yyvsp[0].intval)); }
#line 1651 "MyBison.tab.c"
    break;

  case 68: /* exp: ID '(' arglist ')'  */
#line 295 "MyBison.y"
                         {
        // Check that this identifier exists
        int func = findfunc((yyvsp[-3].s));
        if (func == -1)
            yyerror("Unknown function %s", (yyvsp[-3].s));
        // printf("%s\n", $1);
        arglist_buf(arg_num);
        arg_num = 0;
        // Make a leaf AST node for it
        (yyval.a) = mkastleaf(A_FUNC, func);
        }
#line 1667 "MyBison.tab.c"
    break;

  case 69: /* exp: ID  */
#line 306 "MyBison.y"
         {
        // printf("%s\n", $1);
        // Check that this identifier exists
        int id = findlocal((yyvsp[0].s));
        if (id == -1)
            yyerror("Unknown variable %s", (yyvsp[0].s));
        // Make a leaf AST node for it
        (yyval.a) = mkastleaf(A_IDENT, id);
        }
#line 1681 "MyBison.tab.c"
    break;


#line 1685 "MyBison.tab.c"

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
      yyerror (YY_("syntax error"));
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
                      yytoken, &yylval);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 327 "MyBison.y"

