/*** Definition section ***/
%{
/* Flex 源程序采样类 C 的语法和规则 */
/* C code to be copied verbatim */
/* 以下是声明部分，`%{` 和 `%}` 之间的内容会被原样复制到生成的 C 文件头部
    包括该条注释内容 */
#include <string.h>
int chars = 0;
%}

/* This tells flex to read only one input file */
%option noyywrap

/* 以下是规则部分，在规则部分写注释不能顶格写 */
/* 每条规则由正则表达式和动作组成 */
%%
    /* 在规则部分，不要顶格写注释 */
([[:digit:]]{-}[0])[[:digit:]]*    {
                    yylval.dval = atof(yytext);
                    chars += strlen(yytext);
                    return CONST;
                }

[[:alpha:]]     {
                    struct symtab *sp = symlook(yytext);
                    yylval.symp = sp;
                    chars += strlen(yytext);
                    return IDENTIFIER;
                }

.           {}
%%

/* 以下为 C 代码部分 */
int main(int argc, char *argv[])
{
    yylex();
    printf("look, I find %d words of %d chars\n", words, chars);
    return 0;
}