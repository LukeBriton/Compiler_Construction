//并没有考虑main函数中有参数，其实main函数是可以直接不管的
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <map>
#include "defs.h"
using namespace std;

std::vector<Token> TokenVector;

void TokenIn(const std::string& a, const std::string& b)
{
    TokenVector.push_back(Token(a, b));
}

void Preamble()
{
    cout<<".data"<<endl;
    cout<<"newline: .asciiz \"\\n\" # 定义一个字符串， 用于输出换行。"<<endl;
    cout<<".text"<<endl;
    cout<<".globl main # 声明 main 函数为全局符号，使得模拟器能识别程序的入口点"<<endl;
    cout<<"main:"<<endl;
    cout<<"move $fp, $sp # 设置帧指针"<<endl;
    cout<<"addiu $sp, $sp, -0x100 # 为局部变量分配栈空间"<<endl<<endl;
}

//IDs按声明顺序记录每个变量
//ID_Number 变量个数
vector<string> IDs;
//int ID_Number = 0;
int TempID=0; // 存放栈内的中间变量个数
//regnum 当前可用的存放临时变量的寄存器号，MIPS中有t0-t9共十个
//update_regnum 用了一个寄存器后就让寄存器号+1，用到了最后一个t9则重新回去用t0
//int regnum = 0;
//void update_regnum(){
//    regnum += 1;
//    regnum %= 10;
//}

//运算符的优先级
int getPrecedence(string& op){
    if(op == "|") return 1;
    if(op == "^") return 2;
    if(op == "&") return 3;
    if(op == "==" || op == "!=") return 4;
    if(op == ">" || op == ">=" || op == "<" || op == "<=") return 5;
    if(op == "+" || op == "-") return 6;
    if(op == "*" || op == "/" || op == "%") return 7;
    return 0;
}

int isoperator(string& op){
    if(op == "+" || op == "-" || op == "*" || op == "/" || op == "%" || op == ">" || op == ">=" || op == "<" || op == "<=" || op == "==" || op == "!="|| op=="&" || op=="|"||op=="^")
        return 1;
    else
        return 0;
}

//将复杂赋值语句中“=”后面的表达式转化为后缀表达式
vector<Token> Infix2Suffix(vector<Token>& assignment){
    stack<Token> stack;
    vector<Token> suffix;
    suffix.reserve(100);
    for(vector<Token>::iterator it = assignment.begin() + 2; it != assignment.end(); it++){
        //如果是操作数，直接添加到后缀表达式
        if((*it).type == "ID" || (*it).type == "CONSTANT") suffix.push_back(*it);
        //如果是左括号，入栈
        else if((*it).type == "LP") stack.push(*it);
        //如果是右括号，弹出栈中元素直到遇到左括号
        else if((*it).type == "RP"){
            while (!stack.empty() && stack.top().value != "(") {
                suffix.push_back(stack.top());
                stack.pop();
            }
            stack.pop();  // 弹出左括号
        }
        //如果是运算符
        else{
            while (!stack.empty() && getPrecedence((*it).value) <= getPrecedence(stack.top().value)) {
                suffix.push_back(stack.top());
                stack.pop();
            }
            stack.push((*it));
        }

    }
    //将栈中剩余的运算符添加到后缀表达式
    while (!stack.empty()) {
        suffix.push_back(stack.top());
        stack.pop();
    }
    return suffix;
}


//处理int声明语句，主要用来记录各个变量声明的顺序
void Process_Declaration(string& ID){
    //cout<<"int"<<ID<<endl;
    IDs.push_back(ID);
    //ID_Number++;
}

//处理println_int语句
//简单，找到要打印的那个变量是第几个声明的就行了
void Process_Println(const Token& token){
    //cout<<"//print "<<token.value<<endl; 
    //打印的是数字
    if(token.type == "CONSTANT")
        cout<<"li $a0, "<<token.value<<endl;
    //打印的是变量
    if(token.type == "ID")
    {
        int index = find(IDs.begin(), IDs.end(), token.value) - IDs.begin();
        cout<<"lw $a0, "<<-4*(index + 1)<<"($fp)"<<endl; // 幽默，($fp)写成了(&fp)进而全WA，修改后2分。
    }
    cout<<"li $v0, 1"<<endl;
    cout<<"syscall"<<endl;
    cout<<"li $v0, 4"<<endl;
    cout<<"la $a0, newline"<<endl;
    cout<<"syscall"<<endl;
}

//处理return语句
//永远是return 0，直接抄
void Process_Return(const Token& token){
    //cout<<"return 0"<<endl;
    //cout<<"addi $sp, $sp, "<<4*TempID<<endl;
    if(token.type == "CONSTANT")
        cout<<"li $v0, "<<token.value<<endl;
    if(token.type == "ID")
    {
        int index = find(IDs.begin(), IDs.end(), token.value) - IDs.begin();
        cout<<"lw $v0, "<<-4*(index + 1)<<"($fp)"<<endl; // li -> lw
    }
    cout<<"move $v1, $v0"<<endl;
    cout<<"li $v0, 10"<<endl;
    cout<<"syscall"<<endl;
};

