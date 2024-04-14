#include<vector>
#include<string>

extern int yylex(void);
extern FILE *yyin;  // 声明yyin

// 定义Token结构体
struct Token {
    std::string type;
    std::string value;
    Token(const std::string& type, const std::string& value) : 
        type(type), value(value) {}
};

extern std::vector<Token> TokenVector;  // 创建一个vector来存储Token结构体

extern void TokenIn(const std::string& a, const std::string& b);