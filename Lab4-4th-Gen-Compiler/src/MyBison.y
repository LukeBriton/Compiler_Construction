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
int arg_num = 0;    // 可以方便 arg_pass
// int para_num = 0;// 方便 para_declaration -> 被 symtab.cpp Index_para 取代
int is_main = 0;    // 只在返回时有用，为 0 是一般 func，为 1 是 main。
int scope = 0;      // scope 为当前作用域序号，从 0 开始，0 即为默认函数作用域。
int if_num = 0;
int if_nested = 0;
int loop_num = 0;
int loop_nested = 0;
%}

/*
 * The %union construct, as its name suggests, is used to
 * create a C language union declaration for symbol values.
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
%token PRINTLN_INT
// %token CRLF

%token IF ELSE WHILE
%token BREAK CONTINUE 
%token RETURN MAIN

%token INT VOID

%nonassoc THEN
%nonassoc ELSE

/* Operator Precedence */
/* 应列尽列，否则会：
 * MyBison.y: warning: 13 shift/reduce conflicts [-Wconflicts-sr]
 * MyBison.y: note: rerun with option '-Wcounterexamples'
 * to generate conflict counterexamples
 */
/* https://en.cppreference.com/w/c/language/operator_precedence */
/* lower */
%right '='
%left LOR       // ||
%left LAND      // &&
%left '|'
%left '^'
%left '&'
%left <fn> EQN  // == !=
%left <fn> LGTE // < <= > >=
%left '+' '-'
%left '*' '/' '%'
%right UMINUS '!' '~'
// https://stackoverflow.com/questions/12961351/does-it-make-sense-for-unary-operators-to-be-associative
/* higher */

%type <a> exp

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


// https://stackoverflow.com/questions/24025119/right-recursive-grammar-or-left-recursive
program : { genpreamble(); } procedure      {}
        | program  procedure                {}  // left-recursive

// Using Mid-Rule Actions
// https://www.gnu.org/software/bison/manual/html_node/Using-Mid_002dRule-Actions.html
// https://stackoverflow.com/questions/50968469/bison-mid-rule-actions-are-not-working
// https://www.gnu.org/software/bison/manual/html_node/Mid_002dRule-Conflicts.html
// C allows you to call your main function (while C++ does not )
// https://stackoverflow.com/questions/4238179/calling-main-in-main-in-c
// https://en.wikibooks.org/wiki/C_Programming/Procedures_and_functions
// 不考虑 VOID 类型 return; 和 INT 类型没有 return 的情况。
// 总之，只考虑正确输入。
// 繁冗，待优化。
procedure   : VOID ID '(' { is_main = 0; genfuncpreamble($2, P_VOID); } ')' compound_statement                            {genfuncpostamble();}
            | VOID ID '(' { is_main = 0; genfuncpreamble($2, P_VOID); /*para_num = 0;*/ } paralist ')' compound_statement {genfuncpostamble();}
            | INT ID '(' { is_main = 0; genfuncpreamble($2, P_INT); } ')' compound_statement                              {genfuncpostamble();}
            | INT ID '(' { is_main = 0; genfuncpreamble($2, P_INT); /*para_num = 0;*/ } paralist ')' compound_statement   {genfuncpostamble();}
            | INT MAIN '(' ')' { is_main = 1; genmainpreamble(); } compound_statement   {}
            | INT MAIN '(' INT ID ',' INT ID ')' { is_main = 1; genmainpreamble(); para_declaration($5); para_declaration($8); } compound_statement {}

        // The names are just a well-established convention
        // https://stackoverflow.com/questions/11489387/is-it-compulsory-to-write-int-mainint-argc-char-argv-cant-use-some-other
        // Reverse Order of Arguments
        // https://stackoverflow.com/questions/31100614/why-is-order-of-function-arguments-reversed
        // https://stackoverflow.com/questions/27979376/what-does-it-mean-when-they-say-arguments-are-pushed-in-the-reverse-order
        // https://stackoverflow.com/questions/67868615/why-do-arguments-to-a-function-get-filled-up-in-registers-in-reverse-order-in-c
        // https://stackoverflow.com/questions/621542/do-compilers-take-advantage-of-the-indeterminate-sequencing-of-function-argument