//处理赋值语句
void Process_Assignment(vector<Token> assignment){
    //cout<<"//";
    //for(vector<Token>::iterator it = assignment.begin(); it != assignment.end(); it++){
    //    cout<<(*it).value<<" ";
    //}
    //cout<<endl;

    //统计赋值语句中操作符的个数(不包括=和())
    int op_count = 0;
    for(vector<Token>::iterator it = assignment.begin(); it != assignment.end(); it++){
        if (isoperator((*it).value)) op_count++;
    }

    //如果没有操作符，则赋值语句是形如a = 5或者形如a = b的
    if(op_count == 0){
        //寻找要赋值变量的index
        int index = find(IDs.begin(), IDs.end(), assignment[0].value) - IDs.begin();
        //赋值的值是数字
        if(assignment[2].type == "CONSTANT"){
            //提取数字
            string number = assignment[2].value;
            cout<<"li $v0, " + number<<endl;
        }
        //赋值的值是变量
        else{
            int index1 = find(IDs.begin(), IDs.end(), assignment[2].value) - IDs.begin();
            cout<<"lw $v0, "<<-4*(index1 + 1)<<"($fp)"<<endl;
        }
        cout<<"sw $v0, 0($sp)"<<endl;
        cout<<"addiu $sp, $sp, -4"<<endl;
        cout<<"lw $v0, 4($sp)"<<endl;
        cout<<"sw $v0, "<<-4*(index + 1)<<"($fp)"<<endl;
        cout<<"addiu $sp, $sp, 4"<<endl;
    }

    //复杂表达式赋值语句，过程相当于利用栈求后缀表达式的值
    else{
        //得到后缀算术表达式
        vector<Token> expression = Infix2Suffix(assignment);
        //for(vector<Token>::iterator it = expression.begin(); it != expression.end(); it++) cout<<(*it).value<<" ";
        //cout<<endl;
        stack<Token> stack;
        for(vector<Token>::iterator it = expression.begin(); it != expression.end(); it++){
            //map记录变量或数字存放的寄存器
            //存放中间结果的寄存器也可以当做是一个变量
            map<string,string> map;

            //如果是变量或者数字，入栈
            if((*it).type == "ID" || (*it).type == "CONSTANT") stack.push(*it);
            //如果是操作符，从栈中提取两个操作数进行运算
            else{

                Token token1 = stack.top();stack.pop();
                Token token2 = stack.top();stack.pop();
                int offset = 0; // 给存放到栈内的中间变量分配的空间
                offset = 4 * ((token1.type == "TempID") + (token2.type == "TempID"));

                //操作数1 token1 放在t0中

                //变量 lw出来
                if(token1.type == "ID"){
                    int index = find(IDs.begin(), IDs.end(), token1.value) - IDs.begin();
                    cout<<"lw $t0, "<<-4*(index + 1)<<"($fp)"<<endl;
                } 
                //数字 li出来
                else if(token1.type == "CONSTANT"){
                    cout<<"li $t0, "<<token1.value<<endl;
                }
                //临时变量
                else{
                    //int index = atoi((token1.value.substr(1)).c_str());
                    //cout<<"lw $t0, "<<4*(TempID-1-index)<<"($sp)"<<endl;
                    cout<<"lw $t0, 0($sp)"<<endl;
                }

                //操作数2 token2 放在t1中
                
                if(token2.type == "ID"){
                    int index = find(IDs.begin(), IDs.end(), token2.value) - IDs.begin();
                    cout<<"lw $t1, "<<-4*(index + 1)<<"($fp)"<<endl;
                } 
                else if(token2.type == "CONSTANT"){
                    cout<<"li $t1, "<<token2.value<<endl; // 敲成token1了之前
                }
                else{
                    //int index = atoi((token2.value.substr(1)).c_str());
                    //cout<<"lw $t1, "<<4*(TempID-1-index)<<"($sp)"<<endl;
                    if(offset == 4)
                        cout<<"lw $t1, 0($sp)"<<endl;
                    else if(offset == 8)
                        cout<<"lw $t1, 4($sp)"<<endl;
                }

                //运算符op
                string op = (*it).value;
                //计算token2 op token1
                if(op == "+") cout<<"add $t2, $t1, $t0"<<endl;
                if(op == "-") cout<<"sub $t2, $t1, $t0"<<endl;
                if(op == "*") cout<<"mul $t2, $t1, $t0"<<endl;
                if(op == "/") cout<<"div $t2, $t1, $t0"<<endl;
                if(op == "%"){
                    cout<<"div $t1, $t0"<<endl;  // 运算数顺序并没有错
                    cout<<"mfhi $t2"<<endl; // 忘加逗号 // 现在不需要逗号了，因为%hi的特殊性，只能用mfhi
                } 
                if(op == "&") cout<<"and $t2, $t1, $t0"<<endl;
                if(op == "|") cout<<"or $t2, $t1, $t0"<<endl;
                if(op == "^") cout<<"xor $t2, $t1, $t0"<<endl;
                if(op == "=="){
                    cout<<"xor $t2, $t1, $t0"<<endl;
                    cout<<"sltiu $t2, $t2, 1"<<endl;
                }
                if(op == "!="){ // （之前仍只用寄存器的时候）改完之后9分
                    cout<<"slt $t2, $t1, $t0"<<endl;
                    cout<<"slt $t0, $t0, $t1"<<endl;
                    cout<<"or $t2, $t0, $t2"<<endl;
                }
                if(op == "<") cout<<"slt $t2, $t1, $t0"<<endl;
                if(op == "<="){ // 之前顺序 "<=" 和 ">=" 搞混了
                    cout<<"slt $t2, $t0, $t1"<<endl;
                    cout<<"xori $t2, $t2, 1"<<endl;
                }
                if(op == ">") cout<<"slt $t2, $t0, $t1"<<endl;
                if(op == ">="){
                    cout<<"slt $t2, $t1, $t0"<<endl;
                    cout<<"xori $t2, $t2, 1"<<endl;
                }

                if(offset)
                {
                    cout<<"addiu $sp, $sp, "<<offset<<endl;
                    TempID -= offset/4;
                }
                //cout << TempID << endl;
                //中间结果因此命名为ai(i=0,1,2,...)，存入内存sp-4*i处
                TempID ++;
                cout<<"addiu $sp, $sp, -4"<<endl;
                cout<<"sw $t2, 0($sp)"<<endl;
                //结果入栈 实际上是存放中间结果的中间变量入栈
                Token result = {"TempID", "Temp" + to_string(TempID)};
                //Token result = {"TempID", "a" + to_string(TempID)};
                //TempID++;
                //map[result.value] = "$t" + to_string(regnum);
                stack.push(result);
                //update_regnum();
            }
        }
//栈顶即是最后的结果，将其赋值给要赋值的那个变量
        int index = find(IDs.begin(), IDs.end(), assignment[0].value) - IDs.begin();
        //int index1 = atoi((stack.top().value.substr(1)).c_str());
        //cout<<"lw $v0, "<<4*(TempID-1-index1)<<"($sp)"<<endl;
        cout<<"lw $v0, 0($sp)"<<endl;
        //cout<<"addiu $sp, $sp, 4"<<endl;//不要加这句，留待以后再改吧。
        TempID--;
        //cout << TempID <<endl;
        //cout<<"move $v0, " + stack.top().value<<endl;
        //cout<<"sw $v0, 0($sp)"<<endl;
        /*
         * Despite its name, add immediate unsigned (addiu) is used
         * to add constants to signed integers when we don't care about
         * overflow. MIPS has no subtract immediate instruction, and
         * negative numbers need sign extension, so the MIPS architects 
         * decided to sign-extend the immediate field.
         */
        cout<<"addiu $sp, $sp, -4"<<endl;
        cout<<"lw $v0, 4($sp)"<<endl;
        cout<<"sw $v0, "<<-4*(index + 1)<<"($fp)"<<endl;
        cout<<"addiu $sp, $sp, 4"<<endl;
    } 
    

}


