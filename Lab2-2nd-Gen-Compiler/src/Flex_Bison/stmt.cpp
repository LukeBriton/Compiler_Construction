#include "defs.h"
#include "declare.h"

// Parsing of statements
// Copyright (c) 2019 Warren Toomey, GPL3

using std::cout;
using std::endl;

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
    struct ASTnode *tree;
    int reg;

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

void return_statement(struct ASTnode *exp)
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
    cout<<"move $v1, $v0"<<endl;
    cout<<"li $v0, 10"<<endl;
    cout<<"syscall"<<endl;
}