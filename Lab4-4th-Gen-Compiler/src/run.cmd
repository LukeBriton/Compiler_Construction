@echo off

rem 遍历cases文件夹
for %%f in (cases\*) do (
    echo 处理文件: %%f
    Compiler.exe "%%f"
    echo.
)

pause