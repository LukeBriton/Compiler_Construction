#include "defs.h"
#include "declare.h"

// Generic code generator
// Copyright (c) 2019 Warren Toomey, GPL3

using std::cout;
using std::endl;

// Given an AST, generate assembly code recursively.
// Return the register id with the tree's final value
void genAST(struct ASTnode *n) {

    // Get the left and right sub-tree values

    int offset = 0; // 给存放到栈内的中间变量分配的空间

    // 此处是从显式用栈的版本改造而来
    // 当初的代码是：
    // Token token1 = stack.top();stack.pop();
    // Token token2 = stack.top();stack.pop();
    // 则 n->left 对应 token2，n->right 对应 token1。

    // 尚不能合并，有待改进。
    if (n->left)
        genAST(n->left);
    if (n->right)
        genAST(n->right);
    
    if (n->left)
    {
        switch (n->left->op) {
        case A_INTLIT:
            cout<<"li $t1, "<<n->left->v.intvalue<<endl;
            break;
        case A_IDENT:
            cout<<"lw $t1, "<<-4*n->left->v.intvalue<<"($fp)"<<endl;
            break;
        default:
            offset += 4;
            cout<<"lw $t1, 0($sp)"<<endl;
        }
    }
    if (n->right)
    {
        switch (n->right->op) {
        case A_INTLIT:
            cout<<"li $t0, "<<n->right->v.intvalue<<endl;
            break;
        case A_IDENT:
            cout<<"lw $t0, "<<-4*n->right->v.intvalue<<"($fp)"<<endl;
            break;
        default:
            offset += 4;
            if(offset == 4)
                cout<<"lw $t0, 0($sp)"<<endl;
            else if(offset == 8)
                cout<<"lw $t0, 4($sp)"<<endl;
        }
    }

    switch (n->op) {
    case '+':
        cgadd();
        break;
    case '-':
        cgsub();
        break;
    case '*':
        cgmul();
        break;
    case '/':
        cgdiv();
        break;
    case '&':
        cgand();
        break;
    case '|':
        cgor();
        break;
    case '^':
        cgxor();
        break;
    case '%':
        cgmod();
        break;
    //CMP
    //LGTE
    case A_GT:
        cggt();
        break;
    case A_LT:
        cglt();
        break;
    case A_GE:
        cgge();
        break;
    case A_LE:
        cgle();
        break;
    //EQN
    case A_NEQ:
        cgneq();
        break;
    case A_EQ:
        cgeq();
        break;
    case A_INTLIT:
        return;
    case A_IDENT:
        return;
    default:
        yyerror("Unknown AST operator");
    }

    if(offset)
        cout<<"addiu $sp, $sp, "<<offset<<endl;
    
    // 中间变量入栈
    /*
     * Despite its name, add immediate unsigned (addiu) is used
     * to add constants to signed integers when we don't care about
     * overflow. MIPS has no subtract immediate instruction, and
     * negative numbers need sign extension, so the MIPS architects 
     * decided to sign-extend the immediate field.
     */
    cout<<"addiu $sp, $sp, -4"<<endl;
    cout<<"sw $t2, 0($sp)"<<endl;
}

void genpreamble() {
    cgpreamble();
}