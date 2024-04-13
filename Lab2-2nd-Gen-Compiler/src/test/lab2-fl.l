%{
#include<stdio.h>
#include<string.h>
%}

keyword			"int"|"return"|"main"|"println_int"
digit 			[0-9]
letter 			[A-Za-z]
id 				({letter}|_)({letter}|{digit}|_)*
number 			[1-9]{digit}*|0
vacancy 		[\t\n ]
%%
{vacancy}+ ;
{keyword}		{fprintf(yyout,"KEYWORD:%s\n", yytext);}
{id}			{fprintf(yyout,"ID:%s\n", yytext);}
{number} 		{fprintf(yyout,"CONSTANT:%s\n",yytext);}
"=" 			{fprintf(yyout,"ASSIGN:%s\n",yytext);}
"+" 			{fprintf(yyout,"ADD:%s\n",yytext);}
"-" 			{fprintf(yyout,"SUB:%s\n",yytext);}
"*"				{fprintf(yyout,"MUL:%s\n",yytext);}
"/" 			{fprintf(yyout,"DIV:%s\n",yytext);}
"%" 			{fprintf(yyout,"MOD:%s\n",yytext);}
"<" 			{fprintf(yyout,"LT:%s\n",yytext);}
"<=" 			{fprintf(yyout,"LE:%s\n",yytext);}
">" 			{fprintf(yyout,"GT:%s\n",yytext);}
">=" 			{fprintf(yyout,"GE:%s\n",yytext);}
"==" 			{fprintf(yyout,"EQ:%s\n",yytext);}
"!=" 			{fprintf(yyout,"NEQ:%s\n",yytext);}
"&"				{fprintf(yyout,"AND:%s\n",yytext);}
"|"				{fprintf(yyout,"OR:%s\n",yytext);}
"^"				{fprintf(yyout,"XOR:%s\n",yytext);}
";"				{fprintf(yyout,"SEMI:%s\n",yytext);}
"{"				{fprintf(yyout,"LB:%s\n",yytext);}
"}"				{fprintf(yyout,"RB:%s\n",yytext);}
"(" 			{fprintf(yyout,"LP:%s\n",yytext);}
")" 			{fprintf(yyout,"RP:%s\n",yytext);}
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
yyout=fopen(argv[2],"w");
yylex();
  return 0;
}
int yywrap()
{
return 1;
}

