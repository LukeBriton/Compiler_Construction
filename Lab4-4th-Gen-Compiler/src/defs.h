#include <iostream>
#include <string>

// So I don't have to include headers in .cpps
// wherever cout, string, endl etc. are used
// https://stackoverflow.com/questions/3943352/where-to-put-include-statements-header-or-source
// https://stackoverflow.com/questions/16821763/where-should-i-include-header-files-in-the-cpp-or-in-the-h-file
// https://stackoverflow.com/questions/2679373/include-headers-in-header-file

// Structure and enum definitions
// Copyright (c) 2019 Warren Toomey, GPL3

// AST node types. The first few line up
// with the related tokens
enum {
    A_GT = 1, A_LT, A_GE, A_LE, A_NEQ, A_EQ,
    A_LAND, A_LOR,
    A_UMINUS,
    A_INTLIT,
    A_IDENT,
    A_FUNC
};

// Primitive types
enum {
    P_INT, P_VOID
};

// Structural types
enum {
    S_VAR, S_FUNC
};

// Abstract Syntax Tree structure
struct ASTnode {
    int op;			// "Operation" to be performed on this tree
    struct ASTnode *left;		// Left and right child trees
    struct ASTnode *right;      // 若为 unary，则只有左子树。
    union {
        int intvalue;		// For A_INTLIT, the integer value
                        	// For A_IDENT, the symbol slot number
                            // For A_FUNC, the symbol slot number
    } v;
};

// https://stackoverflow.com/questions/612328/difference-between-struct-and-typedef-struct-in-c
// https://stackoverflow.com/questions/31269728/string-in-struct
// https://softwareengineering.stackexchange.com/questions/306774/how-to-create-constructors-for-structures-in-c
struct symbol {
    std::string name;
    int type;
    int stype;

    // 构造函数 用以存入新的 symbol
    symbol(std::string n, int t, int s) : name(n), type(t), stype(s) {}

    // 重载小于运算符 提供给 map
    // error: no match for 'operator<' (operand types are 'const symbol' and 'const symbol')
    // https://stackoverflow.com/questions/41911931/operator-overloading-of-c-stl-map-with-custom-classes
    bool operator<(const symbol& other) const {
        if (name < other.name)
            return name < other.name;
        if (type < other.type)
            return type < other.type;
        return stype < other.stype;
    }
};

// error: no newline at end of file [-Werror,-Wnewline-eof]
// https://stackoverflow.com/questions/5813311/whats-the-significance-of-the-no-newline-at-end-of-file-log
