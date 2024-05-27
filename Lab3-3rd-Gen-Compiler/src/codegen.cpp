#include "defs.h"
#include "declare.h"

// MIPS Code Generator
// 改编自 Code generator for x86-64
// Copyright (c) 2019 Warren Toomey, GPL3

// using namespace std; 
// https://stackoverflow.com/questions/1452721/whats-the-problem-with-using-namespace-std
using std::cout;
using std::endl;

// Print out the assembly preamble
void cgpreamble() {
    cout<<".data"<<endl;
    cout<<"newline: .asciiz \"\\n\" # 定义一个字符串， 用于输出换行。"<<endl;
    cout<<".text"<<endl;
    cout<<endl;
    // cout<<".globl main # 声明 main 函数为全局符号，使得模拟器能识别程序的入口点"<<endl;
    // cout<<"main:"<<endl;
    // cout<<"move $fp, $sp # 设置帧指针"<<endl;
    // cout<<"addiu $sp, $sp, -0x100 # 为局部变量分配栈空间"<<endl<<endl;
}

void cgadd() {
    cout<<"add $t2, $t1, $t0"<<endl;
}
void cgsub() {
    cout<<"sub $t2, $t1, $t0"<<endl;
}
void cgmul() {
    cout<<"mul $t2, $t1, $t0"<<endl;
}
void cgdiv() {
    cout<<"div $t2, $t1, $t0"<<endl;
}

void cgand() {
    cout<<"and $t2, $t1, $t0"<<endl;
}
void cgor() {
    cout<<"or $t2, $t1, $t0"<<endl;
}
void cgxor() {
    cout<<"xor $t2, $t1, $t0"<<endl;
}

void cgmod() {
    cout<<"div $t1, $t0"<<endl;
    cout<<"mfhi $t2"<<endl; // 因为%hi的特殊性，只能用mfhi
}

void cggt() {
    cout<<"slt $t2, $t0, $t1"<<endl;
}
void cglt() {
    cout<<"slt $t2, $t1, $t0"<<endl;
}
void cgge() {
    cout<<"slt $t2, $t1, $t0"<<endl;
    cout<<"xori $t2, $t2, 1"<<endl;
}
void cgle() {
    cout<<"slt $t2, $t0, $t1"<<endl;
    cout<<"xori $t2, $t2, 1"<<endl;
}
void cgneq() {
    cout<<"slt $t2, $t1, $t0"<<endl;
    cout<<"slt $t0, $t0, $t1"<<endl;
    cout<<"or $t2, $t0, $t2"<<endl;
}
void cgeq() {
    cout<<"xor $t2, $t1, $t0"<<endl;
    cout<<"sltiu $t2, $t2, 1"<<endl;
}


//&&
void cgland() {
    //初始化t2为0
    cout<<"ori $t2, $zero, 0"<<endl;
    //判断t0是否为0
    cout<<"sltu $t3, $zero, $t0"<<endl;
    //判断t1是否为0
    cout<<"sltu $t4, $zero, $t1"<<endl;
    //and操作得到最后的结果，保存在t2中
    cout<<"and $t2, $t3, $t4"<<endl;
}
//||
void cglor() {
    //初始化t2为0
    cout<<"ori $t2, $zero, 0"<<endl;
    //判断t0是否为0
    cout<<"sltu $t3, $zero, $t0"<<endl;
    //判断t1是否为0
    cout<<"sltu $t4, $zero, $t1"<<endl;
    //or操作得到最后的结果，保存在t2中
    cout<<"or $t2, $t3, $t4"<<endl;
}
//-
void cgneg() {
    cout<<"sub $t2, $zero, $t1"<<endl;
}
//!
void cglnot() {
    //检查t0是否为0，是的话t2=!t0=1
    cout<<"sltu $t2, $t1, 1"<<endl;
}
//~
void cgnot() {
    cout<<"nor $t2, $t1, $zero"<<endl;
}

// 适用于作为 exp（返回值参与运算）的情形
void cgfunccall(int value)
{
    cout<<"jal " << funcname(value) << " # 调用函数"<<endl;
    cout<<"addiu $sp, $sp, " << 4 * get_arg_num() << " # 清理栈" <<endl;
    cout<<"addiu $sp, $sp, -4 # 给函数返回值腾地儿"<<endl;
    cout<<"sw $v0, 0($sp) # 函数返回值入栈"<<endl; // 这前两步相当于中间变量的存储
    // cout<<"lw $t2, 0($sp) # 兼容 genAST"<<endl;// 这个用不着，原因是已经存放在栈顶了。
    
    // 或者，就得改 gen.cpp 中处理左右子树时的分类讨论
    // 加一种判断函数的，直接从 $v0 还是 $t2 读取？？？
    // cout<<"move $t2, $v0 # 懒省事"<<endl; // 搭配 genAST 最末
    // 暂时懒得改了
}


void cgfuncpreamble(const char* name, int type)
{
    addfunc(name, type);
    clearlocal();
    cout << ".globl " << name << "\n\n";
    cout << name << ":\n";
    cout << "addiu $sp, $sp, -8 # 为保存寄存器分配空间\n"; // 实验说明上的写法是 -4，详见 arg_pass
    // cout << "sw $ra, 0($sp) # 保存 ra\n";
    // cout << "sw $fp, 4($sp) # 保存 fp\n"; // 实验说明上的写法
    cout << "sw $fp, 0($sp) # 保存 fp\n";
    cout << "sw $ra, 4($sp) # 保存 ra\n";
    cout << "move $fp, $sp # 设置 fp 便于访问局部变量\n";
    cout << "addiu $sp, $sp, -0x100 # 为局部变量分配栈空间" <<endl;
}

void cgfuncpostamble()
{
    cout << "move $sp, $fp # 清理局部变量\n";
    // cout << "lw $fp, 4($sp) # 恢复 fp\n";
    // cout << "lw $ra, 0($sp) # 恢复 ra\n";
    cout << "lw $ra, 4($sp) # 保存 ra\n";
    cout << "lw $fp, 0($sp) # 保存 fp\n";
    cout << "addiu $sp, $sp, 8 # 清理为保存寄存器分配的空间，恢复栈指针\n";
    cout << "jr $ra # 返回\n\n";
}

void cgmainpreamble() {
    // 暂时不考虑调用 main 函数的情况
    clearlocal();
    cout<<".globl main # 声明 main 函数为全局符号，使得模拟器能识别程序的入口点"<<endl<<endl;
    cout<<"main:"<<endl;
    cout<<"move $fp, $sp # 设置帧指针"<<endl;
    cout<<"addiu $sp, $sp, -0x100 # 为局部变量分配栈空间"<<endl;
}

// TODO
// stmt.cpp 中其实应该调用此处接口来着。
void cgloadint(int value) {
    
}
void cgloadlocal(char *identifier) {

}
void cgstorlocal(int r, char *identifier) {
    
}

// error: no newline at end of file [-Werror,-Wnewline-eof]
// https://stackoverflow.com/questions/5813311/whats-the-significance-of-the-no-newline-at-end-of-file-log
