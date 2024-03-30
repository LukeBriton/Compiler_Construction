win_bison -d MyBison.y

win_flex MyFlex.l
gcc lex.yy.c MyBison.tab.c -o Compiler.exe
Compiler