/* Modern style */
%option noyywrap

%x COMMENT

/*** Definition section ***/
%{
/* Flex 源程序采样类 C 的语法和规则 */
/* C code to be copied verbatim */
/* 以下是声明部分，`%{` 和 `%}` 之间的内容会被原样复制到生成的 C 文件头部
    包括该条注释内容 */
#include <string.h>
int chars = 0;
int words = 0;
int lines = 0;
%}

/* 以下是规则部分，在规则部分写注释不能顶格写 */
/* 每条规则由正则表达式和动作组成 */
%%
    /* 在规则部分，不要顶格写注释 */
    /* 否则：MyFlex.l:23: unrecognized rule */
    /* { 和 Regex 间必须有 whitespeace*/
    /* 否则也会 unrecognized，注意，报错行号其实会报在下一行。 */
        /* comments，抄书 */
"/*"                { BEGIN(COMMENT); }
<COMMENT>"*/"       { BEGIN(INITIAL); }
<COMMENT>([^*]|\n)+|.
<COMMENT><<EOF>>    { printf("Unterminated comment\n"); }
"//".*\n
    /* 关键字： int, return */
    /* printf 双引号需要转义 */
"int" { printf("Keyword \"int\"\n"); }
"return" { printf("Keyword \"return\"\n"); }
    /* 标识符：单个英文字母，如 a、 b 等 */
    /* 以后考虑增加处理 字母、数字、下划线 */
    /* 以及例如 2a 非法 a5 合法此类 */
    /* Starting Condition? */
[[:alpha:]]     {
                    chars += yyleng;
                    printf("Identifier\n");
                    //return IDENTIFIER;
                }
    /* 常量：十进制整型，如 1、 223、 10 等 */
    /* 此处疑似实际指的是字面量，且局限在了整型字面量中的decimal-literal */
    /* 以后考虑外加浮点数、非十进制数，乃至字符（串）的处理 */
    /* a.b1() 和 1.4 */
    /* C99 decimal constant */
([[:digit:]]{-}[0])[[:digit:]]*    {
                    chars += yyleng;
                    printf("Literal\n");
                    //return LITERAL;
                }
    /* 操作符： =、 +、 -、 *、 / */
"=" { printf("Operator \"=\"\n"); }
"+" { printf("Operator \"+\"\n"); }
"-" { printf("Operator \"-\"\n"); }
"*" { printf("Operator \"*\"\n"); }
"/" { printf("Operator \"/\"\n"); }
    /* 分隔符： ; */
";" { printf("Semicolon \";\"\n"); }

.           {}
%%

/* 以下为 C 代码部分 */
int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        if(!(yyin = fopen(argv[1], "r")))
        {
            perror(argv[1]);
            return (1);
        }
    }
    yylex();
    printf("look, I find %d words of %d chars\n", words, chars);
    return 0;
}