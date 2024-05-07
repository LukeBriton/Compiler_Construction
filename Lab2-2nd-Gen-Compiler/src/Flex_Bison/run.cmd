@echo off

win_bison -d MyBison.y
::del MyBison.tab.cpp
::rename MyBison.tab.c MyBison.tab.cpp

win_flex MyFlex.l
::del lex.yy.cpp
::rename lex.yy.c lex.yy.cpp

g++ MyBison.tab.c lex.yy.c codegen.cpp gen.cpp main.cpp stmt.cpp symtab.cpp ast.cpp -o Compiler.exe

rem 遍历cases文件夹
for %%f in (cases\*) do (
    echo 处理文件: %%f
    compiler.exe "%%f"
    echo.
)


pause