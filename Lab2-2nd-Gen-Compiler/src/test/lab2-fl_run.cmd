win_flex lab2-fl.l
del lex.yy.cpp
rename lex.yy.c lex.yy.cpp
g++ lex.yy.cpp test.cpp -o test
test.exe cases/mycase3.c
pause