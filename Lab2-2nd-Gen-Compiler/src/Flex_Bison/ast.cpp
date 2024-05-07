#include "defs.h"
#include "declare.h"

// AST tree functions
// Copyright (c) 2019 Warren Toomey, GPL3

// 关于 malloc & free，无所谓，OS 会出手
// https://stackoverflow.com/questions/654754/
// what-really-happens-when-you-dont-free-after-malloc-before-program-termination

// Build and return a generic AST node
struct ASTnode *mkastnode(int op, struct ASTnode *left,
			    struct ASTnode *right, int intvalue) {
    struct ASTnode *n;

    // Malloc a new ASTnode
    n = (struct ASTnode *) malloc(sizeof(struct ASTnode));
    if (n == NULL)
        yyerror("Unable to malloc in mkastnode()");

    // Copy in the field values and return it
    n->op = op;
    n->left = left;
    n->right = right;
    n->v.intvalue = intvalue;
    return (n);
}


// Make an AST leaf node
struct ASTnode *mkastleaf(int op, int intvalue) {
    return (mkastnode(op, NULL, NULL, intvalue));
}

// Make a unary AST node: only one child
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue) {
    return (mkastnode(op, left, NULL, intvalue));
}