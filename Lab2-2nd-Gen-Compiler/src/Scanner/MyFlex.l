/*
 * Scanner
 *
 * Modern style
 * 
 * Flex lets you say %option nodefault at the top of the scanner to
 * tell it not to add a default rule and rather to report an error
 * if the input rules don’t cover all possible input.
 *
 * The %yylineno option tells flex to define an integer variable
 * called yylineno and to maintain the current line number in it...
 * It’s still up to you to initialize yylineno to 1 at the beginning
 * of each file and to save and restore it if you’re handling include files.
 */

%option noyywrap yylineno

/*%x COMMENT*/

/*** Definition section ***/
%{
/* Flex 源程序采样类 C 的语法和规则 */
/* C code to be copied verbatim */
/* 以下是声明部分，`%{` 和 `%}` 之间的内容
 * 会被原样复制到生成的 C 文件头部
 * 包括该条注释内容
 */
#include <string.h>
#include "MyBison.tab.h"
#include "Declare.h"
%}

/* 以下是规则部分，在规则部分写注释不能顶格写 */
/* 每条规则由正则表达式和动作组成 */
%%
    /* 在规则部分，不要顶格写注释 */
    /* 否则：MyFlex.l:23: unrecognized rule */
    /* { 和 Regex 间必须有 whitespeace*/
    /* 否则也会 unrecognized，注意，报错行号其实会报在下一行。 */


    /* comments，抄书 */
    /* 疑似很有问题，现已删去。 */


    /* 关键字： int, return, main(?) */

    /* keywords */
    /* "if" { return IF; } */
    /* TODO */
    /* In languages that don’t have a THEN keyword... */
    /* flex & bison P188 */
    /* "then" { return THEN; } */
    /* "else" { return ELSE; } */
    /* "while" { return WHILE; } */
    /* "do" { return DO; } */
"return" { return RETURN; }
"main" { return MAIN; }

    /* declaration keywords */
    /* 怀疑之后有必要统一设为 Type，*/
    /* 依靠 yylval 区分具体类型 */
"int" {return INT; }


    /* 操作符： =、 +、 -、 *、 / */

    /* single character ops */
    /* 掉了"=", Silly of me */
    /* 大概暂时不用区分指针、取址 */
"+" |
"-" |
"*" |
"/" |
"%" |
"=" |
"&" |
"|" |
"^" |
"(" |
")" |
"{" |
"}" |
"," |
";" { return yytext[0]; }

    /* comparison ops, all are a CMP token */
">" { yylval.fn = 1; return CMP; }
"<" { yylval.fn = 2; return CMP; }
"!=" { yylval.fn = 3; return CMP; }
"==" { yylval.fn = 4; return CMP; }
">=" { yylval.fn = 5; return CMP; }
"<=" { yylval.fn = 6; return CMP; }


    /* built-in functions */
"println_int" { yylval.fn = B_println_int; return FUNC; } /* MyFlex.l:116: warning, rule cannot be matched */

    /* 标识符：[A-Za-z_][0-9A-Za-z_]*/
    /* 不含 UCN, implementation-defined 字符。*/
    /* Starting Condition? */
    /* printf 双引号需要转义 */
[_[:alpha:]][_[:alnum:]]*     {
                    //chars += yyleng;
                    //printf("Identifier\n");
                    return ID;
                }


    /* 常量：十进制整型，如 1、 223、 10 等 */
    /* 此处疑似实际指的是字面量，且局限在了整型字面量中的 decimal-literal */
    /* 似乎是后加的区分，但在此还是以细分为尊。 正好 CONST 留给 const */
    /* https://en.cppreference.com/w/c/language/integer_constant */
    /* https://en.cppreference.com/w/cpp/language/integer_literal */
    /* 以后考虑外加浮点数、非十进制数，乃至字符（串）的处理 */
    /* a.b1() 和 1.4 */
    /* C99 decimal constant */
    /* The ‘{-}’ operator computes the difference of two character classes.
    The ‘{-}’ operator is left associative */
([[:digit:]]{-}[0])[[:digit:]]*    {
                    //printf("Literal\n");
                    //叫做 NUMBER 是为了方便之后扩展 Parser 中句法。
                    yylval.num = atof(yytext);
                    return NUMBER;
                }


"//".*
[ \t] /* ignore whitespace */

\\\n { printf("c> "); } /* ignore line continuation */

\r\n|\n|\r { return CRLF; }

.           { yyerror("Mystery character %c\n", *yytext); }
%%
