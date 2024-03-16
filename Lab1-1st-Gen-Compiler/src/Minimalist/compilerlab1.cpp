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


bool isKeyword(const string& str) {
    return str == "int" || str == "return";
}

bool isIdentifier(const string& str) {
    return str.size() == 1 && isalpha(str[0]);
}

bool isConstant(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return !str.empty();
}

bool isOperator(char ch) {
    return ch == '=' || ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool isSeparator(char ch) {
    return ch == ';';
}

TokenType getTokenType(const string& token) {
    if (isKeyword(token)) return KEYWORD;
    if (isIdentifier(token)) return IDENTIFIER;
    if (isConstant(token)) return CONSTANT;
    if (token.size() == 1 && isOperator(token[0])) return OPERATOR;
    if (token.size() == 1 && isSeparator(token[0])) return SEPARATOR;
    return UNKNOWN;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        string token;
        for (char ch : line) {
            if (isspace(ch)) {
                if (!token.empty()) {
                    cout << "Token: " << token << ", Type: " << getTokenType(token) << endl;
                    token.clear();
                }
            } else if (isOperator(ch) || isSeparator(ch)) {
                if (!token.empty()) {
                    cout << "Token: " << token << ", Type: " << getTokenType(token) << endl;
                    token.clear();
                }
                cout << "Token: " << ch << ", Type: " << getTokenType(string(1, ch)) << endl;
            } else {
                token += ch;
            }
        }
        if (!token.empty()) {
            cout << "Token: " << token << ", Type: " << getTokenType(token) << endl;
        }
    }

    inputFile.close();
    return 0;
}
