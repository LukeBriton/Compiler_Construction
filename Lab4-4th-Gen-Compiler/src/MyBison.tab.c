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

#line 83 "MyBison.tab.c"

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
  YYSYMBOL_RETURN = 6,                     /* RETURN  */
  YYSYMBOL_MAIN = 7,                       /* MAIN  */
  YYSYMBOL_INT = 8,                        /* INT  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_10_ = 10,                       /* '='  */
  YYSYMBOL_LOR = 11,                       /* LOR  */
  YYSYMBOL_LAND = 12,                      /* LAND  */
  YYSYMBOL_13_ = 13,                       /* '|'  */
  YYSYMBOL_14_ = 14,                       /* '^'  */
  YYSYMBOL_15_ = 15,                       /* '&'  */
  YYSYMBOL_EQN = 16,                       /* EQN  */
  YYSYMBOL_LGTE = 17,                      /* LGTE  */
  YYSYMBOL_18_ = 18,                       /* '+'  */
  YYSYMBOL_19_ = 19,                       /* '-'  */
  YYSYMBOL_20_ = 20,                       /* '*'  */
  YYSYMBOL_21_ = 21,                       /* '/'  */
  YYSYMBOL_22_ = 22,                       /* '%'  */
  YYSYMBOL_UMINUS = 23,                    /* UMINUS  */
  YYSYMBOL_24_ = 24,                       /* '!'  */
  YYSYMBOL_25_ = 25,                       /* '~'  */
  YYSYMBOL_26_ = 26,                       /* '('  */
  YYSYMBOL_27_ = 27,                       /* ')'  */
  YYSYMBOL_28_ = 28,                       /* '{'  */
  YYSYMBOL_29_ = 29,                       /* '}'  */
  YYSYMBOL_30_ = 30,                       /* ','  */
  YYSYMBOL_31_ = 31,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_program = 33,                   /* program  */
  YYSYMBOL_34_1 = 34,                      /* $@1  */
  YYSYMBOL_procedure = 35,                 /* procedure  */
  YYSYMBOL_36_2 = 36,                      /* $@2  */
  YYSYMBOL_37_3 = 37,                      /* $@3  */
  YYSYMBOL_38_4 = 38,                      /* $@4  */
  YYSYMBOL_39_5 = 39,                      /* $@5  */
  YYSYMBOL_40_6 = 40,                      /* $@6  */
  YYSYMBOL_41_7 = 41,                      /* $@7  */
  YYSYMBOL_paralist = 42,                  /* paralist  */
  YYSYMBOL_stmts = 43,                     /* stmts  */
  YYSYMBOL_declarations = 44,              /* declarations  */
  YYSYMBOL_identifier = 45,                /* identifier  */
  YYSYMBOL_stmt = 46,                      /* stmt  */
  YYSYMBOL_47_8 = 47,                      /* $@8  */
  YYSYMBOL_48_9 = 48,                      /* $@9  */
  YYSYMBOL_arglist = 49,                   /* arglist  */
  YYSYMBOL_exp = 50                        /* exp  */
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
#define YYLAST   269

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  129

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   269


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
       2,     2,     2,    24,     2,     2,     2,    22,    15,     2,
      26,    27,    20,    18,    30,    19,     2,    21,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
       2,    10,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    14,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    28,    13,    29,    25,     2,     2,     2,
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
       5,     6,     7,     8,     9,    11,    12,    16,    17,    23
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   113,   113,   113,   114,   126,   126,   127,   127,   128,
     128,   129,   129,   130,   130,   131,   131,   153,   154,   162,
     163,   187,   188,   191,   192,   196,   197,   197,   197,   198,
     205,   206,   212,   226,   227,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   262,   273
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
  "PRINTLN_INT", "RETURN", "MAIN", "INT", "VOID", "'='", "LOR", "LAND",
  "'|'", "'^'", "'&'", "EQN", "LGTE", "'+'", "'-'", "'*'", "'/'", "'%'",
  "UMINUS", "'!'", "'~'", "'('", "')'", "'{'", "'}'", "','", "';'",
  "$accept", "program", "$@1", "procedure", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "paralist", "stmts", "declarations", "identifier", "stmt",
  "$@8", "$@9", "arglist", "exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-72)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-12)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -72,     4,    -2,   -72,    10,    11,   -72,   -72,     1,     8,
      22,    33,    -5,    51,    47,    73,    82,   -72,    61,    73,
      62,    95,    12,    71,    76,    77,    28,   105,   -72,    78,
     104,   106,   105,   105,    89,     0,    93,    21,   114,   -72,
      15,    30,   -72,   105,   170,   190,    48,    74,   105,    21,
      21,    21,   -72,   182,    21,    21,    21,    21,   123,   199,
     -72,   105,   -72,   -72,   114,   -72,    79,   -72,   183,   -72,
     -72,    87,   144,   184,   165,   185,    21,   -72,   -72,   -72,
     202,    21,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,   -72,    21,   105,   -72,   -72,   -72,   -72,
     -72,   194,    21,   195,   200,   -72,   110,   229,   238,   131,
     151,   171,   243,    29,    29,   -72,   -72,   -72,   219,   237,
     239,   -72,   -72,   -72,   -72,   -72,   105,    92,   -72
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     4,     3,     0,     0,
       0,     9,     0,     5,     0,     0,     0,    13,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    26,
       0,     0,    19,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,    53,     0,     0,     0,     0,     0,    23,
      21,     0,    10,    20,     0,    25,     0,    18,     0,    14,
       6,     0,     0,     0,    33,     0,     0,    47,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,    27,    22,    12,    15,     8,
      29,     0,     0,     0,     0,    50,    46,    45,    44,    43,
      42,    41,    40,    38,    39,    35,    36,    37,    24,     0,
       0,    32,    34,    30,    52,    28,     0,     0,    16
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   -72,   226,   -72,   -72,   -72,   -72,   -72,   -72,
     249,   -32,   -72,   205,   -38,   -72,   -72,   -71,   -19
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     6,    18,    19,    14,    15,    24,   120,
      22,    40,    41,    60,    42,    61,   119,    73,    74
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      46,    47,    63,    16,     3,   104,     4,     5,    63,    63,
      49,    66,     4,     5,     8,    10,    71,     9,    58,    35,
      36,    37,    17,    38,    52,    53,    50,    11,    63,    95,
      72,   122,    75,    63,    12,    77,    78,    79,    80,    29,
      54,   -11,    30,    39,    62,    55,    56,    57,    13,    90,
      91,    92,    35,    36,    37,    34,    38,    63,    30,    -7,
      64,    65,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,    20,   118,    39,    69,    35,    36,
      37,    21,    38,    35,    36,    37,    23,    38,    25,    63,
      27,    35,    36,    37,   127,    38,    35,    36,    37,    28,
      38,    31,    39,    70,    32,    33,    43,    39,    97,    35,
      36,    37,    44,    38,    45,    39,    99,    48,    59,    51,
      39,   128,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    39,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    86,    87,    88,
      89,    90,    91,    92,    67,   100,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    87,    88,
      89,    90,    91,    92,    68,   102,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    76,    94,
      98,   101,   103,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,   121,   123,   124,     7,   105,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    88,    89,    90,    91,    92,   125,   126,    26,    96
};