int main(int argc, char *argv[]) {
    //打开词法分析结果，词法分析输出格式Type:Value

    if(argc > 1)
    {
        if(!(yyin = fopen(argv[1], "r")))
        {
            perror(argv[1]);
            return (1);
        }
    }
    yylex();
    Preamble();
    //依次读取每个token
    for(vector<Token>::iterator it = TokenVector.begin(); it != TokenVector.end(); it++){
            //cout<<(*it).type<<":"<<(*it).value<<endl;

            //处理int main(int argv, int argc)

            //处理int声明语句，关键在int后面的那个标识符
            if((*it).value == "int" && (*(it+1)).value != "main") Process_Declaration((*(it+1)).value);

            //处理return语句
            if((*it).value == "return") Process_Return((*(it+1)));

            //处理println_int语句，关键在println_int括号中的标识符或者数字
            if((*it).value == "println_int") Process_Println((*(it+2)));

            //处理赋值语句，对整句赋值语句进行分析
            if((*it).value == "="){
                vector<Token> assignment;
                for(vector<Token>::iterator it1 = it-1; (*it1).value != ";"; it1++){
                    assignment.push_back(*it1);
                    //cout<<(*it1).type<<":"<<(*it1).value<<endl;
                }
                 Process_Assignment(assignment);
            }
    }

    return 0;
}
