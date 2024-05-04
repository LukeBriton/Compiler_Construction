/*
 * Functions
 *
 * 基于：
 * flex & bison Example 3-4.
 * C routines for AST calculator
 * Example 3-8.
 * Advanced calculator helper functions fb3-2func.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "Declare.h"

/* symbol table */
struct symbol symtab[NHASH];

/* hash a symbol */
static unsigned symhash(char *sym)
{
    unsigned int hash = 0;
    unsigned c;
    /* 有没有更高效的？ */
    /* 以及，如何比较散列函数的“效率”？*/
    /* https://www.cs.mcgill.ca/~cs520/2020/slides/7-symbol.pdf */
    while(c = *sym++) hash = hash*9 ^ c;
    return hash;
}

struct symbol *lookup(char* sym)
{
    struct symbol *sp = &symtab[symhash(sym)%NHASH];
    int scount = NHASH; /* how many have we looked at */
    while(--scount >= 0) {
        if(sp->name && !strcmp(sp->name, sym)) { return sp; }

        if(!sp->name) { /* new entry */
            sp->name = strdup(sym);
            sp->value = 0;
            sp->func = NULL;
            sp->syms = NULL;
            return sp;
        }
        if(++sp >= symtab+NHASH) sp = symtab; /* try the next entry */
    }
    yyerror("symbol table overflow\n");
    abort(); /* tried them all, table is full */
}

