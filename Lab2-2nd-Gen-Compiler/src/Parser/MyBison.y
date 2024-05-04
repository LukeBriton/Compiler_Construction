/* 
 * Parser
 *
 * 基于：
 * https://ustc-compiler-principles.github.io/2023/lab1/Bison/
 * “一个复杂的 Bison 程序”--calc.y
 * 以及 flex & bison Example 3-2.
 * Bison parser for AST calculator
 * + acwj/06_Variables
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include "Declare.h"
%}

/*
 * The %union construct, as its name suggests, is used to
 * create a C language union declaration for symbol values.
 * a, which is a pointer to an AST,
 * and num, which is a long long int.
 */

%union {
    struct ast *a;
    int num;
    struct symbol *s; /* which symbol */
    //struct symlist *sl;
    int fn; /* which function */
}

/* declare tokens */
%token <num> NUMBER
%token <s> ID
%token <fn> FUNC
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
%left <fn> LGE // 理论上可以细分
%left '+' '-'
%left '*' '/' '%'
//%nonassoc UMINUS
/* higher */

%type <a> exp stmt 
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

program : INT MAIN '(' ')' '{' stmts '}'                        {}
        | INT MAIN '(' INT ident ',' INT ident ')' '{' stmts '}'{}

;

stmts   : stmt      {}
        | stmt stmts{}
;

// warning: type clash on default action
// https://lists.gnu.org/archive/html/help-bison/2000-10/msg00056.html
// { $$ = $1; }; by default

stmt : INT ident ';'        {}
     | INT ident '=' exp ';'{}
     | ident '=' exp ';'    {}
     | FUNC '(' exp ')' ';' {}
     | RETURN exp ';'       {}
;

ident: ID
;

exp : exp '*' exp { $$ = newast('*', $1,$3); }
    | exp '/' exp { $$ = newast('/', $1,$3); }
    | exp '%' exp { $$ = newast('%', $1,$3); }
    | exp '+' exp { $$ = newast('+', $1,$3); }
    | exp '-' exp { $$ = newast('-', $1,$3); }
    | exp LGE exp { $$ = newcmp($2, $1, $3); }
    | exp EQN exp { $$ = newcmp($2, $1, $3); }
    | exp '&' exp { $$ = newast('&', $1,$3); }
    | exp '^' exp { $$ = newast('^', $1,$3); }
    | exp '|' exp { $$ = newast('|', $1,$3); }
    | '(' exp ')' { $$ = $2; }
    | NUMBER { $$ = newnum($1); }
    | ident { $$ = newref($1); }

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
