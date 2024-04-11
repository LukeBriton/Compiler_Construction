/* 
 * Parser
 *
 * 基于：
 * https://ustc-compiler-principles.github.io/2023/lab1/Bison/
 * “一个复杂的 Bison 程序”--calc.y
 * 以及 flex & bison Example 3-2.
 * Bison parser for AST calculator
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
    struct symlist *sl;
    int fn; /* which function */
}

/* declare tokens */
%token <num> NUMBER
%token <s> ID
%token <fn> FUNC
%token CRLF

%token IF THEN ELSE WHILE DO LET RETURN

%nonassoc <fn> CMP
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%type <a> exp stmt list explist
%type <sl> symlist
%start calclist

/* 
 * Keep in mind that any rule without explicit 
 * action code gets the default action $$ = $1;
 */

%%

stmt: IF exp THEN list { $$ = newflow('I', $2, $4, NULL); }
    | IF exp THEN list ELSE list { $$ = newflow('I', $2, $4, $6); }
    | WHILE exp DO list { $$ = newflow('W', $2, $4, NULL); }
    | exp
;

list: /* nothing */ { $$ = NULL; }
    | stmt ';' list {   if ($3 == NULL)
                            $$ = $1;
                        else
                            $$ = newast('L', $1, $3);
                    }
;

exp : exp CMP exp { $$ = newcmp($2, $1, $3); }
    | exp '+' exp { $$ = newast('+', $1,$3); }
    | exp '-' exp { $$ = newast('-', $1,$3);}
    | exp '*' exp { $$ = newast('*', $1,$3); }
    | exp '/' exp { $$ = newast('/', $1,$3); }
    | exp '%' exp { $$ = newast('%', $1,$3); }
    | '(' exp ')' { $$ = $2; }
    | '-' exp %prec UMINUS { $$ = newast('M', $2, NULL); }
    | NUMBER { $$ = newnum($1); }
    | ID { $$ = newref($1); }
    | ID '=' exp { $$ = newasgn($1, $3); }
    | FUNC '(' explist ')' { $$ = newfunc($1, $3); }
    | ID '(' explist ')' { $$ = newcall($1, $3); }
;

explist : exp
        | exp ',' explist { $$ = newast('L', $1, $3); }
;
symlist : ID { $$ = newsymlist($1, NULL); }
        | ID ',' symlist { $$ = newsymlist($1, $3); }
;

calclist: /* nothing */
    | calclist stmt CRLF {
        printf("= %d\n> ", eval($2));
        treefree($2);
    }
    | calclist LET ID '(' symlist ')' '=' list CRLF {
        dodef($3, $5, $8);
        printf("Defined %s\n> ", $3->name);
    }
    | calclist error CRLF { yyerrok; printf("> "); }
;

%%
