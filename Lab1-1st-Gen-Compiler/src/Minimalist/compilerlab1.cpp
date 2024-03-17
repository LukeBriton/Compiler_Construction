// Minimalist: More is Less
// 暴力 Dirty C++ STL

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

enum TokenType {
    KEYWORD,//关键字
    IDENTIFIER,//标识符
    CONSTANT,//常量
    OPERATOR,//操作符
    SEPARATOR,//分隔符
    UNKNOWN
};

int current_num; // 存放读入的当前整数
char lval; // 左值，等号左边，或者声明变量时唯一的标识符。
int rval; // 右值，四则运算用 Constant Folding 常量折叠
int esp; // 栈顶指针
char lastOp;
bool isDeclaration = false;
bool isAssignment = false;
bool isReturn = false;

// abc...xyzABC...XYZ 至多有52个 相当于映射 检索 O(1)
// 反正变量名不能重合，是单射、集合。
int alphabet_pos[52]; // 变量/标识符在栈帧中的位置 & 判断是否用得上（0 为未声明），各个差4，最大值即为栈顶esp。
int value[52]; // 变量的值

// 可能用不着这仨
//stack<char> var; // 会用到多个临时寄存器（指a = b + c + d;到了汇编代码中现算的情形。）
//stack<char> op; 
// Constant Propagation 常量传播 减少寄存器操作
// 解决 int a = b * c + d / e - 9; 的问题。
// 问题在于：很受立即数长度的限制。
// 采用 x86 Intel Syntax，看着比 AT&T 直观
// 又无须像 MIPS 一样又是 lui 又是 ori，连 32 位的都这么麻烦。
// stack<int> operands; 

bool isKeyword(const string& str) {
    return str == "int" || str == "return";
}

bool isIdentifier(const string& str) {
    return str.size() == 1 && isalpha(str[0]);
}

bool isConstant(const string& str) {
    string num; // 默认构造空串
    for (char c : str) {
        if (!isdigit(c))
            return false;
        else
            num+=c;
    }
    if(!str.empty()) current_num = stoi(num);
    return !str.empty();
}

