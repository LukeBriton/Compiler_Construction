/* %option noyywrap 功能较为复杂，同学们自行了解 */
%option noyywrap
%{
/* Flex 源程序采样类 C 的语法和规则 */
/* 以下是声明部分，`%{` 和 `%}` 之间的内容会被原样复制到生成的 C 文件头部
    包括该条注释内容 */
#include <string.h>
int chars = 0;
int words = 0;
%}

/* 以下是规则部分，在规则部分写注释不能顶格写 */
/* 每条规则由正则表达式和动作组成 */
/* 第一条规则匹配纯字母的字符串，并统计字母个数和字符串个数
                       其中 yytext 为匹配到的 token */
/* 第二条规则匹配其他字符或字符串并执行空动作 */
%%
 /* 在规则部分，不要顶格写注释 */
[a-zA-Z]+  { chars += strlen(yytext); words++; }
.          {}
%%

/* 以下为 C 代码部分 */
int main()
{
    /* yylex() 是由 Flex 自行生成的，用于执行 */
    yylex();
    /* 对于 stdin 输入匹配结束，执行其他操作 */
    printf("look, I find %d words of %d chars\n", words, chars);
    return 0;
}