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
#line 1 "tree.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <limits.h>
	// #define COUNT 10	

	void yyerror(const char*);
	int yylex();
	extern FILE * yyin, *yyout;
	int x=0;	

	extern int line;
	
	int scope = 0;

	int unaryop = -1;		//unary operator type
	int assignop = -1;		//assignment operator == += -=
	int datatype = -1;		//type specifier
	int assigntype = -1;	//RHS type 
	int idcheck = -1;		//check if ID 
	int check_un = 0;		//check for undeclared variables


	char tempStr[100];		//sprintf

	struct node{
		char token[20];
		char name[20];
		int dtype;
		int scope;
		int lineno;
		int valid;
		union value{
			float f;
			int i;
			char c;
		}val;
		
		struct node *link;

	}*first = NULL, *tmp, *crt, *lhs;

	typedef struct Node{
		struct Node *left;
		struct Node *right;
		char token[100];
		struct Node *val;
		int level;
	}Node;

	typedef struct tree_stack{
		Node *node;
		struct tree_stack *next;
	}tree_stack;

	tree_stack *tree_top = NULL;
	char preBuf[1000000];

	struct node * checksym(char *);
	void addsymbol(struct node *,char *);	
	void addInt(struct node *, int, int);
	void addFloat(struct node *, int, float);
	void addChar(struct node *, int, char);
	void addfunc(struct node *t, int, char *);
	void printsymtable();

	struct node * addtosymbol(struct node * n);
	void cleansymbol();


	//AST 
	void create_node(char *token, int leaf);
	void push_tree(Node *newnode);
	Node *pop_tree();
	void preorder(Node* root);
	void printtree(Node* root);
	int getmaxlevel(Node *root);
	void printGivenLevel(Node* root, int level, int h);
	void get_levels(Node *root, int level);



#line 155 "tree.tab.c"

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