bool isOperator(char ch) {
    return ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool isSeparator(char ch) {
    return ch == ';';
}

// 处理标识符的函数
int getAlphabetIndex(char ch) {
    //cout << ch << endl;
    if (islower(ch)) return ch - 'a';
    if (isupper(ch)) return 26 + ch - 'A';
    return -1; // 非法标识符
}

// 总感觉和底下 int main(int, char **) 函数中的操作有重复。
// 待优化
TokenType getTokenType(const string& token) {
    if (isKeyword(token)) return KEYWORD;
    if (isIdentifier(token)) return IDENTIFIER;
    if (isConstant(token)) return CONSTANT;
    if (token.size() == 1 && isOperator(token[0])) return OPERATOR;
    if (token.size() == 1 && isSeparator(token[0])) return SEPARATOR;
    return UNKNOWN;
}

int main(int argc, char *argv[]) {
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        string token;
        for (char ch : line) {
            if (isspace(ch) || isOperator(ch) || isSeparator(ch)) {
                if (!token.empty()) {
                    TokenType type = getTokenType(token);
                    if (type == KEYWORD) {
                        if(token == "int") // 感觉 int 其实没多大用。。。 或者压根可以根据 '=' 来判断？
                        {                  // 不过这里大概确实方便些。
                            //cout << "IIIIINNNNNTTTTT" << endl;
                            isDeclaration = true;
                            // 新声明，那就新入栈。
                            // 不考虑上限，反正到不了。
                            // 不考虑重复声明。 // 算了最好之后补上一个检验。
                            // 或者在IDENTIFIER处。
                            // esp += 4;
                        }
                        else if (token == "return") // 没必要 else if，此处方便阅读。
                        {
                            // return a+b+c; // 其实还是右值表达式计算
                            // 加个判断条件，因为没有等号了
                            // 还是要用到 lastOp
                            isReturn = true;
                        }
                    }
                    // Constant 只会出现在等号右边，应当与标识符变量的运算兼容。
                    else if (type == CONSTANT) {
                        if (lastOp == '='||(isReturn && !lastOp)) {
                            // 不考虑逗号、连等赋值。
                            // int g, h, i;
                            // h = g = i = 8;
                            rval = current_num;
                        }
                        else {
                            switch (lastOp) {
                                case '+': rval += current_num; break;
                                case '-': rval -= current_num; break;
                                case '*': rval *= current_num; break;
                                case '/': rval /= current_num; break;
                            }
                        }
                    }
                    // 不考虑非法语法，比如
                    // 变量未声明、定义
                    // int a = b + c; // b, c undefined/declared var
                    // e = 9; // e undeclared.
                    // 不考虑逗号
                    // Identifier 出现在等号右边时，类似 Constant 的处理。
                    // 没有等号/前有int，那就是声明，声明的话不需要赋值，但需要分配空间，动栈指针
                    // 没有等号/前有return 右值计算，之后返回
                    // 前有等号 右值计算
                    else if (type == IDENTIFIER) {
                        //cout << "token[0]: " << token[0] << endl; 
                        int index = getAlphabetIndex(token[0]);
                        //cout << "index: " << index << endl;
                        //cout << "alphabet_pos[index]: " << alphabet_pos[index] << endl;
                        if(!lastOp && !isReturn)
                        {
                            // 作为左值
                            lval = token[0];
                            //cout << "LVAL: " << token[0] << endl;
                        }
                        // int a = 9;
                        // a;
                        if (alphabet_pos[index]) {
                            if (lastOp == '='||(isReturn && !lastOp)) {
                                rval = value[index];
                            }
                            else {
                                switch (lastOp) {
                                    case '+': rval += value[index]; break;
                                    case '-': rval -= value[index]; break;
                                    case '*': rval *= value[index]; break;
                                    case '/': rval /= value[index]; break;
                                }
                            }
                        }
                        else // 不考虑非法输入，那就只能是在声明/声明+赋值的过程中。
                        // int a;
                        // int b = 8;
                        // a = 9; // 其实是赋值。这个不会到此处，因为已经分配好空间了。
                        // a = a + b; // 也是赋值。这个也已经分配好了，分配好的直接用空间就行。
                        // d = 10; // 非法输入
                        // 目前还无法得知等号，只是先分配。
                        {
                            if(isDeclaration)
                            {
                                // 进栈
                                esp+=4;
                                //cout << "ESP+=4    \n";
                                alphabet_pos[index] = esp;
                                // 假如声明时没有赋值，权当默认初始化为0了。
                                // 也就是说单看数组无法区分是“声明了赋值0”还是“声明了未赋值”
                                // 不区分、不考虑
                                // 我们只需要在特定的行根据 isDeclaration 跟 isAssignment 的组合选择输出与否。
                            }
                        }
                    }

                    token.clear();
                }
            }
            if (isOperator(ch)) {
                lastOp = ch; // 保存当前操作符
                if(ch == '=')
                    isAssignment = true;
                token.clear();
            }
            else if (isSeparator(ch)) {
                if(isAssignment)
                {
                    value[getAlphabetIndex(lval)] = rval;
                    cout << "mov eax, " << rval << endl;
                    cout << "mov DWORD PTR [ebp-" << alphabet_pos[getAlphabetIndex(lval)] << "], eax" << endl;
                }
                else if(isReturn)
                {
                    cout << "mov eax, " << rval << endl;
                }

                lval = 0;
                rval = 0; // 重置 rval 为下一个表达式准备
                lastOp = 0; // 重置操作符
                isDeclaration = false;
                isAssignment = false;
                isReturn = false;
                token.clear();
            }
            else if (isspace(ch))
                token.clear();
            else{
                token += ch;
            }
        }
    }

    inputFile.close();
    return 0;
}
