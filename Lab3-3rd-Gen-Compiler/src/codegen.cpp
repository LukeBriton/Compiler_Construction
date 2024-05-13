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
    cout<<".globl main # 声明 main 函数为全局符号，使得模拟器能识别程序的入口点"<<endl;
    cout<<"main:"<<endl;
    cout<<"move $fp, $sp # 设置帧指针"<<endl;
    cout<<"addiu $sp, $sp, -0x100 # 为局部变量分配栈空间"<<endl<<endl;
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
