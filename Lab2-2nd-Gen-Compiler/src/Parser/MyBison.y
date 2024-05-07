/* 
 * Parser
 *
 * 基于： acwj/07_Comparisons
 * https://ustc-compiler-principles.github.io/2023/lab1/Bison/
 * “一个复杂的 Bison 程序”--calc.y
 * 以及 flex & bison Example 3-2.
 * Bison parser for AST calculator
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "declare.h"
%}

/*
 * The %union construct, as its name suggests, is used to
 * create a C language union declaration for symbol values.
 * a, which is a pointer to an AST,
 * and num, which is a long long int.
 */

%union {
    struct ASTnode *a;
    int intval;
    const char* s; /* which symbol */
    int fn; /* which function */
}

/* declare tokens */

%token <intval> INTLIT
%token <s> ID


// %token <fn> FUNC
%token PRINTLN_INT
// %token CRLF

// %token IF THEN ELSE WHILE DO 
%token RETURN MAIN

%token INT




/* Operator Precedence */
/* 应列尽列，否则会：
 * MyBison.y: warning: 13 shift/reduce conflicts [-Wconflicts-sr]
 * MyBison.y: note: rerun with option '-Wcounterexamples'
 * to generate conflict counterexamples
 */
/* https://en.cppreference.com/w/c/language/operator_precedence */
/* lower */
%right '='
%left '|'
%left '^'
%left '&'
%left <fn> EQN
%left <fn> LGTE // 理论上可以细分
%left '+' '-'
%left '*' '/' '%'
//%nonassoc UMINUS
/* higher */

%type <a> exp
//%type <sl> symlist
%start program

/* 
 * Keep in mind that any rule without explicit 
 * action code gets the default action $$ = $1;
 */

%%

// stmt := Statement...
/*
stmt: IF exp THEN list { $$ = newflow('I', $2, $4, NULL); }
    | IF exp THEN list ELSE list { $$ = newflow('I', $2, $4, $6); }
    | WHILE exp DO list { $$ = newflow('W', $2, $4, NULL); }
    | exp
;
*/

// 变量声明（单变量且无初始化）int a;
/* 未来会有： int a, b, c...;
 * int a, b = 5;（a 只声明，b 初始化。）
 * int a = 5, b = 6;
 * int a = b = 9;
 */
// 简单表达式赋值语句 a = b&1;
// 复杂表达式赋值语句 a = (d+b&1)/(e!=3^b/c&&d);
// return 语句 return 0;
// 函数调用（只需支持预置函数） println_int(a);
// main 函数定义 不带参数 int main(){...}
// main 函数定义 带参数 int main(int argc, int argv){...}

/* Each symbol in a bison rule has a value; the value of
 * the target symbol (the one to the left of the colon) is
 * called $$ in the action code, and the values on the right
 * are numbered $1, $2, and so forth, up to the number of
 * symbols in the rule. */

// Bison handles left recursion much
// more efficiently than right recursion.

// Using Mid-Rule Actions
// https://www.gnu.org/software/bison/manual/html_node/Using-Mid_002dRule-Actions.html
program : INT MAIN '(' ')' {genpreamble();} '{' stmts '}'   {}
        | INT MAIN '(' INT ID ',' INT ID ')' {genpreamble(); addlocal($5); addlocal($8);} '{' stmts '}' {}
;

// Parse one or more statements
stmts   : stmt      {}
        | stmt stmts{}
;

// warning: type clash on default action
// https://lists.gnu.org/archive/html/help-bison/2000-10/msg00056.html
// { $$ = $1; }; by default


/* stmt : INT ID ';' {...}
 *      | ID '=' exp ';' {...} 
 * Flex 中标识符如果是 yylval.s = yytext; 而非 yylval.s = strdup(yytext);
 * 则 stmt 中尝试得到 ID 所对应的 $n 字符串时，会得到自*yytext地址往后的一长串，
 * 但是 exp 中又可以得到正确的 $1。 此外某种可能的尝试是得到一个 std::string 以传递，
 * 但将 Bison 改成 C++ 语法似乎比较麻烦，捣腾了一波没弄成。
 * https://stackoverflow.com/questions/49331561/flex-bison-yytext-skips-over-a-value
 * https://stackoverflow.com/questions/22435879/bison-printing-variable-from-flex-wrong
 * {ID}    {yylval.id = malloc(yyleng + 1); strcpy(yylval.id, yytext); return ID;}
 * https://lists.gnu.org/archive/html/bison-patches/2003-03/msg00055.html
 * strdup 动态分配内存的释放：（OS 还会出手吗？）
 * https://stackoverflow.com/questions/31104302/freeing-the-string-allocated-in-strdup-from-flex-bison
 * https://westes.github.io/flex/manual/A-Note-About-yytext-And-Memory.html
 */

stmt : INT ID ';'        { var_declaration($2); }
     | ID '=' exp ';'    { assignment_statement($1, $3); }
        /* The parser doesn't know which rule to take --until it's
         * parsed the next token to see if it is a '='. By the time
         * the code is executed, yytext has already been overwritten.
         * 这也是何以即便采用了 Mid-Rule，仍得不到正确的结果，如：
         * ID {printf("%s \n\n", $1);} '=' exp ';' {...}
         */
     | PRINTLN_INT '(' exp ')' ';' { println_int_statement($3); }
     | RETURN exp ';'       { return_statement($2); }
;

exp : exp '*' exp { $$ = mkastnode('*', $1, $3, 0); }
    | exp '/' exp { $$ = mkastnode('/', $1, $3, 0); }
    | exp '%' exp { $$ = mkastnode('%', $1, $3, 0); }
    | exp '+' exp { $$ = mkastnode('+', $1, $3, 0); }
    | exp '-' exp { $$ = mkastnode('-', $1, $3, 0); }
    | exp LGTE exp { $$ = mkastnode($2, $1, $3, 0); }
    | exp EQN exp { $$ = mkastnode($2, $1, $3, 0); }
    | exp '&' exp { $$ = mkastnode('&', $1, $3, 0); }
    | exp '^' exp { $$ = mkastnode('^', $1, $3, 0); }
    | exp '|' exp { $$ = mkastnode('|', $1, $3, 0); }
    | '(' exp ')' { $$ = $2; }
    | INTLIT { $$ = mkastleaf(A_INTLIT, $1); }
    | ID {
        // Check that this identifier exists
        int id = findlocal($1);
        if (id == -1)
            yyerror("Unknown variable %s", $1);
        // Make a leaf AST node for it
        $$ = mkastleaf(A_IDENT, id);
        }

    //| '-' exp %prec UMINUS { $$ = newast('M', $2, NULL); }
    // 其实负数已经含在 NUMBER 里了，但是对于 '-' ID 的情况，仍然需要处理

    // 之前一直没有捋明白这计算器里的变量。
    // 现在看来，看上去是只能在一个 stmt 里用。
    // syms points to a linked list of the dummy arguments
    // A separate rule for symlist, a list of symbols, builds
    // a linked list of symbols for the dummy arguments in a function definition.
    // 所以该部分不能直接用，砍掉重练吧。
    //| ID { $$ = newref($1); }
    //| ID '=' exp { $$ = newasgn($1, $3); }
    //| ID '(' explist ')' { $$ = newcall($1, $3); }
;

%%