#include "tree.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_HASH = 3,                       /* HASH  */
  YYSYMBOL_INCLUDE = 4,                    /* INCLUDE  */
  YYSYMBOL_IOSTREAM = 5,                   /* IOSTREAM  */
  YYSYMBOL_STRING_LITERAL = 6,             /* STRING_LITERAL  */
  YYSYMBOL_HEADER_LITERAL = 7,             /* HEADER_LITERAL  */
  YYSYMBOL_PRINT = 8,                      /* PRINT  */
  YYSYMBOL_RETURN = 9,                     /* RETURN  */
  YYSYMBOL_10_ = 10,                       /* '+'  */
  YYSYMBOL_11_ = 11,                       /* '-'  */
  YYSYMBOL_12_ = 12,                       /* '/'  */
  YYSYMBOL_13_ = 13,                       /* '*'  */
  YYSYMBOL_14_ = 14,                       /* '%'  */
  YYSYMBOL_15_ = 15,                       /* '='  */
  YYSYMBOL_INTEGER_LITERAL = 16,           /* INTEGER_LITERAL  */
  YYSYMBOL_CHARACTER_LITERAL = 17,         /* CHARACTER_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 18,             /* FLOAT_LITERAL  */
  YYSYMBOL_IDENTIFIER = 19,                /* IDENTIFIER  */
  YYSYMBOL_INC_OP = 20,                    /* INC_OP  */
  YYSYMBOL_DEC_OP = 21,                    /* DEC_OP  */
  YYSYMBOL_LE_OP = 22,                     /* LE_OP  */
  YYSYMBOL_GE_OP = 23,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 24,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 25,                     /* NE_OP  */
  YYSYMBOL_MUL_ASSIGN = 26,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 27,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 28,                /* MOD_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 29,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 30,                /* SUB_ASSIGN  */
  YYSYMBOL_CHAR = 31,                      /* CHAR  */
  YYSYMBOL_INT = 32,                       /* INT  */
  YYSYMBOL_FLOAT = 33,                     /* FLOAT  */
  YYSYMBOL_VOID = 34,                      /* VOID  */
  YYSYMBOL_FOR = 35,                       /* FOR  */
  YYSYMBOL_WHILE = 36,                     /* WHILE  */
  YYSYMBOL_IF = 37,                        /* IF  */
  YYSYMBOL_38_ = 38,                       /* '<'  */
  YYSYMBOL_39_ = 39,                       /* '>'  */
  YYSYMBOL_40_ = 40,                       /* '{'  */
  YYSYMBOL_41_ = 41,                       /* '}'  */
  YYSYMBOL_42_ = 42,                       /* ';'  */
  YYSYMBOL_43_ = 43,                       /* '('  */
  YYSYMBOL_44_ = 44,                       /* ')'  */
  YYSYMBOL_45_ = 45,                       /* ','  */
  YYSYMBOL_46_ = 46,                       /* '?'  */
  YYSYMBOL_47_ = 47,                       /* ':'  */
  YYSYMBOL_48_ = 48,                       /* '!'  */
  YYSYMBOL_49_ = 49,                       /* '~'  */
  YYSYMBOL_50_INC_OP_ = 50,                /* "INC_OP"  */
  YYSYMBOL_51_DEC_OP_ = 51,                /* "DEC_OP"  */
  YYSYMBOL_YYACCEPT = 52,                  /* $accept  */
  YYSYMBOL_S = 53,                         /* S  */
  YYSYMBOL_program = 54,                   /* program  */
  YYSYMBOL_translation_unit = 55,          /* translation_unit  */
  YYSYMBOL_ext_dec = 56,                   /* ext_dec  */
  YYSYMBOL_libraries = 57,                 /* libraries  */
  YYSYMBOL_compound_statement = 58,        /* compound_statement  */
  YYSYMBOL_block_item_list = 59,           /* block_item_list  */
  YYSYMBOL_block_item = 60,                /* block_item  */
  YYSYMBOL_printstat = 61,                 /* printstat  */
  YYSYMBOL_declaration = 62,               /* declaration  */
  YYSYMBOL_statement = 63,                 /* statement  */
  YYSYMBOL_condition_statement = 64,       /* condition_statement  */
  YYSYMBOL_iteration_statement = 65,       /* iteration_statement  */
  YYSYMBOL_type_specifier = 66,            /* type_specifier  */
  YYSYMBOL_init_declarator_list = 67,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 68,           /* init_declarator  */
  YYSYMBOL_69_1 = 69,                      /* $@1  */
  YYSYMBOL_assignment_expression = 70,     /* assignment_expression  */
  YYSYMBOL_71_2 = 71,                      /* $@2  */
  YYSYMBOL_assignment_operator = 72,       /* assignment_operator  */
  YYSYMBOL_conditional_expression = 73,    /* conditional_expression  */
  YYSYMBOL_expression_statement = 74,      /* expression_statement  */
  YYSYMBOL_expression = 75,                /* expression  */
  YYSYMBOL_primary_expression = 76,        /* primary_expression  */
  YYSYMBOL_postfix_expression = 77,        /* postfix_expression  */
  YYSYMBOL_unary_expression = 78,          /* unary_expression  */
  YYSYMBOL_unary_operator = 79,            /* unary_operator  */
  YYSYMBOL_equality_expression = 80,       /* equality_expression  */
  YYSYMBOL_relational_expression = 81,     /* relational_expression  */
  YYSYMBOL_additive_expression = 82,       /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 83, /* multiplicative_expression  */
  YYSYMBOL_function_definition = 84,       /* function_definition  */
  YYSYMBOL_function_call = 85,             /* function_call  */
  YYSYMBOL_declarator = 86,                /* declarator  */
  YYSYMBOL_parameter_list = 87,            /* parameter_list  */
  YYSYMBOL_parameter_declaration = 88,     /* parameter_declaration  */
  YYSYMBOL_identifier_list = 89            /* identifier_list  */
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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   253

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  168

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


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
       2,     2,     2,    48,     2,     2,     2,    14,     2,     2,
      43,    44,    13,    10,    45,    11,     2,    12,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    42,
      38,    15,    39,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,    49,     2,     2,     2,
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
       5,     6,     7,     8,     9,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    50,    51
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   127,   127,   135,   136,   137,   142,   143,   148,   149,
     154,   159,   160,   165,   166,   174,   175,   176,   177,   181,
     186,   187,   192,   197,   209,   210,   211,   215,   221,   225,
     233,   234,   235,   236,   241,   242,   247,   247,   345,   410,
     411,   411,   624,   625,   626,   627,   628,   629,   634,   635,
     650,   651,   656,   657,   662,   694,   703,   721,   739,   746,
     747,   748,   753,   754,   782,   783,   784,   785,   786,   787,
     792,   793,   802,   814,   815,   824,   833,   842,   855,   856,
     861,   870,   871,   876,   888,   905,   923,   949,   950,   955,
     962,   963,   964,   969,   970,   975,   976,   981,   982
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
  "\"end of file\"", "error", "\"invalid token\"", "HASH", "INCLUDE",
  "IOSTREAM", "STRING_LITERAL", "HEADER_LITERAL", "PRINT", "RETURN", "'+'",
  "'-'", "'/'", "'*'", "'%'", "'='", "INTEGER_LITERAL",
  "CHARACTER_LITERAL", "FLOAT_LITERAL", "IDENTIFIER", "INC_OP", "DEC_OP",
  "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "MUL_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "CHAR", "INT", "FLOAT", "VOID",
  "FOR", "WHILE", "IF", "'<'", "'>'", "'{'", "'}'", "';'", "'('", "')'",
  "','", "'?'", "':'", "'!'", "'~'", "\"INC_OP\"", "\"DEC_OP\"", "$accept",
  "S", "program", "translation_unit", "ext_dec", "libraries",
  "compound_statement", "block_item_list", "block_item", "printstat",
  "declaration", "statement", "condition_statement", "iteration_statement",
  "type_specifier", "init_declarator_list", "init_declarator", "$@1",
  "assignment_expression", "$@2", "assignment_operator",
  "conditional_expression", "expression_statement", "expression",
  "primary_expression", "postfix_expression", "unary_expression",
  "unary_operator", "equality_expression", "relational_expression",
  "additive_expression", "multiplicative_expression",
  "function_definition", "function_call", "declarator", "parameter_list",
  "parameter_declaration", "identifier_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-139)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-93)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     160,     6,  -139,  -139,  -139,  -139,  -139,    15,  -139,    -8,
    -139,  -139,     8,  -139,    26,    -2,  -139,  -139,    20,    51,
    -139,    26,    71,   168,  -139,   160,    57,    63,  -139,    72,
    -139,    86,    22,  -139,  -139,  -139,  -139,  -139,    94,   116,
     121,   126,  -139,  -139,   117,  -139,  -139,  -139,  -139,  -139,
     107,  -139,   134,  -139,  -139,  -139,  -139,    72,  -139,  -139,
    -139,    56,  -139,    -1,   189,   117,   -12,    45,    75,   118,
     146,   137,  -139,  -139,    80,   177,  -139,   188,  -139,  -139,
     157,   117,   208,  -139,   224,  -139,  -139,    22,   117,   117,
     190,  -139,  -139,  -139,  -139,   117,  -139,  -139,   198,  -139,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,  -139,   176,  -139,  -139,    23,  -139,   195,   160,
    -139,   192,    22,  -139,   159,   167,  -139,  -139,  -139,  -139,
    -139,  -139,  -139,  -139,   117,    45,    45,   184,    75,    75,
      75,    75,   118,   118,  -139,  -139,  -139,   204,   194,  -139,
    -139,  -139,  -139,   117,   117,   135,   135,  -139,   117,   205,
     196,   199,  -139,  -139,  -139,  -139,   135,  -139
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    89,    31,    32,    33,    30,     0,     2,     5,
       6,     8,     0,     9,     0,     0,     1,     7,    38,     0,
      34,     0,     0,     0,    86,     0,     0,     0,    22,     0,
      85,     0,     0,    64,    65,    55,    57,    56,    54,     0,
       0,     0,    11,    50,     0,    66,    67,    68,    69,    23,
       0,    13,     0,    15,    16,    26,    25,     0,    52,    39,
      24,     0,    59,    62,    81,     0,    48,    70,    73,    78,
       0,     0,    97,    92,    96,     0,    93,     0,     4,    10,
       0,     0,    38,    35,     0,    54,    18,     0,     0,     0,
       0,    12,    14,    19,    51,     0,    60,    61,     0,    63,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,    95,    90,     0,    91,     0,     0,
      37,     0,     0,    81,     0,     0,    58,    53,    42,    45,
      46,    47,    43,    44,     0,    71,    72,     0,    76,    77,
      74,    75,    79,    80,    83,    82,    84,    88,     0,    94,
      98,     3,    20,     0,     0,     0,     0,    41,     0,    87,
       0,     0,    29,    27,    49,    21,     0,    28
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -139,  -139,   -22,  -139,   233,  -139,     0,  -139,   200,  -139,
     -13,  -138,  -139,  -139,   -21,  -139,   220,  -139,   -73,  -139,
    -139,    93,   -28,   -44,  -139,  -139,   -58,  -139,  -139,    73,
     -29,   138,  -139,  -139,    -6,  -139,   136,   140
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     7,     8,     9,    10,    80,    49,    50,    51,    52,
      11,    54,    55,    56,    12,    19,    20,    27,    58,    98,
     134,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    13,    70,    14,    75,    76,    77
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      90,    57,    74,    78,    86,    25,    21,    99,   120,    53,
      15,     2,   100,   101,    24,    16,    71,   162,   163,    96,
      97,    30,   127,     3,     4,     5,     6,    18,   167,    57,
     123,   123,    33,    34,   102,   -36,    26,    53,    35,    36,
      37,    85,   123,   123,    71,   123,   123,   123,   123,   123,
     123,   144,   145,   146,     3,     4,     5,     6,   137,   122,
     -89,   157,    79,   -89,    43,    44,    22,   103,   104,    23,
      45,    46,    47,    48,   138,   139,   140,   141,    81,    31,
      32,    33,    34,   105,   106,   107,   108,    35,    36,    37,
      38,    82,    74,    28,   154,    74,    29,   151,    94,   114,
     123,    95,     3,     4,     5,     6,    39,    40,    41,   160,
     161,    22,    42,    43,    44,    31,    32,    33,    34,    45,
      46,    47,    48,    35,    36,    37,    38,    33,    34,    84,
     109,   110,   111,    35,    36,    37,    85,   -89,     3,     4,
       5,     6,    39,    40,    41,    33,    34,    22,    91,    43,
      44,    35,    36,    37,    85,    45,    46,    47,    48,    87,
      44,   124,   125,     1,    88,    45,    46,    47,    48,    89,
      39,    40,    41,   135,   136,    22,    93,    43,    44,     2,
     113,   103,   104,    45,    46,    47,    48,    72,   112,   103,
     104,     3,     4,     5,     6,    72,   119,   105,   106,     3,
       4,     5,     6,   155,   -40,   105,   106,     3,     4,     5,
       6,   156,    73,   128,   150,   -40,   -40,   -40,   -40,   -40,
     147,   115,   116,   -36,   129,   130,   131,   132,   133,    95,
     121,   158,   117,   118,   126,    95,   152,   153,   159,   118,
     165,    95,    17,   166,    95,   142,   143,   -92,   -91,    83,
      92,   164,   149,   148
};

