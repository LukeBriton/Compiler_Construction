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
    A_IDENT
};

// Abstract Syntax Tree structure
struct ASTnode {
    int op;			// "Operation" to be performed on this tree
    struct ASTnode *left;		// Left and right child trees
    struct ASTnode *right;
    union {
        int intvalue;		// For A_INTLIT, the integer value
        int id;			// For A_IDENT, the symbol slot number
    } v;
};

// error: no newline at end of file [-Werror,-Wnewline-eof]
// https://stackoverflow.com/questions/5813311/whats-the-significance-of-the-no-newline-at-end-of-file-log