;

// int a, int b, int c, int d
// $fp + 8, $fp + 12, $fp + 16, $fp + 20... （$fp的位置是 旧$sp）
// https://stackoverflow.com/questions/14647018/a-notation-for-empty-right-hand-sides-of-rules
// https://stackoverflow.com/questions/156767/whats-the-difference-between-an-argument-and-a-parameter
// 不考虑初始化
// 某种关于参数个数的想法：一个临时变量，计数，传递给函数。
// paralist : INT ID { printf("%s\n", $2); var_declaration($2); }
//          | INT ID ',' paralist { printf("%s\n", $2); var_declaration($2); } // 右递归
//          // 输出顺序：d, c, b, a 
// ;

paralist : INT ID { /*para_num++;*/ /*printf("%s\n", $2);*/ para_declaration($2);/*, para_num);*/ /*printf("%d\n", findlocal($2));*/ }
         | paralist ',' INT ID { /*para_num++;*/ /*printf("%s\n", $4);*/ para_declaration($4);/*, para_num);*/ /*printf("%d\n", findlocal($4));*/ } // 左递归
         // 输出顺序：a, b, c, d 
; 

compound_statement: '{' '}' {}          // empty, i.e. no statement
|      '{' { scope++; pass_scope(scope); /*printf("%d\n", scope);*/ } stmts { scope--; pass_scope(scope); /*printf("%d\n", scope);*/ } '}'        {}
;

// Parse one or more statements
// Bison handles left recursion much more efficiently than right recursion.

// I was totally messing up with so-called left-recursion and right-recursion.
stmts   : stmt          {}
        | stmts stmt    {}  // left-recursive
        //| stmt stmts  {}  // right-recursive
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

// https://en.cppreference.com/w/c/language/declarations
declaration : declarators ';'               {}
;

declarators : INT declarator                {}
            | declarators ',' declarator    {}
;

declarator  : ID            { var_declaration($1); }
            | ID '=' exp    { var_declaration($1); assignment_statement($1, $3); }
;

// https://chatgpt.com/share/2c21c2a5-e6d1-44a4-a459-51ae52b8ec9f

// 条件表达式为 0 => 跳转 （需要 if_ ）
// 否则正常执行（也就不需要 if_true_i 的标签）
if_statement : if_true %prec THEN { printf("\n$if_end_%d:\n", if_nested); if_nested --; }
             | if_true ELSE { /*printf("if_false_%d:\n\n\n", ++if_false_num);*/ } stmt { printf("\n$if_end_%d:\n", if_nested); if_nested --; /*printf("false\n");*/ }
;

// 统一按照跳转至 if_false_N 即可。
if_true      : IF '(' exp { if_num ++; if_nested = if_num; condition($3, 1, if_nested); } ')' { /*printf("true\n");*/ } stmt { printf("j $if_end_%d\n", if_nested); printf("\n$if_false_%d:\n", if_nested); }
;

loop : WHILE '(' { loop_num ++; loop_nested = loop_num; printf("\n$loop_%d:\n", loop_nested); } exp { condition($4, 2, loop_nested); } ')' stmt { printf("j $loop_%d\n", loop_nested); printf("\n$loop_end_%d:\n", loop_nested); loop_nested --; }
;

