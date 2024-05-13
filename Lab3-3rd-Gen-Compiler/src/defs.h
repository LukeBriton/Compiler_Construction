#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structure and enum definitions
// Copyright (c) 2019 Warren Toomey, GPL3

// AST node types. The first few line up
// with the related tokens
enum {
    A_GT = 1, A_LT, A_GE, A_LE, A_NEQ, A_EQ,
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