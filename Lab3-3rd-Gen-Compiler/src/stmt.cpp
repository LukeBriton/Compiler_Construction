#include "defs.h"
#include "declare.h"
#include <sstream>
#include <queue>

// Parsing of statements
// Copyright (c) 2019 Warren Toomey, GPL3

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;
using std::queue;

// 忘记加 static 了
static ostringstream local;
static queue<string> arglistbufs;
static int arg_num = 0;

// TO MODIFY
// statements: statement
//      |      statement statements
//      ;
//
// statement: 'print' expression ';'
//      |     'int'   identifier ';'
//      |     identifier '=' expression ';'
//      ;
//
// identifier: T_IDENT
//      ;

void println_int_statement(struct ASTnode *exp) {
    // struct ASTnode *tree;
    // error: unused variable 'tree' [-Werror,-Wunused-variable]
    // int reg;
    // error: unused variable 'reg' [-Werror,-Wunused-variable]

    // 处理表达式
    if(exp->op == A_INTLIT)
    {
        cout<<"li $a0, "<<exp->v.intvalue<<endl;
    }
    else if(exp->op == A_IDENT)
    {
        cout<<"lw $a0, "<<-4*exp->v.intvalue<<"($fp)"<<endl;
    }
    else
    {
        genAST(exp);
        cout<<"lw $a0, 0($sp)"<<endl;
    }
    cout<<"li $v0, 1"<<endl;
    cout<<"syscall"<<endl;
    cout<<"li $v0, 4"<<endl;
    cout<<"la $a0, newline"<<endl;
    cout<<"syscall"<<endl;
}

// Parse the declaration of a variable
void var_declaration(const char* name) {
    addlocal(name);
}

void para_declaration(const char* name, int para_num) {
    addpara(name, para_num);
}

void assignment_statement(const char* name, struct ASTnode *exp) {
    int id;

    // Check it's been defined then make a leaf node for it
    if ((id = findlocal(name)) == -1) {
        yyerror("Undeclared variable %s", name);
    }
    
    // 处理表达式
    if(exp->op == A_INTLIT)
    {
        cout<<"li $v0, "<<exp->v.intvalue<<endl;
    }
    else if(exp->op == A_IDENT)
    {
        cout<<"lw $v0, "<<-4*exp->v.intvalue<<"($fp)"<<endl;
    }
    else
    {
        genAST(exp);
        cout<<"lw $v0, 0($sp)"<<endl;
    }
    cout<<"sw $v0, "<<-4*id<<"($fp)"<<endl;
}

void return_statement(struct ASTnode *exp, int scope)
{

    // 处理表达式
    if(exp->op == A_INTLIT)
    {
        cout<<"li $v0, "<<exp->v.intvalue<<endl;
    }
    else if(exp->op == A_IDENT)
    {
        cout<<"lw $v0, "<<-4*exp->v.intvalue<<"($fp)"<<endl;
    }
    else
    {
        genAST(exp);
        cout<<"lw $v0, 0($sp)"<<endl;
    }
    
    if(scope == 1)
    {
        cout<<"move $v1, $v0"<<endl;
        cout<<"li $v0, 10"<<endl;
        cout<<"syscall"<<endl;
    }

}

void arg_pass(struct ASTnode *exp)
{
    // https://stackoverflow.com/questions/5193173/getting-cout-output-to-a-stdstring
    // https://stackoverflow.com/questions/74255969/how-to-store-cout-in-string-and-then-output-the-string-to-console
    // https://en.cppreference.com/w/cpp/io/basic_ios/rdbuf
    // https://stackoverflow.com/questions/33601886/is-it-necessary-to-reset-rdbuf-of-cout-cerr-and-clog-if-they-have-been-changed
    auto cout_buff = cout.rdbuf(); // save pointer to std::cout buffer
    cout.rdbuf(local.rdbuf()); // substitute internal std::cout buffer with buffer of 'local' object

    int offset = 0; // 给存放到栈内的中间变量分配的空间

    // 处理表达式
    if(exp->op == A_INTLIT)
    {
        cout<<"li $v0, "<<exp->v.intvalue<<endl;
    }
    else if(exp->op == A_IDENT)
    {
        cout<<"lw $v0, "<<-4*exp->v.intvalue<<"($fp)"<<endl;
    }
    else
    {
        genAST(exp);
        offset += 4;
        cout<<"lw $v0, 0($sp)"<<endl;
    }

    if(offset)
        cout<<"addiu $sp, $sp, "<<offset<<endl;

    // 要是想达到 最左的参数存在地址最低处 $fp + 2*4
    // arglist 也应该从右往左挨个 (0)$sp = $v0 ，$sp -= 4。
    // 实在不行直接 当下的 $sp - 4 * argnum ？
    // $fp 减多少无所谓不会爆，但是 $sp 得腾出空间才行吧
    
    // 实验说明上的写法
    // cout<<"sw $v0, 0($sp) # 参数入栈"<<endl;
    // cout<<"addiu $sp, $sp, -4 # 为参数分配空间"<<endl;
    // 我怀疑这里的 -4 是为了，最后一个 -4 执行后腾出一个空间，
    // 用于与函数声明时存放 $ra, $fp（以及这里是反的为什么还能跑）
    // addiu $sp, $sp, -4 # 为保存寄存器分配空间
    // sw $ra, 0($sp) # 保存 ra
    // sw $fp, 4($sp) # 保存 fp
    // 为了下面这个，应该需要改 cgfuncpreamble 上面这个 -4 为 -8 来存 $ra, $fp
    // 以及 cgfuncpostamble！！！
    cout<<"addiu $sp, $sp, -4 # 为参数分配空间"<<endl;
    cout<<"sw $v0, 0($sp) # 参数入栈"<<endl; 

    // go back to old buffer
    std::cout.rdbuf(cout_buff);
}

int get_arg_num()
{
    return arg_num;
}

void arglist_buf(int arg_num)
{
    ::arg_num = arg_num;
    arglistbufs.push(local.str());

    // https://stackoverflow.com/questions/5288036/how-to-clear-ostringstream
    // https://stackoverflow.com/questions/624260/how-to-reuse-an-ostringstream/624291#624291
    // https://stackoverflow.com/questions/20731/how-do-you-clear-a-stringstream-variable
    local.str("");
    local.clear();
}

// https://stackoverflow.com/questions/29944985/is-there-a-way-to-pass-auto-as-an-argument-in-c
// https://stackoverflow.com/questions/2192547/where-is-the-c-auto-keyword-used
void arglist_output()
{
    cout << arglistbufs.front();
    arglistbufs.pop();
}

void void_func_call(const char* name)
{
    cout<<"jal " << name << " # 调用函数"<<endl;
    cout<<"addiu $sp, $sp, " << 4 * arg_num << " # 清理栈" <<endl;
}

void func_call(const char* name)
{
    cout<<"jal " << name << " # 调用函数"<<endl;
    cout<<"addiu $sp, $sp, " << 4 * arg_num << " # 清理栈" <<endl;
    // 考虑到返回值没有赋予的对象，也没必要再将 $v0 存在栈顶了
}

// error: no newline at end of file [-Werror,-Wnewline-eof]
// https://stackoverflow.com/questions/5813311/whats-the-significance-of-the-no-newline-at-end-of-file-log
