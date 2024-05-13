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
    
    // n = (struct ASTnode *) malloc(sizeof(struct ASTnode));
    // error: use of old-style cast [-Werror,-Wold-style-cast]
    // https://stackoverflow.com/questions/5249418/warning-use-of-old-style-cast-in-g
    // https://stackoverflow.com/questions/332030/when-should-static-cast-dynamic-cast-const-cast-and-reinterpret-cast-be-used
    // https://stackoverflow.com/questions/19004890/how-should-i-cast-the-result-of-malloc-in-c
    // I would prefer to use static_cast, as what you are doing is converting a void* to
    // a pointer to some other object type, which is well defined in C++.
    n = static_cast<struct ASTnode *>(malloc(sizeof(struct ASTnode)));
    
    // if (n == NULL)
    if (n == nullptr)
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
    // return (mkastnode(op, NULL, NULL, intvalue));
    // error: zero as null pointer constant [-Werror,-Wzero-as-null-pointer-constant]
    // /usr/lib64/clang/14.0.5/include/stddef.h:84:18: note: expanded from macro 'NULL'
    // #    define NULL __null
    // https://stackoverflow.com/questions/13091804/whats-better-to-use-in-c11-zero-or-null
    // Q: But in modern C++ implementations NULL is defined as nullptr, isn't it?
    // Then why explicit nullptr is better than NULL? Or maybe this answer is simply outdated?
    // 其余注释见 mkastunary
    return (mkastnode(op, nullptr, nullptr, intvalue));
}

// Make a unary AST node: only one child
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue) {
    // return (mkastnode(op, left, NULL, intvalue));
    // https://stackoverflow.com/questions/20509734/null-vs-nullptr-why-was-it-replaced
    // https://stackoverflow.com/questions/1282295/what-is-the-nullptr-keyword-and-why-is-it-better-than-null
    // https://stackoverflow.com/questions/9003425/is-it-safe-to-define-null-nullptr
    // You shouldn't have seen that, the standard library defines it in <cstddef> (and <stddef.h>).
    // And, IIRC, according to the standard, redefining names defined by standard header files results in undefined behaviour.
    // So from a purely standardese viewpoint, you shouldn't do that.
    return (mkastnode(op, left, nullptr, intvalue));
}

// error: no newline at end of file [-Werror,-Wnewline-eof]
// https://stackoverflow.com/questions/5813311/whats-the-significance-of-the-no-newline-at-end-of-file-log
