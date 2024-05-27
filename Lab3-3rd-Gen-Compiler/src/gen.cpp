#include "defs.h"
#include "declare.h"

// Generic code generator
// Copyright (c) 2019 Warren Toomey, GPL3

using std::cout;
using std::endl;

// Given an AST, generate assembly code recursively.
void genAST(struct ASTnode *n) {

    int offset = 0; // 给存放到栈内的中间变量分配的空间

    // Get the left and right sub-tree values

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

    switch (n->op)
    {
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

        // Logical
        case A_LAND:
            cgland();
            break;
        case A_LOR:
            cglor();
            break;

        // Unary
        case A_UMINUS:
            cgneg();
            break;
        case '!':
            cglnot();
            break;
        case '~':
            cgnot();
            break;

        // 函数确实需要跟其他 op 一样将结果入栈
        case A_FUNC:
            // 总是有种把参数列表当作函数子树的想法，
            // 而实际上函数是叶子，offset 一直为 0
            // 所以不用担心“子树”位于栈中，
            // 应该能够用 cgfunccall 把入栈的操作处理好。
            arglist_output();
            cgfunccall(n->v.intvalue);
            // break; 
            // 用 break 的话，就不要在 cgfuncall 中 addiu $sp, $sp, -4，
            // 但是需要留着 cgfuncall 里存入 $t2 的代码
            return;
            // 之前误用成 return; 导致下方代码无法执行。 // 但怎么现在来看，还是得用 return;
            // 现在不用纠结了，用 return 就行。
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

void genfuncpreamble(const char* name, int type) {
    cgfuncpreamble(name, type);
}

void genmainpreamble() {
    cgmainpreamble();
}

void genfuncpostamble() {
    cgfuncpostamble();
}
// error: no newline at end of file [-Werror,-Wnewline-eof]
// https://stackoverflow.com/questions/5813311/whats-the-significance-of-the-no-newline-at-end-of-file-log
