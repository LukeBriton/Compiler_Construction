/*
 * Functions
 *
 * 基于：
 * flex & bison Example 3-4.
 * C routines for AST calculator
 * Example 3-8.
 * Advanced calculator helper functions fb3-2func.c
 */

#include <stdio.h>
#include <stdarg.h>
#include "declare.h"
#include "defs.h"

//warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings]
//void yyerror(char *s, ...)
void yyerror(const char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

int main(int argc, char *argv[]) {

    if(argc > 1)
    {
        if(!(yyin = fopen(argv[1], "r")))
        {
            perror(argv[1]);
            return (1);
        }
    }
    yyparse();
    return 0;
}