static const yytype_int8 yycheck[] =
{
      32,    33,    40,     8,     0,    76,     8,     9,    46,    47,
      10,    43,     8,     9,     4,     4,    48,     7,    37,     4,
       5,     6,    27,     8,     3,     4,    26,    26,    66,    61,
      49,   102,    51,    71,    26,    54,    55,    56,    57,    27,
      19,     8,    30,    28,    29,    24,    25,    26,    26,    20,
      21,    22,     4,     5,     6,    27,     8,    95,    30,     8,
      30,    31,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    27,    94,    28,    29,     4,     5,
       6,     8,     8,     4,     5,     6,     4,     8,    27,   127,
      28,     4,     5,     6,   126,     8,     4,     5,     6,     4,
       8,    30,    28,    29,    28,    28,    28,    28,    29,     4,
       5,     6,     8,     8,     8,    28,    29,    28,     4,    26,
      28,    29,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    28,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    15,    16,    17,    18,
      19,    20,    21,    22,    31,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    16,    17,    18,
      19,    20,    21,    22,     4,    31,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    17,    18,
      19,    20,    21,    22,     4,    30,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    26,    10,
      27,    27,    27,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    31,    31,    27,     2,    27,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    18,    19,    20,    21,    22,    29,    28,    19,    64
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    33,    34,     0,     8,     9,    35,    35,     4,     7,
       4,    26,    26,    26,    38,    39,     8,    27,    36,    37,
      27,     8,    42,     4,    40,    27,    42,    28,     4,    27,
      30,    30,    28,    28,    27,     4,     5,     6,     8,    28,
      43,    44,    46,    28,     8,     8,    43,    43,    28,    10,
      26,    26,     3,     4,    19,    24,    25,    26,    50,     4,
      45,    47,    29,    46,    30,    31,    43,     4,     4,    29,
      29,    43,    50,    49,    50,    50,    26,    50,    50,    50,
      50,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    31,    10,    43,    45,    29,    27,    29,
      31,    27,    30,    27,    49,    27,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    48,
      41,    31,    49,    31,    27,    29,    28,    43,    29
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    34,    33,    33,    36,    35,    37,    35,    38,
      35,    39,    35,    40,    35,    41,    35,    42,    42,    43,
      43,    44,    44,    45,    45,    46,    47,    48,    46,    46,
      46,    46,    46,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     0,     8,     0,     9,     0,
       8,     0,     9,     0,     8,     0,    13,     2,     4,     1,
       2,     2,     3,     1,     3,     2,     0,     0,     5,     4,
       5,     3,     5,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       3,     1,     4,     1
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
#line 113 "MyBison.y"
          { genpreamble(); }
#line 1217 "MyBison.tab.c"
    break;

  case 3: /* program: $@1 procedure  */
#line 113 "MyBison.y"
                                            {}
#line 1223 "MyBison.tab.c"
    break;

  case 4: /* program: program procedure  */
#line 114 "MyBison.y"
                                            {}
#line 1229 "MyBison.tab.c"
    break;

  case 5: /* $@2: %empty  */
#line 126 "MyBison.y"
                          { is_main = 0; genfuncpreamble((yyvsp[-1].s), P_VOID); }
#line 1235 "MyBison.tab.c"
    break;

  case 6: /* procedure: VOID ID '(' $@2 ')' '{' stmts '}'  */
#line 126 "MyBison.y"
                                                                                                   {genfuncpostamble();}
#line 1241 "MyBison.tab.c"
    break;

  case 7: /* $@3: %empty  */
#line 127 "MyBison.y"
                          { is_main = 0; genfuncpreamble((yyvsp[-1].s), P_VOID); /*para_num = 0;*/ }
#line 1247 "MyBison.tab.c"
    break;

  case 8: /* procedure: VOID ID '(' $@3 paralist ')' '{' stmts '}'  */
#line 127 "MyBison.y"
                                                                                                                     {genfuncpostamble();}
#line 1253 "MyBison.tab.c"
    break;

  case 9: /* $@4: %empty  */
#line 128 "MyBison.y"
                         { is_main = 0; genfuncpreamble((yyvsp[-1].s), P_INT); }
#line 1259 "MyBison.tab.c"
    break;

  case 10: /* procedure: INT ID '(' $@4 ')' '{' stmts '}'  */
#line 128 "MyBison.y"
                                                                                                   {genfuncpostamble();}
#line 1265 "MyBison.tab.c"
    break;

  case 11: /* $@5: %empty  */
#line 129 "MyBison.y"
                         { is_main = 0; genfuncpreamble((yyvsp[-1].s), P_INT); /*para_num = 0;*/ }
#line 1271 "MyBison.tab.c"
    break;

  case 12: /* procedure: INT ID '(' $@5 paralist ')' '{' stmts '}'  */
#line 129 "MyBison.y"
                                                                                                                     {genfuncpostamble();}
#line 1277 "MyBison.tab.c"
    break;

  case 13: /* $@6: %empty  */
#line 130 "MyBison.y"
                               { is_main = 1; genmainpreamble(); }
#line 1283 "MyBison.tab.c"
    break;

  case 14: /* procedure: INT MAIN '(' ')' $@6 '{' stmts '}'  */
#line 130 "MyBison.y"
                                                                                   {}
#line 1289 "MyBison.tab.c"
    break;

  case 15: /* $@7: %empty  */
#line 131 "MyBison.y"
                                                 { is_main = 1; genmainpreamble(); addlocal((yyvsp[-1].s)); addlocal((yyvsp[-4].s)); }
#line 1295 "MyBison.tab.c"
    break;

  case 16: /* procedure: INT MAIN '(' INT ID ',' INT ID ')' $@7 '{' stmts '}'  */
#line 131 "MyBison.y"
                                                                                                                               {}
#line 1301 "MyBison.tab.c"
    break;

  case 17: /* paralist: INT ID  */
#line 153 "MyBison.y"
                  { /*para_num++;*/ /*printf("%s\n", $2);*/ para_declaration((yyvsp[0].s));/*, para_num);*/ /*printf("%d\n", findlocal($2));*/ }
#line 1307 "MyBison.tab.c"
    break;

  case 18: /* paralist: paralist ',' INT ID  */
#line 154 "MyBison.y"
                               { /*para_num++;*/ /*printf("%s\n", $4);*/ para_declaration((yyvsp[0].s));/*, para_num);*/ /*printf("%d\n", findlocal($4));*/ }
#line 1313 "MyBison.tab.c"
    break;

  case 19: /* stmts: stmt  */
#line 162 "MyBison.y"
                        {}
#line 1319 "MyBison.tab.c"
    break;

  case 20: /* stmts: stmts stmt  */
#line 163 "MyBison.y"
                        {}
#line 1325 "MyBison.tab.c"
    break;

  case 21: /* declarations: INT identifier  */
#line 187 "MyBison.y"
                                            {}
#line 1331 "MyBison.tab.c"
    break;

  case 22: /* declarations: declarations ',' identifier  */
#line 188 "MyBison.y"
                                            {}
#line 1337 "MyBison.tab.c"
    break;

  case 23: /* identifier: ID  */
#line 191 "MyBison.y"
                            { var_declaration((yyvsp[0].s)); }
#line 1343 "MyBison.tab.c"
    break;

  case 24: /* identifier: ID '=' exp  */
#line 192 "MyBison.y"
                            { var_declaration((yyvsp[-2].s)); assignment_statement((yyvsp[-2].s), (yyvsp[0].a)); }
#line 1349 "MyBison.tab.c"
    break;

  case 25: /* stmt: declarations ';'  */
#line 196 "MyBison.y"
                            {}
#line 1355 "MyBison.tab.c"
    break;

  case 26: /* $@8: %empty  */
#line 197 "MyBison.y"
           { scope++; pass_scope(scope); /*printf("%d\n", scope);*/ }
#line 1361 "MyBison.tab.c"
    break;

  case 27: /* $@9: %empty  */
#line 197 "MyBison.y"
                                                                            { scope--; pass_scope(scope); /*printf("%d\n", scope);*/ }
#line 1367 "MyBison.tab.c"
    break;

  case 28: /* stmt: '{' $@8 stmts $@9 '}'  */
#line 197 "MyBison.y"
                                                                                                                                                  {}
#line 1373 "MyBison.tab.c"
    break;

  case 29: /* stmt: ID '=' exp ';'  */
#line 198 "MyBison.y"
                            { assignment_statement((yyvsp[-3].s), (yyvsp[-1].a)); }
#line 1379 "MyBison.tab.c"
    break;

  case 30: /* stmt: PRINTLN_INT '(' exp ')' ';'  */
#line 205 "MyBison.y"
                                   { println_int_statement((yyvsp[-2].a)); }
#line 1385 "MyBison.tab.c"
    break;

  case 31: /* stmt: RETURN exp ';'  */
#line 206 "MyBison.y"
                            {
        return_statement((yyvsp[-1].a));
        if (is_main == 1)
            exit_syscall();
        }
#line 1395 "MyBison.tab.c"
    break;

  case 32: /* stmt: ID '(' arglist ')' ';'  */
#line 212 "MyBison.y"
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
#line 1411 "MyBison.tab.c"
    break;

  case 33: /* arglist: exp  */
#line 226 "MyBison.y"
              { arg_num++; /*printf("%d\n", arg_num);*/ /*printf("%d\n", $1->v.intvalue);*/ arg_pass((yyvsp[0].a)); }
#line 1417 "MyBison.tab.c"
    break;

  case 34: /* arglist: exp ',' arglist  */
#line 227 "MyBison.y"
                          { arg_num++; /*printf("%d\n", arg_num);*/ /*printf("%d\n", $1->v.intvalue);*/ arg_pass((yyvsp[-2].a)); }
#line 1423 "MyBison.tab.c"
    break;

  case 35: /* exp: exp '*' exp  */
#line 238 "MyBison.y"
                  { (yyval.a) = mkastnode('*', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1429 "MyBison.tab.c"
    break;

  case 36: /* exp: exp '/' exp  */
#line 239 "MyBison.y"
                  { (yyval.a) = mkastnode('/', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1435 "MyBison.tab.c"
    break;

  case 37: /* exp: exp '%' exp  */
#line 240 "MyBison.y"
                  { (yyval.a) = mkastnode('%', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1441 "MyBison.tab.c"
    break;

  case 38: /* exp: exp '+' exp  */
#line 241 "MyBison.y"
                  { (yyval.a) = mkastnode('+', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1447 "MyBison.tab.c"
    break;

  case 39: /* exp: exp '-' exp  */
#line 242 "MyBison.y"
                  { (yyval.a) = mkastnode('-', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1453 "MyBison.tab.c"
    break;

  case 40: /* exp: exp LGTE exp  */
#line 243 "MyBison.y"
                   { (yyval.a) = mkastnode((yyvsp[-1].fn), (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1459 "MyBison.tab.c"
    break;

  case 41: /* exp: exp EQN exp  */
#line 244 "MyBison.y"
                  { (yyval.a) = mkastnode((yyvsp[-1].fn), (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1465 "MyBison.tab.c"
    break;

  case 42: /* exp: exp '&' exp  */
#line 245 "MyBison.y"
                  { (yyval.a) = mkastnode('&', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1471 "MyBison.tab.c"
    break;

  case 43: /* exp: exp '^' exp  */
#line 246 "MyBison.y"
                  { (yyval.a) = mkastnode('^', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1477 "MyBison.tab.c"
    break;

  case 44: /* exp: exp '|' exp  */
#line 247 "MyBison.y"
                  { (yyval.a) = mkastnode('|', (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1483 "MyBison.tab.c"
    break;

  case 45: /* exp: exp LAND exp  */
#line 248 "MyBison.y"
                   { (yyval.a) = mkastnode(A_LAND, (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1489 "MyBison.tab.c"
    break;

  case 46: /* exp: exp LOR exp  */
#line 249 "MyBison.y"
                  { (yyval.a) = mkastnode(A_LOR, (yyvsp[-2].a), (yyvsp[0].a), 0); }
#line 1495 "MyBison.tab.c"
    break;

  case 47: /* exp: '-' exp  */
#line 250 "MyBison.y"
                           { (yyval.a) = mkastunary(A_UMINUS, (yyvsp[0].a), 0); }
#line 1501 "MyBison.tab.c"
    break;

  case 48: /* exp: '!' exp  */
#line 251 "MyBison.y"
              { (yyval.a) = mkastunary('!', (yyvsp[0].a), 0); }
#line 1507 "MyBison.tab.c"
    break;

  case 49: /* exp: '~' exp  */
#line 252 "MyBison.y"
              { (yyval.a) = mkastunary('~', (yyvsp[0].a), 0); }
#line 1513 "MyBison.tab.c"
    break;

  case 50: /* exp: '(' exp ')'  */
#line 253 "MyBison.y"
                  { (yyval.a) = (yyvsp[-1].a); }
#line 1519 "MyBison.tab.c"
    break;

  case 51: /* exp: INTLIT  */
#line 254 "MyBison.y"
             { (yyval.a) = mkastleaf(A_INTLIT, (yyvsp[0].intval)); }
#line 1525 "MyBison.tab.c"
    break;

  case 52: /* exp: ID '(' arglist ')'  */
#line 262 "MyBison.y"
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
#line 1541 "MyBison.tab.c"
    break;

  case 53: /* exp: ID  */
#line 273 "MyBison.y"
         {
        // printf("%s\n", $1);
        // Check that this identifier exists
        int id = findlocal((yyvsp[0].s));
        if (id == -1)
            yyerror("Unknown variable %s", (yyvsp[0].s));
        // Make a leaf AST node for it
        (yyval.a) = mkastleaf(A_IDENT, id);
        }
#line 1555 "MyBison.tab.c"
    break;


#line 1559 "MyBison.tab.c"

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

#line 294 "MyBison.y"

