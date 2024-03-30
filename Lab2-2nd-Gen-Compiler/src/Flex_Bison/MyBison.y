/* calc.y */
%{
#include <stdio.h>
    int yylex(void);
    void yyerror(const char *s);
%}

%token IDENTIFIER
%token INT RETURN
%token CRLF
%token <num> NUMBER
%token <op> ADDOP MULOP LPAREN RPAREN ASSIGN SEMICOLON
%type <num> top line expr term factor

%start top

%union {
    char op;
    long long int num;
}

%%

top
: top line {}
| {}

line
: expr CRLF
{
    printf(" = %d\n", $1); //乐，这个忘了改了差点。
}

expr
: term
{
    $$ = $1;
}
| expr ADDOP term
{
    switch ($2) {
    case '+': $$ = $1 + $3; break;
    case '-': $$ = $1 - $3; break;
    }
}

term
: factor
{
    $$ = $1;
}
| term MULOP factor
{
    switch ($2) {
    case '*': $$ = $1 * $3; break;
    case '/': $$ = $1 / $3; break; // 除 0 会报 syntax error
    }
}

factor
: LPAREN expr RPAREN
{
    $$ = $2;
}
| NUMBER
{
    $$ = $1;
}

%%

void yyerror(const char *s)
{
    fprintf(stderr, "%s\n", s);
}

int main(int argc, char *argv[])
{
    yyparse();
    return 0;
}