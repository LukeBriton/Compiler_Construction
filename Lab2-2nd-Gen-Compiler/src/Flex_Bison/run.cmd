win_bison -d MyBison.y

win_flex MyFlex.l
gcc MyBison.tab.c Function.c lex.yy.c -o Compiler.exe
Compiler