static const yytype_uint8 yycheck[] =
{
      44,    22,    23,    25,    32,     7,    12,    65,    81,    22,
       4,    19,    24,    25,    14,     0,    22,   155,   156,    20,
      21,    21,    95,    31,    32,    33,    34,    19,   166,    50,
      88,    89,    10,    11,    46,    15,    38,    50,    16,    17,
      18,    19,   100,   101,    50,   103,   104,   105,   106,   107,
     108,   109,   110,   111,    31,    32,    33,    34,   102,    87,
      40,   134,     5,    43,    42,    43,    40,    22,    23,    43,
      48,    49,    50,    51,   103,   104,   105,   106,    15,     8,
       9,    10,    11,    38,    39,    10,    11,    16,    17,    18,
      19,    19,   113,    42,   122,   116,    45,   119,    42,    19,
     158,    45,    31,    32,    33,    34,    35,    36,    37,   153,
     154,    40,    41,    42,    43,     8,     9,    10,    11,    48,
      49,    50,    51,    16,    17,    18,    19,    10,    11,    43,
      12,    13,    14,    16,    17,    18,    19,    43,    31,    32,
      33,    34,    35,    36,    37,    10,    11,    40,    41,    42,
      43,    16,    17,    18,    19,    48,    49,    50,    51,    43,
      43,    88,    89,     3,    43,    48,    49,    50,    51,    43,
      35,    36,    37,   100,   101,    40,    42,    42,    43,    19,
      43,    22,    23,    48,    49,    50,    51,    19,    42,    22,
      23,    31,    32,    33,    34,    19,    39,    38,    39,    31,
      32,    33,    34,    44,    15,    38,    39,    31,    32,    33,
      34,    44,    44,    15,    19,    26,    27,    28,    29,    30,
      44,    44,    45,    15,    26,    27,    28,    29,    30,    45,
       6,    47,    44,    45,    44,    45,    44,    45,    44,    45,
      44,    45,     9,    44,    45,   107,   108,    43,    43,    29,
      50,   158,   116,   113
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    19,    31,    32,    33,    34,    53,    54,    55,
      56,    62,    66,    84,    86,     4,     0,    56,    19,    67,
      68,    86,    40,    43,    58,     7,    38,    69,    42,    45,
      58,     8,     9,    10,    11,    16,    17,    18,    19,    35,
      36,    37,    41,    42,    43,    48,    49,    50,    51,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    70,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      85,    86,    19,    44,    66,    87,    88,    89,    54,     5,
      57,    15,    19,    68,    43,    19,    74,    43,    43,    43,
      75,    41,    60,    42,    42,    45,    20,    21,    71,    78,
      24,    25,    46,    22,    23,    38,    39,    10,    11,    12,
      13,    14,    42,    43,    19,    44,    45,    44,    45,    39,
      70,     6,    74,    78,    81,    81,    44,    70,    15,    26,
      27,    28,    29,    30,    72,    81,    81,    75,    82,    82,
      82,    82,    83,    83,    78,    78,    78,    44,    89,    88,
      19,    54,    44,    45,    74,    44,    44,    70,    47,    44,
      75,    75,    63,    63,    73,    44,    44,    63
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    54,    54,    54,    55,    55,    56,    56,
      57,    58,    58,    59,    59,    60,    60,    60,    60,    60,
      61,    61,    62,    63,    63,    63,    63,    64,    65,    65,
      66,    66,    66,    66,    67,    67,    69,    68,    68,    70,
      71,    70,    72,    72,    72,    72,    72,    72,    73,    73,
      74,    74,    75,    75,    76,    76,    76,    76,    76,    77,
      77,    77,    78,    78,    79,    79,    79,    79,    79,    79,
      80,    80,    80,    81,    81,    81,    81,    81,    82,    82,
      82,    83,    83,    83,    83,    84,    84,    85,    85,    86,
      86,    86,    86,    87,    87,    88,    88,    89,    89
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     6,     4,     1,     1,     2,     1,     1,
       1,     2,     3,     1,     2,     1,     1,     2,     2,     2,
       4,     6,     3,     1,     1,     1,     1,     5,     7,     5,
       1,     1,     1,     1,     1,     3,     0,     4,     1,     1,
       0,     4,     1,     1,     1,     1,     1,     1,     1,     5,
       1,     2,     1,     3,     1,     1,     1,     1,     3,     1,
       2,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     2,     4,     3,     1,
       4,     4,     3,     1,     3,     2,     1,     1,     3
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
  case 2: /* S: program  */
#line 127 "tree.y"
            {
				cleansymbol();	
                printsymtable();
                return 0;
            }
#line 1372 "tree.tab.c"
    break;

  case 14: /* block_item_list: block_item_list block_item  */
#line 167 "tree.y"
                        {
				create_node("assign", 0);
			}
#line 1380 "tree.tab.c"
    break;

  case 18: /* block_item: RETURN expression_statement  */
#line 178 "tree.y"
                        {
				create_node("return", 1);
			}
#line 1388 "tree.tab.c"
    break;

  case 23: /* statement: compound_statement  */
#line 197 "tree.y"
                             {
						struct node *ftp;
						ftp = first;
						while(ftp!=NULL){
							if(ftp->scope == scope && ftp->valid == 1){
								ftp->valid = 0;
							}
							ftp=ftp->link;
						}
						scope--;

					}
#line 1405 "tree.tab.c"
    break;

  case 27: /* condition_statement: IF '(' relational_expression ')' statement  */
#line 215 "tree.y"
                                                     {create_node("if", 0);}
#line 1411 "tree.tab.c"
    break;

  case 28: /* iteration_statement: FOR '(' expression_statement expression_statement expression ')' statement  */
#line 222 "tree.y"
                        { 
				create_node("for", 0); 
			}
#line 1419 "tree.tab.c"
    break;

  case 29: /* iteration_statement: WHILE '(' relational_expression ')' statement  */
#line 226 "tree.y"
        {
		create_node("while", 0); 
	}
#line 1427 "tree.tab.c"
    break;

  case 30: /* type_specifier: VOID  */
#line 233 "tree.y"
                {	datatype = (yyvsp[0].ival); }
#line 1433 "tree.tab.c"
    break;

  case 31: /* type_specifier: CHAR  */
#line 234 "tree.y"
                {	datatype = (yyvsp[0].ival); }
#line 1439 "tree.tab.c"
    break;

  case 32: /* type_specifier: INT  */
#line 235 "tree.y"
                {	datatype = (yyvsp[0].ival); }
#line 1445 "tree.tab.c"
    break;

  case 33: /* type_specifier: FLOAT  */
#line 236 "tree.y"
                {	datatype = (yyvsp[0].ival); }
#line 1451 "tree.tab.c"
    break;

  case 36: /* $@1: %empty  */
#line 247 "tree.y"
                     { create_node((yyvsp[0].ptr)->name, 1); }
#line 1457 "tree.tab.c"
    break;

  case 37: /* init_declarator: IDENTIFIER $@1 '=' assignment_expression  */
#line 248 "tree.y"
                                        {	
						if((yyvsp[-3].ptr)->dtype !=- 1 && (yyvsp[-3].ptr)->scope < scope && (yyvsp[-3].ptr)->valid == 1){
																		
							struct node *ftp, *nnode;
							nnode = (struct node *)malloc(sizeof(struct node));
							ftp = first;
							while(ftp->link!=NULL){
								ftp = ftp->link;
							}
							addsymbol(nnode,(yyvsp[-3].ptr)->name);	
							ftp->link = nnode;
							nnode->link = NULL;
							(yyvsp[-3].ptr) = nnode;

							if (datatype == 0){	
								
								addInt((yyvsp[-3].ptr), 0, (yyvsp[0].fval));
								if(assigntype == 1){
									printf("Line:%d: ", line);
									printf("\033[1;35m"); 
									printf("warning: ");
									printf("\033[0m");
									printf("\'float\' to \'int\' \n\n");
								}
							}
							else if(datatype == 1){
								
								addFloat((yyvsp[-3].ptr), 1, (yyvsp[0].fval));
								if(assigntype == 2){
									printf("Line:%d: ", line);
									printf("\033[1;35m"); 
									printf("warning: ");
									printf("\033[0m");
									printf(" \'char\' to \'float\' \n\n");
								}
							}
							else if(datatype == 2){
								float tempf = (float)(yyvsp[0].fval);
								addChar((yyvsp[-3].ptr), 2, (int)tempf);

								if(assigntype == 1){
									printf("Line:%d: ", line);
									
									printf(" \'float\' to \'char\' \n\n");
								}
							}
							x = datatype;
							
							create_node("=", 0);

						}

						
						else if((yyvsp[-3].ptr)->dtype !=- 1){

								printf("Line:%d: ", line);
								
								printf("redefinition of \'%s\' \n",  (yyvsp[-3].ptr)->name);
						}
						else{
							
							
							create_node("=", 0);

							if (datatype == 0){	
								
								addInt((yyvsp[-3].ptr), 0, (yyvsp[0].fval));
								if(assigntype == 1){
									printf("Line:%d: ", line);
									
									printf("\'float\' to \'int\' \n\n");
								}
							}
							else if(datatype == 1){
								
								addFloat((yyvsp[-3].ptr), 1, (yyvsp[0].fval));
								if(assigntype == 2){
									printf("Line:%d: ", line);
									
									printf("\'char\' to \'float\' \n\n");
								}
							}
							else if(datatype == 2){
								float tempf = (float)(yyvsp[0].fval);
								addChar((yyvsp[-3].ptr), 2, (int)tempf);

								if(assigntype == 1){
									printf("Line:%d: ", line);
									
									printf("\'float\' to \'char\' \n\n");
								}
							}
							x = datatype;
							
						}
					}
#line 1558 "tree.tab.c"
    break;

  case 38: /* init_declarator: IDENTIFIER  */
#line 345 "tree.y"
                        {	//previous. a , dtype = 1(int)
						// printf("type = %d\nscope = %d\nvalid = %d", $1->dtype, $1->scope, $1->valid);
						if((yyvsp[0].ptr)->dtype !=- 1 && (yyvsp[0].ptr)->scope < scope && (yyvsp[0].ptr)->valid == 1){
							// printf("case 1 \n" );
																		
							struct node *ftp, *nnode;
							nnode = (struct node *)malloc(sizeof(struct node));
							ftp = first;
							while(ftp->link!=NULL){
								ftp = ftp->link;
							}
							addsymbol(nnode,(yyvsp[0].ptr)->name);	
							ftp->link = nnode;
							nnode->link = NULL;							
							(yyvsp[0].ptr) = nnode;
							
							if (datatype == 0){	
								addInt((yyvsp[0].ptr), 0, INT_MIN);
							}
							else if(datatype == 1){
								addFloat((yyvsp[0].ptr), 1, INT_MIN);
							}
							else if(datatype == 2){
								addChar((yyvsp[0].ptr), 2, '-');
		
							}
							x = datatype;

							char buff[20];
							strcpy(buff, "Dc ");
							strcat(buff, (yyvsp[0].ptr)->name);
							create_node(buff, 1);

						}
						else if((yyvsp[0].ptr)->dtype !=- 1 ){
							printf("Line:%d: ", line);
							
							printf("redefinition of \'%s\' \n", (yyvsp[0].ptr)->name);
						
						}else{
							

							if (datatype == 0){	
								addInt((yyvsp[0].ptr), 0, INT_MIN);
							}
							else if(datatype == 1){
								addFloat((yyvsp[0].ptr), 1, INT_MIN);
							}
							else if(datatype == 2){
								addChar((yyvsp[0].ptr), 2, '-');
		
							}
							x = datatype;

							char buff[20];
							strcpy(buff, "Dc ");
							strcat(buff, (yyvsp[0].ptr)->name);
							create_node(buff, 1);
						
						}
					}
#line 1624 "tree.tab.c"
    break;

  case 39: /* assignment_expression: conditional_expression  */
#line 410 "tree.y"
                                        {	(yyval.fval) = (yyvsp[0].fval); }
#line 1630 "tree.tab.c"
    break;

  case 40: /* $@2: %empty  */
#line 411 "tree.y"
                                { crt = lhs; }
#line 1636 "tree.tab.c"
    break;

  case 41: /* assignment_expression: unary_expression $@2 assignment_operator assignment_expression  */
#line 412 "tree.y"
                        {							
				switch(assignop){
					case 0: if(idcheck == 1){
								create_node("=", 0);
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										
										printf("\'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)(yyvsp[0].fval);
									
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										
										printf("\'char\' to \'float\' \n\n");
									}
									crt->val.f = (yyvsp[0].fval);
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										
										printf("\'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)(yyvsp[0].fval));
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 1: if(idcheck == 1){
								create_node("+=", 0);
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
								
										printf("\'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)(yyvsp[-3].fval) + (int)(yyvsp[0].fval);
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										
										printf("\'char\' to \'float\' \n\n");
									}
									crt->val.f = (yyvsp[-3].fval)+ (yyvsp[0].fval);
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										
										printf(" \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)(yyvsp[-3].fval) + (int)(yyvsp[0].fval));
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 2:	if(idcheck == 1){
							create_node("-=", 0);
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										
										printf("\'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)(yyvsp[-3].fval) - (int)(yyvsp[0].fval);
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										
										printf("\'char\' to \'float\' \n\n");
									}
									crt->val.f = (yyvsp[-3].fval) - (yyvsp[0].fval);
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										
										printf("\'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)(yyvsp[-3].fval) - (int)(yyvsp[0].fval));
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 3:	if(idcheck == 1){
								create_node("*=", 0);
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										
										printf("\'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)(yyvsp[-3].fval) * (int)(yyvsp[0].fval);
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										
										printf("\'char\' to \'float\' \n\n");
									}
									crt->val.f = (yyvsp[-3].fval) * (yyvsp[0].fval);
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										
										printf("\'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)(yyvsp[-3].fval) * (int)(yyvsp[0].fval));
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 4:	if(idcheck == 1){
								create_node("/=", 0);
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										
										printf(" \'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)(yyvsp[-3].fval) / (int)(yyvsp[0].fval);
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										
										printf("\'char\' to \'float\' \n\n");
									}
									crt->val.f = (yyvsp[-3].fval) / (yyvsp[0].fval);
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										
										printf("implicit conversion from \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)(yyvsp[-3].fval) / (int)(yyvsp[0].fval));
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;

					case 5:	if(idcheck == 1){
								create_node("%=", 0);
								if(crt->dtype == 0){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										
										printf("implicit conversion from \'float\' to \'int\' \n\n");
									}
									crt->val.i = (int)(yyvsp[-3].fval) % (int)(yyvsp[0].fval);
								}
								else if(crt->dtype == 1){
									if(assigntype == 2){
										printf("Line:%d: ", line);
										
										printf("implicit conversion from \'char\' to \'float\' \n\n");
									}
									crt->val.f = (int)(yyvsp[-3].fval) % (int)(yyvsp[0].fval);
								}
								else if(crt->dtype == 2){
									if(assigntype == 1){
										printf("Line:%d: ", line);
										
										printf("implicit conversion from \'float\' to \'char\' \n\n");
									}
									crt->val.c = (char)((int)(yyvsp[-3].fval) % (int)(yyvsp[0].fval));
								}
							}
							else{
								printf("We'll see later\n");
							}
							crt = NULL;
							break;


				}
				assignop = -1;
				assigntype = -1;
			}
#line 1847 "tree.tab.c"
    break;

  case 42: /* assignment_operator: '='  */
#line 624 "tree.y"
                                {	assignop = 0;	}
#line 1853 "tree.tab.c"
    break;

  case 43: /* assignment_operator: ADD_ASSIGN  */
#line 625 "tree.y"
                        {	assignop = 1;	}
#line 1859 "tree.tab.c"
    break;

  case 44: /* assignment_operator: SUB_ASSIGN  */
#line 626 "tree.y"
                        {	assignop = 2;	}
#line 1865 "tree.tab.c"
    break;

  case 45: /* assignment_operator: MUL_ASSIGN  */
#line 627 "tree.y"
                        {	assignop = 3;	}
#line 1871 "tree.tab.c"
    break;

  case 46: /* assignment_operator: DIV_ASSIGN  */
#line 628 "tree.y"
                        {	assignop = 4;	}
#line 1877 "tree.tab.c"
    break;

  case 47: /* assignment_operator: MOD_ASSIGN  */
#line 629 "tree.y"
                        {	assignop = 5;	}
#line 1883 "tree.tab.c"
    break;

  case 48: /* conditional_expression: equality_expression  */
#line 634 "tree.y"
                                {	(yyval.fval) = (yyvsp[0].fval);	}
#line 1889 "tree.tab.c"
    break;

  case 49: /* conditional_expression: equality_expression '?' expression ':' conditional_expression  */
#line 636 "tree.y"
                        {
				create_node("else", 0);
				create_node("if", 0);
				if((yyvsp[-4].fval) == 1){
					(yyval.fval) = (yyvsp[-2].fval);

				}else{
					(yyval.fval) = (yyvsp[0].fval);
				}
			}
#line 1904 "tree.tab.c"
    break;

  case 50: /* expression_statement: ';'  */
#line 650 "tree.y"
                                        {				}
#line 1910 "tree.tab.c"
    break;

  case 51: /* expression_statement: expression ';'  */
#line 651 "tree.y"
                                {				}
#line 1916 "tree.tab.c"
    break;

  case 52: /* expression: assignment_expression  */
#line 656 "tree.y"
                                        {		}
#line 1922 "tree.tab.c"
    break;

  case 53: /* expression: expression ',' assignment_expression  */
#line 657 "tree.y"
                                               {		}
#line 1928 "tree.tab.c"
    break;

  case 54: /* primary_expression: IDENTIFIER  */
#line 663 "tree.y"
                                {					
					idcheck = 1;
					lhs = (yyvsp[0].ptr);

					if((yyvsp[0].ptr)->dtype == -1 && check_un == 0){

						printf("Line:%d: ", line);
						
						printf("use of undeclared identifier \'%s\' \n\n", (yyvsp[0].ptr)->name);

						check_un = 0;		// set check_un = -1

					}
					else if((yyvsp[0].ptr)->dtype == 0){
						(yyval.fval) = (yyvsp[0].ptr)->val.i;
						assigntype = 0;
						create_node((yyvsp[0].ptr)->name, 1);
					}
					else if((yyvsp[0].ptr)->dtype == 1){
						(yyval.fval) = (yyvsp[0].ptr)->val.f;
						assigntype = 1;
						create_node((yyvsp[0].ptr)->name, 1);
					}
					else if((yyvsp[0].ptr)->dtype == 2){
						(yyval.fval) = (yyvsp[0].ptr)->val.c;
						assigntype = 2;
						create_node((yyvsp[0].ptr)->name, 1);
					}
						
									
				}
#line 1964 "tree.tab.c"
    break;

  case 55: /* primary_expression: INTEGER_LITERAL  */
#line 695 "tree.y"
                                {
					(yyval.fval) = (yyvsp[0].ival);
					assigntype = 0;
				
					sprintf(tempStr, "%d", (int)(yyvsp[0].ival));
					create_node(tempStr, 1);
				}
#line 1976 "tree.tab.c"
    break;

  case 56: /* primary_expression: FLOAT_LITERAL  */
#line 704 "tree.y"
                                {	
					assigntype = 1;
					if(datatype == 1){
						(yyval.fval) = (yyvsp[0].fval);
					}
					else if(datatype == 0){
						
						(yyval.fval) = (int)(yyvsp[0].fval);
					}
					else if(datatype == 2){

						(yyval.fval) = (int)(yyvsp[0].fval);
					}

					sprintf(tempStr, "%f", (yyvsp[0].fval));
					create_node(tempStr, 1);
				}
#line 1998 "tree.tab.c"
    break;

  case 57: /* primary_expression: CHARACTER_LITERAL  */
#line 722 "tree.y"
                                {	
					assigntype = 2;
					if(datatype == 2){
						int tempc = (int)(yyvsp[0].cval);
						(yyval.fval) =  (float)tempc;
					}
					else if(datatype == 0){
						(yyval.fval) = (int)(yyvsp[0].cval);
					}
					else if(datatype == 1){
						
						(yyval.fval) = (int)(yyvsp[0].cval);
					}

					sprintf(tempStr, "%c", (yyvsp[0].cval));
					create_node(tempStr, 1);
				}
#line 2020 "tree.tab.c"
    break;

  case 58: /* primary_expression: '(' expression ')'  */
#line 740 "tree.y"
                                {
					(yyval.fval) = (yyvsp[-1].fval);
				}
#line 2028 "tree.tab.c"
    break;

  case 59: /* postfix_expression: primary_expression  */
#line 746 "tree.y"
                                        {	(yyval.fval) = (yyvsp[0].fval);	}
#line 2034 "tree.tab.c"
    break;

  case 60: /* postfix_expression: postfix_expression INC_OP  */
#line 747 "tree.y"
                                        {	(yyvsp[-1].fval)++; (yyval.fval) = (yyvsp[-1].fval);	create_node("++", 0); }
#line 2040 "tree.tab.c"
    break;

  case 61: /* postfix_expression: postfix_expression DEC_OP  */
#line 748 "tree.y"
                                    {	(yyvsp[-1].fval)--; (yyval.fval) = (yyvsp[-1].fval);	create_node("--", 0); }
#line 2046 "tree.tab.c"
    break;

  case 62: /* unary_expression: postfix_expression  */
#line 753 "tree.y"
                                {	(yyval.fval) = (yyvsp[0].fval);	}
#line 2052 "tree.tab.c"
    break;

  case 63: /* unary_expression: unary_operator unary_expression  */
#line 755 "tree.y"
                                {
					switch(unaryop){
						case 1:	(yyval.fval) = (yyvsp[0].fval);
								create_node("'+'", 0);
								break;
						case 2:	(yyval.fval) = -(yyvsp[0].fval);
								create_node("'+'", 0);
								break;
						case 3:	(yyval.fval) = !(yyvsp[0].fval);
								create_node("!", 0);
								break;
						case 4:	(yyval.fval) = ~((int)(yyvsp[0].fval));
								create_node("~", 0);
								break;	
						case 5:	(yyval.fval) = ++(yyvsp[0].fval);
								create_node("++", 0);							
								break;
						case 6:	(yyval.fval) = --(yyvsp[0].fval);
								create_node("--", 0);
								break;		
					}
					unaryop = -1;
				}
#line 2080 "tree.tab.c"
    break;

  case 64: /* unary_operator: '+'  */
#line 782 "tree.y"
                        {	unaryop = 1;	}
#line 2086 "tree.tab.c"
    break;

  case 65: /* unary_operator: '-'  */
#line 783 "tree.y"
                        {	unaryop = 2;	}
#line 2092 "tree.tab.c"
    break;

  case 66: /* unary_operator: '!'  */
#line 784 "tree.y"
                        {	unaryop = 3;	}
#line 2098 "tree.tab.c"
    break;

  case 67: /* unary_operator: '~'  */
#line 785 "tree.y"
                        {	unaryop = 4;	}
#line 2104 "tree.tab.c"
    break;

  case 68: /* unary_operator: "INC_OP"  */
#line 786 "tree.y"
                        {	unaryop = 5;	}
#line 2110 "tree.tab.c"
    break;

  case 69: /* unary_operator: "DEC_OP"  */
#line 787 "tree.y"
                        {	unaryop = 6;	}
#line 2116 "tree.tab.c"
    break;

  case 70: /* equality_expression: relational_expression  */
#line 792 "tree.y"
                                {	(yyval.fval) = (yyvsp[0].fval);	}
#line 2122 "tree.tab.c"
    break;

  case 71: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 794 "tree.y"
                                { 
					create_node("==", 0);
					if((yyvsp[-2].fval) == (yyvsp[0].fval))
						(yyval.fval) = 1;
					else
						(yyval.fval) = 0;

				}
#line 2135 "tree.tab.c"
    break;

  case 72: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 803 "tree.y"
                                { 
					create_node("!=", 0);
					if((yyvsp[-2].fval) != (yyvsp[0].fval))
						(yyval.fval) = 1;
					else
						(yyval.fval) = 0;
				}
#line 2147 "tree.tab.c"
    break;

  case 73: /* relational_expression: additive_expression  */
#line 814 "tree.y"
                                {	(yyval.fval) = (yyvsp[0].fval);	}
#line 2153 "tree.tab.c"
    break;

  case 74: /* relational_expression: relational_expression '<' additive_expression  */
#line 816 "tree.y"
                                { 
					create_node("<", 0);
					if((yyvsp[-2].fval) < (yyvsp[0].fval))
						(yyval.fval) = 1;
					else
						(yyval.fval) = 0;

				}
#line 2166 "tree.tab.c"
    break;

  case 75: /* relational_expression: relational_expression '>' additive_expression  */
#line 825 "tree.y"
                                { 
					create_node(">", 0);
					if((yyvsp[-2].fval) > (yyvsp[0].fval))
						(yyval.fval) = 1;
					else
						(yyval.fval) = 0;

				}
#line 2179 "tree.tab.c"
    break;

  case 76: /* relational_expression: relational_expression LE_OP additive_expression  */
#line 834 "tree.y"
                                { 
					create_node("<=", 0);
					if((yyvsp[-2].fval) <= (yyvsp[0].fval))
						(yyval.fval) = 1;
					else
						(yyval.fval) = 0;

				}
#line 2192 "tree.tab.c"
    break;

  case 77: /* relational_expression: relational_expression GE_OP additive_expression  */
#line 843 "tree.y"
                                { 
					create_node(">=", 0);
					if((yyvsp[-2].fval) >= (yyvsp[0].fval))
						(yyval.fval) = 1;
					else
						(yyval.fval) = 0;

				}
#line 2205 "tree.tab.c"
    break;

  case 78: /* additive_expression: multiplicative_expression  */
#line 855 "tree.y"
                                        {	(yyval.fval) = (yyvsp[0].fval);	}
#line 2211 "tree.tab.c"
    break;

  case 79: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 857 "tree.y"
                        {	
				create_node("+", 0);
				(yyval.fval) = (yyvsp[-2].fval) + (yyvsp[0].fval);	
			}
#line 2220 "tree.tab.c"
    break;

  case 80: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 862 "tree.y"
                        {	
				create_node("-", 0);
				(yyval.fval) = (yyvsp[-2].fval) - (yyvsp[0].fval);	
			}
#line 2229 "tree.tab.c"
    break;

  case 81: /* multiplicative_expression: unary_expression  */
#line 870 "tree.y"
                                                {	(yyval.fval) = (yyvsp[0].fval);	}
#line 2235 "tree.tab.c"
    break;

  case 82: /* multiplicative_expression: multiplicative_expression '*' unary_expression  */
#line 872 "tree.y"
                                        {	
						create_node("*", 0);	
						(yyval.fval) = (yyvsp[-2].fval) * (yyvsp[0].fval);	
					}
#line 2244 "tree.tab.c"
    break;

  case 83: /* multiplicative_expression: multiplicative_expression '/' unary_expression  */
#line 877 "tree.y"
                                        {	
						if((yyvsp[0].fval) == 0){
							printf("Line:%d: ", line);
							
							printf("division by zero is undefined\n\n");
							(yyval.fval) = INT_MAX;		//junk value in real
						}else{
							(yyval.fval) = (yyvsp[-2].fval) / (yyvsp[0].fval);	
							create_node("/", 0);
						}
					}
#line 2260 "tree.tab.c"
    break;

  case 84: /* multiplicative_expression: multiplicative_expression '%' unary_expression  */
#line 889 "tree.y"
                                        {	
						if(assigntype == 1){
							printf("Line:%d: ", line);
							
							printf("invalid operands to binary expression (\'float\' and \'float\') \n\n");
							}else{								
								(yyval.fval) = (int)(yyvsp[-2].fval) % (int)(yyvsp[0].fval);	
								create_node("%", 0);
							}
						}
#line 2275 "tree.tab.c"
    break;

  case 85: /* function_definition: type_specifier declarator compound_statement  */
#line 906 "tree.y"
                                {
					create_node((yyvsp[-1].string), 3);
					struct node *ftp;
					ftp = first;
					while(ftp!=NULL){
						if(ftp->scope == scope && ftp->valid == 1){
							ftp->valid = 0;
						}
						else if(strcmp(ftp->token, "param") == 0 && ftp->valid == 1){
							ftp->valid = 0;
						}

						ftp=ftp->link;
					}
					scope--;

				}
#line 2297 "tree.tab.c"
    break;

  case 86: /* function_definition: declarator compound_statement  */
#line 924 "tree.y"
                                {	
					create_node((yyvsp[-1].string), 3);
					printf("Line:%d: ", line);
					
					printf("\033[0m");
					printf("type specifier missing, defaults to \'int\' \n");

					struct node *ftp;
					ftp = first;
					while(ftp!=NULL){
						if(ftp->scope == scope && ftp->valid == 1){
							ftp->valid = 0;
						}
						else if(strcmp(ftp->token, "param") == 0 && ftp->valid == 1){
							ftp->valid = 0;
						}

						ftp=ftp->link;
					}
					scope--;
				}
#line 2323 "tree.tab.c"
    break;

  case 89: /* declarator: IDENTIFIER  */
#line 956 "tree.y"
                                {	
					// printf("OKAY : %s\n", $1->name);
					// create_node($1->name, 1);
					addfunc((yyvsp[0].ptr), datatype, "function");	
					strcpy((yyval.string), (yyvsp[0].ptr)->name); 								
				}
#line 2334 "tree.tab.c"
    break;

  case 90: /* declarator: declarator '(' parameter_list ')'  */
#line 962 "tree.y"
                                                        { }
#line 2340 "tree.tab.c"
    break;

  case 91: /* declarator: declarator '(' identifier_list ')'  */
#line 963 "tree.y"
                                                { }
#line 2346 "tree.tab.c"
    break;

  case 92: /* declarator: declarator '(' ')'  */
#line 964 "tree.y"
                                                                { }
#line 2352 "tree.tab.c"
    break;

  case 93: /* parameter_list: parameter_declaration  */
#line 969 "tree.y"
                                                                        {}
#line 2358 "tree.tab.c"
    break;

  case 94: /* parameter_list: parameter_list ',' parameter_declaration  */
#line 970 "tree.y"
                                                        {}
#line 2364 "tree.tab.c"
    break;

  case 95: /* parameter_declaration: type_specifier IDENTIFIER  */
#line 975 "tree.y"
                                                {	addfunc((yyvsp[0].ptr), datatype, "param");	}
#line 2370 "tree.tab.c"
    break;

  case 96: /* parameter_declaration: type_specifier  */
#line 976 "tree.y"
                                                        {}
#line 2376 "tree.tab.c"
    break;

  case 97: /* identifier_list: IDENTIFIER  */
#line 981 "tree.y"
                                                                {		}
#line 2382 "tree.tab.c"
    break;

  case 98: /* identifier_list: identifier_list ',' IDENTIFIER  */
#line 982 "tree.y"
                                                {		}
#line 2388 "tree.tab.c"
    break;


#line 2392 "tree.tab.c"

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

#line 986 "tree.y"



void yyerror(const char *str){
	fflush(stdout);
	printf("Line:%d: ", line);
	
	printf("%s\n", str);
}


int main(){
	yyout = fopen("output.c", "w");


	tree_top = (tree_stack*)malloc(sizeof(tree_stack));
	tree_top->node = NULL;
	tree_top->next = NULL;
	struct Node *root;

	printf("\n");
	yyparse();

	root = pop_tree();
	get_levels(root, 1);

	printtree(root);
	

	preorder(root);
	
	printf("%s\n", preBuf);

	fclose(yyout);
	return 0;
}


void addfunc(struct node *t,int type, char *s){
	if(t->dtype == -1) {
        t->dtype = type;
        t->val.i = 0;
        strcpy(t->token, s);
    }
}


void addInt(struct node *t,int type,int val) {
    if(t->dtype == -1) {
        t->dtype = type;
        t->val.i = val;
        strcpy(t->token, "identifier");
    }
}


void addFloat(struct node *t,int type,float val) {
    if(t->dtype == -1) {
        t->dtype = type;
        t->val.f = (float)val;
        strcpy(t->token, "identifier");
    }
}


void addChar(struct node *t,int type, char val) {
   	if(t->dtype == -1) {
   	    t->dtype = type;
   	    t->val.c = (char)val;
   	    strcpy(t->token, "identifier");
   	}
}


struct node * addtosymbol(struct node * n){
	if(first == NULL){
		first = n;
	}
	else{
		struct  node * ftp = first;
		while(ftp->link !=NULL) {
			ftp = ftp->link;
		}
		ftp->link = n;
	}
	return n;
}


struct node * checksym(char *vname) {
	struct node *ftp;
	struct node *rp;
	struct node *nnode;
	struct node *same;
	
	if(first == NULL) {
		nnode = (struct node *)malloc(sizeof(struct node));
		addsymbol(nnode,vname);
	    first = nnode;
	}
	else {
	    ftp = first;
	    while(ftp!=NULL) {

	        if(strcmp(vname,ftp->name) == 0){
	            if(ftp->scope > scope && ftp->valid == 1) {	          	
					same = ftp; 
	            	return same;
	            }	
	            else if(ftp->scope == scope && ftp->valid == 1){
	            	same = ftp;
	            	return same;
	            }          	
	            else if(ftp->scope < scope && ftp->valid == 1){
	         		check_un = 1;	//no error 

	         		same = ftp;
	            	return same;
	         			            		         				         		       	         
	            } 
	          	else if(ftp->scope > scope && ftp->valid == 0){
	          		check_un = 0;	//undeclared
	          	}

	        }            
	        rp = ftp;
	        ftp = ftp->link;
	    }
	    nnode = (struct node *)malloc(sizeof(struct node));
		addsymbol(nnode,vname);

	    rp->link = nnode;
	}
	return nnode;
}


void addsymbol(struct node *tp, char *vname) {
    strcpy(tp->name,vname);
    tp->dtype = -1;
    tp->link = NULL;
    tp->scope = scope;
    tp->valid = 1;
    tp->lineno = line;
}


void cleansymbol(){
	struct node** pp = &first; 
    while (*pp) { 
  
        struct node* entry = *pp; 
 
        if (entry->dtype == -1  ) { 
            *pp = entry->link; 
            free(entry); 
        }
        else if(strcmp(entry->name,"main")== 0 && strcmp(entry->token, "function")==0){	//remove main entry from symbol table
        	*pp = entry->link; 
            free(entry); 
        }
        // Else move to next 
        else
            pp = &(entry->link); 
    } 
}


void printsymtable(){
	struct node *ftp;
    ftp=first;
    //blue
    printf("\n\nSYMBOL TABLE\n\n");
    //white

	printf("   SYMBOL\t\tNAME\t  TYPE\t      DIMENTION\t   LINE OF CODE\t       VALUE \n");
   
    while(ftp!=NULL) {
        char data_type[10];
        if(ftp->dtype==0)
        	strcpy(data_type,"int");
        if(ftp->dtype==1)
        	strcpy(data_type,"float");
        if(ftp->dtype==2)
        	strcpy(data_type,"char");
        if(ftp->dtype==3)
        	strcpy(data_type,"void");

        printf("%11s\t%12s\t%6s\t\t%d\t\t%d\t\t",ftp->token, ftp->name, data_type, ftp->scope, ftp->lineno);

        if(ftp->dtype == 0){
        	if(ftp->val.i == INT_MIN)
        		printf("-\n");
        	else
           		printf("%d\n",ftp->val.i);
        }
        else if(ftp->dtype == 1){
        	if(ftp->val.f == INT_MIN)
        		printf("-\n");
        	else
           		printf("%f\n",ftp->val.f);
       	}
        else if(ftp->dtype == 2){
            printf("%c\n",ftp->val.c);
        }
        else if(strcmp(ftp->token, "function")==0){
        	printf("-\n");
        }
        else{
	        printf("-	Delete it\n");
	    }
        ftp=ftp->link;
    }
    printf("\n\n\n");
}


void create_node(char *token, int leaf) {
	Node *l;
	Node *r;
	if(leaf==0) {

		r = pop_tree();
		l = pop_tree();
	}
	else if(leaf ==1) {
		l = NULL;
		r = NULL;
	}
	else {
		l = pop_tree();
		r = NULL;
	}

	Node *newnode = (Node*)malloc(sizeof(Node));
	strcpy(newnode->token, token);
	newnode->left = l;
	newnode->right = r;
	push_tree(newnode);
}


void push_tree(Node *newnode){
	tree_stack *temp= (tree_stack*)malloc(sizeof(tree_stack));
	temp->node = newnode;
	temp->next = tree_top;
	tree_top = temp;
}


Node* pop_tree(){
	tree_stack *temp = tree_top;
	tree_top = tree_top->next;
	Node *retnode = temp->node;
	if(temp != NULL)
		free(temp);
	return retnode;
}


void printtree(Node* root){
    int h = getmaxlevel(root)-1;
    int i;
	
	printf("\n\nAbstract Syntax Tree\n\n");

	
    for (i=1; i<=h; i++){
		printf("\t");
		for(int j=0;j<=h+1-i;j++){
			printf("        ");
		}
        printGivenLevel(root,i,h);

        printf("\n\n\n");
    }
	
}


int getmaxlevel(Node *root){
	int count=0;
	Node *temp= root;
	while(temp->left!=NULL){
		count++;
		temp=temp->left;
	}
	return count*2;
}


void printGivenLevel(Node* root, int level, int h){
    if (root == NULL)
        return;
    if (level == 1){
		for(int j=0; j<=h-1-level; j++){
			printf(" ");
		}
	    printf("%s", root->token);
	}
    else if (level > 1){
        printGivenLevel(root->left,level-1,h);
		for(int j=0; j<=h-1-level; j++){
			printf(" ");
		}
        printGivenLevel(root->right,level-1,h);
    }
}


void preorder(Node * node){
	if (node == NULL)
		return;

	if(node->left!=NULL && node->right!=NULL)
		strcat(preBuf, "   ( ");
	strcat(preBuf, node->token);
	strcat(preBuf, "   ");

	preorder(node-> left);

	
	if(node->right){
		preorder(node-> right);
	}
	
	if(node->left!=NULL && node->right!=NULL)
		strcat(preBuf, ")   ");
	// printf("\n");
	
}

void get_levels(Node *root, int level){
	root->level = level;
	if(root->left == NULL && root->right == NULL){
		return;
	}
	if(root->left == NULL){
		get_levels(root->right, level+1);
	}
	else if(root->right == NULL){
		get_levels(root->left, level+1);
	}
	else{
		get_levels(root->left, level+1);
		get_levels(root->right, level+1);
	}
}
