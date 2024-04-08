%{
#include<stdio.h>
#include<string.h>
%}

keyword			"int"|"return"|"main"|"println_int"
digit 			[0-9]
letter 			[A-Za-z]
id 				({letter}|_)({letter}|{digit}|_)*
number 			[1-9]{digit}*|0
vacancy 			[\t\n ]
%%
{vacancy}+ ;
{keyword}		{printf("KEYWORD: %s\n", yytext);}
{id}				{printf("ID: %s\n", yytext);}
{number} 		{printf("CONSTANT: %s\n",yytext);}
"=" 				{printf("ASSIGN: %s\n",yytext);}
"+" 				{printf("ADD: %s\n",yytext);}
"-" 				{printf("SUB: %s\n",yytext);}
"*"				{printf("MUL: %s\n",yytext);}
"/" 				{printf("DIV: %s\n",yytext);}
"%" 				{printf("MOD: %s\n",yytext);}
"<" 				{printf("LT: %s\n",yytext);}
"<=" 			{printf("LE: %s\n",yytext);}
">" 				{printf("GT: %s\n",yytext);}
">=" 			{printf("GE: %s\n",yytext);}
"==" 			{printf("EQ: %s\n",yytext);}
"!=" 				{printf("NEQ: %s\n",yytext);}
"&"				{printf("AND: %s\n",yytext);}
"|"				{printf("OR: %s\n",yytext);}
"^"				{printf("XOR: %s\n",yytext);}
";"				{printf("SEMI: %s\n",yytext);}
"{"				{printf("LB: %s\n",yytext);}
"}"				{printf("RB: %s\n",yytext);}
"(" 				{printf("LP: %s\n",yytext);}
")" 				{printf("RP: %s\n",yytext);}
%%
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
  return 0;
}
int yywrap()
{
return 1;
}