stmt : declaration          {}
     | compound_statement   {}
     | if_statement         {}
     | loop                 {}
     | BREAK ';'            { printf("\nj $loop_end_%d\n", loop_nested); }
     | CONTINUE ';'         { printf("\nj $loop_%d\n", loop_nested); }
     | ID '=' exp ';'       { assignment_statement($1, $3); }
        /* The parser doesn't know which rule to take --until it's
         * parsed the next token to see if it is a '='. By the time
         * the code is executed, yytext has already been overwritten.
         * 这也是何以即便采用了 Mid-Rule，仍得不到正确的结果，如：
         * ID {printf("%s \n\n", $1);} '=' exp ';' {...}
         */
     | PRINTLN_INT '(' exp ')' ';' { println_int_statement($3); }
     | RETURN exp ';'       {
        return_statement($2);
        if (is_main == 1)
            exit_syscall();
        else if (is_main == 0)
            genfuncpostamble();
        }
     //| ID '(' { arg_num = 0; } arglist ')' ';' {
     | ID '(' arglist ')' ';' {
        // Check that this identifier exists
        int func = findfunc($1);
        if (func == -1)
            yyerror("Unknown function %s", $1);
        // printf("%s\n", $1);
        arglist_buf(arg_num);
        arg_num = 0;
        arglist_output();
        func_call($1);
        }
;

// 不考虑 arguments 数量与 parameters 不相等的情况
arglist : exp { arg_num++; /*printf("%d\n", arg_num);*/ /*printf("%d\n", $1->v.intvalue);*/ arg_pass($1); }
        | exp ',' arglist { arg_num++; /*printf("%d\n", arg_num);*/ /*printf("%d\n", $1->v.intvalue);*/ arg_pass($1); } // 右递归
        // 这样正好，paralist是从左到右，这样的话可以随着 para_num 而 addpara，
        // arglist 是从右向左，按照实验说明所给，下移栈顶，将最左的 argument 放在地址最低处。
;
// 一个问题是，当在 exp 中 匹配到 ID '(' arglist ')' 时，arg_pass 的语句均已经执行完毕，
// 之后才构建了一个 FUNC 的 AST 结点，作为一个 exp。
// 如果出现 test(1, 2) + func(3, 4) 这样的语句，
// 其首先将参数 2, 1 入栈，这时才算匹配上了一个 exp
// 此时 func_call 并没有执行，会一直等到整个 AST 全部生成，在遍历的过程中碰到为止。
// 之后 4, 3 入栈，与前略同。

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
    | exp LAND exp { $$ = mkastnode(A_LAND, $1, $3, 0); }
    | exp LOR exp { $$ = mkastnode(A_LOR, $1, $3, 0); }
    | '-' exp %prec UMINUS { $$ = mkastunary(A_UMINUS, $2, 0); }
    | '!' exp { $$ = mkastunary('!', $2, 0); }
    | '~' exp { $$ = mkastunary('~', $2, 0); }
    | '(' exp ')' { $$ = $2; }
    | INTLIT { $$ = mkastleaf(A_INTLIT, $1); }
    //| ID '(' { arg_num = 0; } arglist ')' { 
    // 不采用以上这种，以预防这种情况：
    // b = test( {置0} func( {置0} 1, 2), func( {置0} 3, 4) );
    //                |---------------------------------->|
    // 当处理完 func(3, 4) 的内部后，拐回来将两个 func 视为 test 的两个参数，
    // 但是 test 本身的 {置0} 操作则早早地进行了，arg_num 会保留 func(3, 4)
    // 的参数个数，再加上匹配 test 得到的两个参数，清理栈时会错误地多出栈了两个。
    | ID '(' arglist ')' {
        // Check that this identifier exists
        int func = findfunc($1);
        if (func == -1)
            yyerror("Unknown function %s", $1);
        // printf("%s\n", $1);
        arglist_buf(arg_num);
        arg_num = 0;
        // Make a leaf AST node for it
        $$ = mkastleaf(A_FUNC, func);
        }
    | ID {
        // printf("%s\n", $1);
        // Check that this identifier exists
        int id = findlocal($1);
        if (id == -1)
            yyerror("Unknown variable %s", $1);
        // Make a leaf AST node for it
        $$ = mkastleaf(A_IDENT, id);
        }

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
