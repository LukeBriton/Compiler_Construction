%{
#include<stdio.h>
#include<string.h>
#include"defs.h"
%}

keyword			"int"|"return"|"main"|"println_int"
digit 			[0-9]
letter 			[A-Za-z]
id 				({letter}|_)({letter}|{digit}|_)*
number 			[1-9]{digit}*|0
vacancy 		[\t\r\n ]
%%
{vacancy}+ ;
{keyword}		{TokenIn("KEYWORD", yytext);}
{id}			{TokenIn("ID", yytext);}
{number} 		{TokenIn("CONSTANT", yytext);}
"=" 			{TokenIn("ASSIGN", yytext);}
"+" 			{TokenIn("ADD", yytext);}
"-" 			{TokenIn("SUB", yytext);}
"*"				{TokenIn("MUL", yytext);}
"/" 			{TokenIn("DIV", yytext);}
"%" 			{TokenIn("MOD", yytext);}
"<" 			{TokenIn("LT", yytext);}
"<=" 			{TokenIn("LE", yytext);}
">" 			{TokenIn("GT", yytext);}
">=" 			{TokenIn("GE", yytext);}
"==" 			{TokenIn("EQ", yytext);}
"!=" 			{TokenIn("NEQ", yytext);}
"&"				{TokenIn("AND", yytext);}
"|"				{TokenIn("OR", yytext);}
"^"				{TokenIn("XOR", yytext);}
","				{TokenIn("COMMA", yytext);}
";"				{TokenIn("SEMI", yytext);}
"{"				{TokenIn("LB", yytext);}
"}"				{TokenIn("RB", yytext);}
"(" 			{TokenIn("LP", yytext);}
")" 			{TokenIn("RP", yytext);}
    /* Eat undifined chars up */
    /* 否则就会像 e07.c 一样，开头的 “ï»¿” 
     * 其实是 UTF-8 BOM (Byte Order Mark)
     * 字节顺序标记 EF BB BF
     * 在以 UTF-8 编码时看不见
     * 在读入后被 ECHO 到输出中了
     */
    /* flex acts as though there is a default rule
     * at the end of the scanner that copies
     * otherwise unmatched input to yyout. */
.               {}
%%

int yywrap()
{
    return 1;
}

