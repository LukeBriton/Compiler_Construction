/*
 * Declarations
 *
 * 基于： acwj/07_Comparisons
 * flex & bison Example 3-1.
 * Calculator that builds an AST: header fb3-1.h
 * Example 3-5.
 * Advanced calculator header fb3-2.h
 */
#include <string>


/* interface to the lexer & parser */
extern int yylex(void);
extern int yyparse(void);
extern int yylineno; /* from lexer */
extern FILE *yyin;  // 声明yyin
void yyerror(const char *s, ...);

// ast.cpp
struct ASTnode *mkastnode(int op, struct ASTnode *left,
			  struct ASTnode *right, int intvalue);
struct ASTnode *mkastleaf(int op, int intvalue);
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue);

/* Code Generation */
// gen.cpp
void genAST(struct ASTnode *n);
void genpreamble();
void genfuncpreamble(const char* name, int type);
void genmainpreamble();
void genfuncpostamble();

// cg.cpp
void freeall_registers(void);
void cgpreamble();

void cgadd(void);
void cgsub(void);
void cgmul(void);
void cgdiv(void);

void cgand(void);
void cgor(void);
void cgxor(void);

void cgmod(void);

void cggt(void);
void cglt(void);
void cgge(void);
void cgle(void);
void cgneq(void);
void cgeq(void);

void cgland(void);
void cglor(void);

void cgneg(void);
void cglnot(void);
void cgnot(void);

void cgprintln_int(int r);
void cgfuncpreamble(const char* name, int type);
void cgmainpreamble(void);
void cgfuncpostamble(void);
void cgfunccall(int value);

void cgloadint(int value);
void cgloadlocal(char *identifier);
void cgstorlocal(int r, char *identifier);

// stmt.cpp
void println_int_statement(struct ASTnode *exp);
void var_declaration(const char* name);
void para_declaration(const char* name, int para_num);
void assignment_statement(const char* name, struct ASTnode *exp);
void return_statement(struct ASTnode *exp, int scope);
void arg_pass(struct ASTnode *exp);
int get_arg_num(void);
void arglist_buf(int arg_num);
void arglist_output(void);
void void_func_call(const char* name);
void func_call(const char* name);

// symtab.cpp
int findlocal(const char* name);
int addlocal(const char* name);
int addpara(const char* name, int para_num);
void clearlocal(void);
int findfunc(const char* name);
int functype(int value);
std::string funcname(int value);
int addfunc(const char* name, int type);

// error: no newline at end of file [-Werror,-Wnewline-eof]
// https://stackoverflow.com/questions/5813311/whats-the-significance-of-the-no-newline-at-end-of-file-log