struct ast *newast(int nodetype, struct ast *l, struct ast *r)
{
    struct ast *a = malloc(sizeof(struct ast));

    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

struct ast *newnum(int num)
{
    struct numval *a = malloc(sizeof(struct numval));

    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'K';
    a->number = num;
    return (struct ast *)a;
}

struct ast *newcmp(int cmptype, struct ast *l, struct ast *r)
{
    struct ast *a = malloc(sizeof(struct ast));
    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = '0' + cmptype;
    a->l = l;
    a->r = r;
    return a;
}

/*
struct ast *newfunc(int functype, struct ast *l)
{
    struct fncall *a = malloc(sizeof(struct fncall));
    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'F';
    a->l = l;
    a->functype = functype;
    return (struct ast *)a;
}
*/

/*
struct ast *newcall(struct symbol *s, struct ast *l)
{
    struct ufncall *a = malloc(sizeof(struct ufncall));
    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'C';
    a->l = l;
    a->s = s;
    return (struct ast *)a;
}
*/

struct ast *newref(struct symbol *s)
{
    struct symref *a = malloc(sizeof(struct symref));
    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'N';
    a->s = s;
    return (struct ast *)a;
}

struct ast *newasgn(struct symbol *s, struct ast *v)
{
    struct symasgn *a = malloc(sizeof(struct symasgn));
    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = '=';
    a->s = s;
    a->v = v;
    return (struct ast *)a;
}

/*
struct ast *newflow(int nodetype, struct ast *cond, struct ast *tl, struct ast *el)
{
    struct flow *a = malloc(sizeof(struct flow));
    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->cond = cond;
    a->tl = tl;
    a->el = el;
    return (struct ast *)a;
}
*/

/* free a tree of ASTs */
void treefree(struct ast *a)
{
    switch(a->nodetype) {
        /* two subtrees */
        case '+':
        case '-':
        case '*':
        case '/':
        case '1': case '2': case '3': case '4': case '5': case '6':
        case 'L':
            treefree(a->r);

        /* one subtree */
        case 'F':// case 'M': case 'C':
            treefree(a->l);

        /* no subtree */
        case 'K': case 'N':
            break;

        case '=':
            free( ((struct symasgn *)a)->v);
        break;

        /* up to three subtrees */
        /*
        case 'I': case 'W':
            free( ((struct flow *)a)->cond);
            if( ((struct flow *)a)->tl) treefree( ((struct flow *)a)->tl);
            if( ((struct flow *)a)->el) treefree( ((struct flow *)a)->el);
            break;
        */

        default:
            printf("internal error: free bad node %c\n", a->nodetype);
    }
    free(a); /* always free the node itself */
}

struct symlist *newsymlist(struct symbol *sym, struct symlist *next)
{
    struct symlist *sl = malloc(sizeof(struct symlist));
    if(!sl) {
        yyerror("out of space");
        exit(0);
    }
    sl->sym = sym;
    sl->next = next;
    return sl;
}

/* free a list of symbols */
void symlistfree(struct symlist *sl)
{
    struct symlist *nsl;
    while(sl) {
        nsl = sl->next;
        free(sl);
        sl = nsl;
    }
}

static int callbuiltin(struct fncall *);
//static int calluser(struct ufncall *);

int eval(struct ast *a)
{
    int v;

    if(!a) {
        yyerror("internal error, null eval");
        return 0;
    }

    switch(a->nodetype) {
    /* constant */
    case 'K': v = ((struct numval *)a)->number; break;

    /* name reference */
    case 'N': v = ((struct symref *)a)->s->value; break;

    /* assignment */
    case '=': v = ((struct symasgn *)a)->s->value =
        eval(((struct symasgn *)a)->v); break;

    /* expressions */
    case '+': v = eval(a->l) + eval(a->r); break;
    case '-': v = eval(a->l) - eval(a->r); break;
    case '*': v = eval(a->l) * eval(a->r); break;
    case '/': v = eval(a->l) / eval(a->r); break;
    case 'M': v = -eval(a->l); break;

    /* comparisons */
    case '1': v = (eval(a->l) > eval(a->r))? 1 : 0; break;
    case '2': v = (eval(a->l) < eval(a->r))? 1 : 0; break;
    case '3': v = (eval(a->l) != eval(a->r))? 1 : 0; break;
    case '4': v = (eval(a->l) == eval(a->r))? 1 : 0; break;
    case '5': v = (eval(a->l) >= eval(a->r))? 1 : 0; break;
    case '6': v = (eval(a->l) <= eval(a->r))? 1 : 0; break;

    /* control flow */
    /* null expressions allowed in the grammar, so check for them */
    
    /* if/then/else */
    /*
    case 'I':
        if( eval( ((struct flow *)a)->cond) != 0) { 
            if( ((struct flow *)a)->tl) {
                v = eval( ((struct flow *)a)->tl);
            } else
                v = 0; // a default value
        } else {
            if( ((struct flow *)a)->el) {
                v = eval(((struct flow *)a)->el);
            } else
                v = 0; // a default value
    }
    break;
    */

    /* while/do */
    /*
    case 'W':
        v = 0.0; // a default value

        if( ((struct flow *)a)->tl) {
            while( eval(((struct flow *)a)->cond) != 0)
                v = eval(((struct flow *)a)->tl);
        }
    break; // value of last statement is value of while/do
    */
   
    /* list of statements */
    case 'L': eval(a->l); v = eval(a->r); break;

    case 'F': v = callbuiltin((struct fncall *)a); break;

    //case 'C': v = calluser((struct ufncall *)a); break;

    default: printf("internal error: bad node %c\n", a->nodetype);
    }
    return v;
}

static int callbuiltin(struct fncall *f)
{
    enum bifs functype = f->functype;
    int v = eval(f->l);
    switch(functype) {
        case B_println_int:
            printf("= %d\n", v);
            return v;
        default:
            yyerror("Unknown built-in function %d", functype);
            return 0;
    }
}

/* define a function */
/*
void dodef(struct symbol *name, struct symlist *syms, struct ast *func)
{
    if(name->syms) symlistfree(name->syms);
    if(name->func) treefree(name->func);
    name->syms = syms;
    name->func = func;
}
*/

/*
static int calluser(struct ufncall *f)
{
    struct symbol *fn = f->s; // function name
    struct symlist *sl; // dummy arguments
    struct ast *args = f->l; // actual arguments
    int *oldval, *newval; // saved arg values
    int v;
    int nargs;
    int i;

    if(!fn->func) {
        yyerror("call to undefined function", fn->name);
        return 0;
    }

    // count the arguments
    sl = fn->syms;
    for(nargs = 0; sl; sl = sl->next)
        nargs++;

    // prepare to save them
    oldval = (int *)malloc(nargs * sizeof(int));
    newval = (int *)malloc(nargs * sizeof(int));
    if(!oldval || !newval) {
        yyerror("Out of space in %s", fn->name); return 0.0;
    }

    // evaluate the arguments
    for(i = 0; i < nargs; i++) {
        if(!args) {
            yyerror("too few args in call to %s", fn->name);
            free(oldval); free(newval);
            return 0.0;
        }
        if(args->nodetype == 'L') { // if this is a list node
            newval[i] = eval(args->l);
            args = args->r;
        } else { // if it's the end of the list
            newval[i] = eval(args);
            args = NULL;
        }
    }

    // save old values of dummies, assign new ones
    sl = fn->syms;
    for(i = 0; i < nargs; i++) {
        struct symbol *s = sl->sym;
        oldval[i] = s->value;
        s->value = newval[i];
        sl = sl->next;
    }
    free(newval);

    // evaluate the function
    v = eval(fn->func);

    // put the real values of the dummies back
    sl = fn->syms;
    for(i = 0; i < nargs; i++) {
        struct symbol *s = sl->sym;
        s->value = oldval[i];
        sl = sl->next;
    }

    free(oldval);
    return v;
}
*/

void yyerror(char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}
int main(int argc, char **argv)
{
    printf("> ");
    return yyparse();
}
