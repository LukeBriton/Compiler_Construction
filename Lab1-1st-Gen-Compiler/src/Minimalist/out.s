.intel_syntax noprefix # 使用 Intel 语法
.global main # 声明 main 函数为全局符号，这使得链接器能够识别程序的入口点。
.extern printf # 声明外部函数 printf，表示该函数在其他地方定义，通常是 C
.data # 开始数据段，用于定义程序中的初始化数据。
format_str:
.asciz "%d\n" # 定义一个用于 printf 的格式字符串，输出整数并换行。
.text # 开始代码段，包含程序的实际指令。
main:
push ebp # 将基指针寄存器 ebp 的当前值压入堆栈， 保存上一个函数栈帧的基指针
mov ebp, esp # 将栈指针 esp 的值复制到基指针 ebp ， 设置新的栈帧基指针
sub esp, 0x100 # 从栈指针 esp 减去 256 字节，为局部变量分配栈空间



mov eax, 1
mov DWORD PTR [ebp-4], eax
mov eax, 2
mov DWORD PTR [ebp-8], eax
mov eax, 3
mov DWORD PTR [ebp-12], eax
mov eax, 3










# 打印 d (当前 eax 的值)
push eax # 将结果 (eax 的值) 作为 printf 的参数
push offset format_str # 将格式字符串的地址作为 printf 的参数
call printf # 调用 printf 函数
add esp, 8 # 清理栈
# 恢复 eax 的值并退出 main
pop eax
leave
ret
