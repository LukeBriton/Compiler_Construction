// 底本 https://github.com/DoctorWkt/acwj
// A Compiler Writing Journey
// 初号机速成单文件杂糅版，代码不具备原创性。

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h> //void exit( int exit_code );
// https://stackoverflow.com/questions/22485822/exit-is-not-working

#define TEXTLEN         512             // Length of symbols in input
#define NSYMBOLS        1024            // Number of symbol table entries

// Token structure
struct token {
  int token;
  int intvalue;
};

// Tokens
enum {
  T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_SEMI, T_EQUALS,
  T_IDENT,
  // Keywords
  T_PRINT, T_INT
};

// AST node types
enum {
  A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT,
  A_IDENT, A_LVIDENT, A_ASSIGN
};

// Abstract Syntax Tree structure
struct ASTnode {
  int op;                               // "Operation" to be performed on this tree
  struct ASTnode *left;                 // Left and right child trees
  struct ASTnode *right;
  union {
    int intvalue;		                    // For A_INTLIT, the integer value
    int id;			                        // For A_IDENT, the symbol slot number
  } v;
};

// Symbol table structure
struct symtable {
  char *name;                   // Name of a symbol
};

/* undefined reference to `Line', `Infile', `Putback'...
extern int     Line;
extern int     Putback;
extern FILE    *Infile;
extern_ struct token    Token;
extern_ char Text[TEXTLEN + 1];
extern_ struct symtable Gsym[NSYMBOLS];
*/
int     Line;
int     Putback;
FILE    *Infile;
FILE    *Outfile;
struct token    Token;

char Text[TEXTLEN + 1];         // Last identifier scanned
struct symtable Gsym[NSYMBOLS]; // Global symbol table
static int Globs = 0;                   // Position of next free global symbol slot

// Operator precedence for each token
static int OpPrec[] = { 0, 10, 10, 20, 20,    0 };
//                     EOF  +   -   *   /  INTLIT

static int next();
static int skip();
int scan(struct token*);
static int scanint(int c);
static int chrpos(const char*, int);
static int scanident(int c, char *buf, int lim);
static int keyword(char *s);
static void scanfile();
static void init();
static void putback(int);

struct ASTnode *mkastnode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue);
struct ASTnode *mkastleaf(int op, int intvalue);
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue);
int arithop(int tok);
static struct ASTnode *primary(void);
struct ASTnode *binexpr(int);
//int interpretAST(struct ASTnode *n);

static int op_precedence(int tokentype);

static int genAST(struct ASTnode *n, int reg);
//void generatecode(struct ASTnode *n);

void freeall_registers();
static int alloc_register();
static void free_register(int reg);
int cgloadint(int value);
int cgadd(int r1, int r2);
int cgmul(int r1, int r2);
int cgsub(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);
void cgpreamble();
void cgpostamble();
int cgloadglob(char *identifier);
int cgstorglob(int r, char *identifier);
void cgglobsym(char *sym);

void print_statement();
void assignment_statement();
void statements();

void match(int t, char *what);
void semi();
void ident();

// Print out fatal messages
void fatal(char *s);
void fatals(char *s1, char *s2);
void fatald(char *s, int d);
void fatalc(char *s, int c);

void var_declaration();

int findglob(char *s);
static int newglob();
int addglob(char *name);

// Get the next character from the input file.
static int next(void) {
  int c;

  if (Putback) {                // Use the character put
    c = Putback;                // back if there is one
    Putback = 0;
    return c;
  }

  c = fgetc(Infile);            // Read from input file
  if ('\n' == c)
    Line++;                     // Increment line count
  return c;
}

// Skip past input that we don't need to deal with, 
// i.e. whitespace, newlines. Return the first
// character we do need to deal with.
static int skip(void) {
  int c;

  c = next();
  // standard white-space characters
  // space ' ', form feed '\f', line feed '\n',
  // carriage return '\r', horizontal tab '\t',
  // vertical tab '\v'
  // 不知何故是以[ \t\r\n\v\f]的顺序出现在一些地方。
  // 为什么不用带上[\a\b\e]?
  // https://en.cppreference.com/w/c/string/byte/isspace
  // https://en.wikipedia.org/wiki/Escape_sequences_in_C
  while (' ' == c || '\t' == c || '\r' == c || '\n' == c || '\v' == c || '\f' == c) {
    c = next();
  }
  return (c);
}

// Scan and return the next token found in the input.
// Return 1 if token valid, 0 if no tokens left.
int scan(struct token *t) {
  int c, tokentype;

  // Skip whitespace
  c = skip();

  // printf("character %c on line %d\n", c, Line);
  // DEBUG

  // Determine the token based on
  // the input character
  switch (c) {
  case EOF:
    t->token = T_EOF; // Almost forgot
    return (0);
  case '+':
    t->token = T_PLUS;
    break;
  case '-':
    t->token = T_MINUS;
    break;
  case '*':
    t->token = T_STAR;
    break;
  case '/':
    t->token = T_SLASH;
    break;
  case ';':
    t->token = T_SEMI;
    break;
  case '=':
    t->token = T_EQUALS;
    break;
  default:

    // If it's a digit, scan the
    // literal integer value in
    if (isdigit(c)) {
      t->intvalue = scanint(c);
      t->token = T_INTLIT;
      break;
    } else if (isalpha(c) || '_' == c) {
      // Read in a keyword or identifier
      scanident(c, Text, TEXTLEN);

      // If it's a recognised keyword, return that token
      if (tokentype = keyword(Text)) {
        t->token = tokentype;
        break;
      }

      // Not a recognised keyword, so it must be an identifier
      t->token = T_IDENT;
      break;
      // Not a recognised keyword, so an error for now
      //printf("Unrecognised symbol %s on line %d\n", Text, Line);
      //exit(1);
    }
    // The character isn't part of any recognised token, error
    printf("Unrecognised character %c on line %d\n", c, Line);
    exit(1);
  }

  // We found a token
  return (1);
}

// Scan and return an integer literal
// value from the input file.
static int scanint(int c) {
  int k, val = 0;

  // Convert each character into an int value
  // const char p[] = "0123456789";
  while ((k = chrpos("0123456789", c)) >= 0) {
    val = val * 10 + k;
    c = next();
  }

  // We hit a non-integer character, put it back.
  putback(c);
  return val;
}

// Return the position of character c
// in string s, or -1 if c not found
static int chrpos(const char *s, int c) {
  char *p;

  // char *strchr( const char *str, int ch );
  // https://en.cppreference.com/w/c/string/byte/strchr
  p = strchr(s, c);
  return (p ? p - s : -1);
}

// Scan an identifier from the input file and
// store it in buf[]. Return the identifier's length
static int scanident(int c, char *buf, int lim) {
  int i = 0;

  // Allow digits, alpha and underscores
  while (isalpha(c) || isdigit(c) || '_' == c) {
    // Error if we hit the identifier length limit,
    // else append to buf[] and get next character
    if (lim - 1 == i) {
      printf("identifier too long on line %d\n", Line);
      exit(1);
    } else if (i < lim - 1) {
      buf[i++] = c;
    }
    c = next();
  }
  // We hit a non-valid character, put it back.
  // NUL-terminate the buf[] and return the length
  putback(c);
  buf[i] = '\0';
  return (i);
}

// Given a word from the input, return the matching
// keyword token number or 0 if it's not a keyword.
// Switch on the first letter so that we don't have
// to waste time strcmp()ing against all the keywords.
static int keyword(char *s) {
  switch (*s) {
    case 'i':
      if (!strcmp(s, "int"))
        return (T_INT);
      break;
    case 'p':
      if (!strcmp(s, "print"))
        return (T_PRINT);
      break;
  }
  return (0);
}

// error: '::main' must return 'int'
// void main(int argc, char *argv[])
int main(int argc, char *argv[]) {
  struct ASTnode *n;
  init();
  
  Infile = fopen(argv[1], "r");
  Outfile = fopen("out.s", "w");

  //scanfile();
  scan(&Token);			// Get the first token from the input
  /*
  n = binexpr(0);		// Parse the expression in the file
  printf("%d\n", interpretAST(n));	// Calculate the final result
  generatecode(n);
  */
  cgpreamble();
  statements();
  cgpostamble(); 
  fclose(Outfile);
  // printf("Hello there"); // DEBUG
  exit(0);
  // return 0; // 还需要返回值吗
}

// List of printable tokens
// warning: ISO C++ forbids converting
// a string constant to 'char*' [-Wwrite-strings]   
// char *tokstr[] = { "+", "-", "*", "/", "intlit" };
// https://stackoverflow.com/questions/20944784/why-is-conversion-from-string-literal-to-char-valid-in-c-but-invalid-in-c
char *tokstr[] = { "+", "-", "*", "/", "intlit" };

// Loop scanning in all the tokens in the input file.
// Print out details of each token found.
static void scanfile() {
  struct token T;

  while (scan(&T)) {
    printf("Token %s", tokstr[T.token]);
    if (T.token == T_INTLIT)
      printf(", value %d", T.intvalue);
    printf("\n");
  }
}

// Initialise global variables
static void init() {
  Line = 1;
  Putback = '\n';
}

// Put back an unwanted character
static void putback(int c) {
  Putback = c;
}

// Build and return a generic AST node
struct ASTnode *mkastnode(int op, struct ASTnode *left,
                          struct ASTnode *right, int intvalue) {
  struct ASTnode *n;

  // Malloc a new ASTnode
  n = (struct ASTnode *) malloc(sizeof(struct ASTnode));
  if (n == NULL) {
    fprintf(stderr, "Unable to malloc in mkastnode()\n");
    exit(1);
  }
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

// Convert a token into an AST operation.
int arithop(int tok) {
  switch (tok) {
    case T_PLUS:
      return (A_ADD);
    case T_MINUS:
      return (A_SUBTRACT);
    case T_STAR:
      return (A_MULTIPLY);
    case T_SLASH:
      return (A_DIVIDE);
    default:
      fprintf(stderr, "unknown token in arithop() on line %d\n", Line);
      exit(1);
  }
}

// Parse a primary factor and return an
// AST node representing it.
static struct ASTnode *primary(void) {
  struct ASTnode *n;
  int id;

  switch (Token.token) {
    case T_INTLIT:
      // For an INTLIT token, make a leaf AST node for it
      n = mkastleaf(A_INTLIT, Token.intvalue);
      break;

    case T_IDENT:
      // Check that this identifier exists
      id = findglob(Text);
      if (id == -1)
        fatals("Unknown variable", Text);

      // Make a leaf AST node for it
      n = mkastleaf(A_IDENT, id);
      break;

    default:
      // a syntax error for any other token type.
      fprintf(stderr, "syntax error on line %d\n", Line);
      exit(1);
  }

  // Scan in the next token and return the leaf node
  scan(&Token);
  return (n);
}

// Return an AST tree whose root is a binary operator
struct ASTnode *binexpr(int ptp) {
  struct ASTnode *n, *left, *right;
  int tokentype;

  // Get the integer literal on the left.
  // Fetch the next token at the same time.
  left = primary();

  // If no tokens left, return just the left node
  tokentype = Token.token;
  if (Token.token == T_SEMI) // ... 误作 T_EOF，愚蠢
    return (left);

  // While the precedence of this token is
  // more than that of the previous token precedence
  while (op_precedence(tokentype) > ptp) {
    // Fetch in the next integer literal
    scan(&Token);

    // Recursively call binexpr() with the
    // precedence of our token to build a sub-tree
    right = binexpr(OpPrec[tokentype]);

    // Join that sub-tree with ours. Convert the token
    // into an AST operation at the same time.
    left = mkastnode(arithop(tokentype), left, right, 0);

    // Update the details of the current token.
    // If no tokens left, return just the left node
    tokentype = Token.token;
    if (tokentype == T_SEMI)
      return (left);
  }

  // Return the tree we have when the precedence
  // is the same or lower
  return (left);
}

// List of AST operators
static char *ASTop[] = { "+", "-", "*", "/" };

// Given an AST, interpret the
// operators in it and return
// a final value.
/*
int interpretAST(struct ASTnode *n) {
  int leftval, rightval;

  // Get the left and right sub-tree values
  if (n->left)
    leftval = interpretAST(n->left);
  if (n->right)
    rightval = interpretAST(n->right);

  // Debug: Print what we are about to do
  if (n->op == A_INTLIT)
    printf("int %d\n", n->v.intvalue);
  else
    printf("%d %s %d\n", leftval, ASTop[n->op], rightval);

  switch (n->op) {
    case A_ADD:
      return (leftval + rightval);
    case A_SUBTRACT:
      return (leftval - rightval);
    case A_MULTIPLY:
      return (leftval * rightval);
    case A_DIVIDE:
      return (leftval / rightval);
    case A_INTLIT:
      // printf("n->intvalue:%d\n", n->intvalue);
      // DEBUG
      return (n->v.intvalue);
    default:
      fprintf(stderr, "Unknown AST operator %d\n", n->op);
      exit(1);
  }
*/

// Check that we have a binary operator and
// return its precedence.
static int op_precedence(int tokentype) {
  int prec = OpPrec[tokentype];
  if (prec == 0) {
    printf("tokentype of T_SEMI is %d\n", T_SEMI);
    fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokentype);
    //DEBUG
    //exit(1);
  }
  return (prec);
}

// Given an AST, generate
// assembly code recursively
static int genAST(struct ASTnode *n, int reg) {
  int leftreg, rightreg;

  // Get the left and right sub-tree values
  if (n->left) leftreg = genAST(n->left, -1);
  if (n->right) rightreg = genAST(n->right, leftreg);

  switch (n->op) {
    case A_ADD:      return (cgadd(leftreg,rightreg));
    case A_SUBTRACT: return (cgsub(leftreg,rightreg));
    case A_MULTIPLY: return (cgmul(leftreg,rightreg));
    case A_DIVIDE:   return (cgdiv(leftreg,rightreg));
    case A_INTLIT:   return (cgloadint(n->v.intvalue));
    case A_IDENT:    return (cgloadglob(Gsym[n->v.id].name));
    case A_LVIDENT:  return (cgstorglob(reg, Gsym[n->v.id].name));
    case A_ASSIGN:
      // The work has already been done, return the result
      return (rightreg);

    default:
      fprintf(stderr, "Unknown AST operator %d\n", n->op);
      exit(1);
  }
}

/*
void generatecode(struct ASTnode *n) {
  int reg;

  cgpreamble();
  reg= genAST(n);
  cgprintint(reg);      // Print the register with the result as an int
  cgpostamble();
}
*/

// List of available registers
// and their names
static int freereg[4];
static char *reglist[4]= { "%r8", "%r9", "%r10", "%r11" };

// Set all registers as available
void freeall_registers(void)
{
  freereg[0]= freereg[1]= freereg[2]= freereg[3]= 1;
}


// Allocate a free register. Return the number of
// the register. Die if no available registers.
static int alloc_register(void)
{
  for (int i=0; i<4; i++) {
    if (freereg[i]) {
      freereg[i]= 0;
      return(i);
    }
  }
  fprintf(stderr, "Out of registers!\n");
  exit(1);
}


// Return a register to the list of available registers.
// Check to see if it's not already there.
static void free_register(int reg)
{
  if (freereg[reg] != 0) {
    fprintf(stderr, "Error trying to free register %d\n", reg);
    exit(1);
  }
  freereg[reg]= 1;
}


// Print out the assembly preamble
void cgpreamble()
{
  freeall_registers();
  fputs(
	"\t.text\n"
	".LC0:\n"
	"\t.string\t\"%d\\n\"\n"
	"printint:\n"
	"\tpushq\t%rbp\n"
	"\tmovq\t%rsp, %rbp\n"
	"\tsubq\t$16, %rsp\n"
	"\tmovl\t%edi, -4(%rbp)\n"
	"\tmovl\t-4(%rbp), %eax\n"
	"\tmovl\t%eax, %esi\n"
	"\tleaq	.LC0(%rip), %rdi\n"
	"\tmovl	$0, %eax\n"
	"\tcall	printf@PLT\n"
	"\tnop\n"
	"\tleave\n"
	"\tret\n"
	"\n"
	"\t.globl\tmain\n"
	"\t# .type\tmain, @function\n"
	"main:\n"
	"\tpushq\t%rbp\n"
	"\tmovq	%rsp, %rbp\n",
  Outfile);
}

// Print out the assembly postamble
void cgpostamble()
{
  fputs(
	"\tmovl	$0, %eax\n"
	"\tpopq	%rbp\n"
	"\tret\n",
  Outfile);
}

// Load an integer literal value into a register.
// Return the number of the register
int cgloadint(int value) {

  // Get a new register
  int r= alloc_register();

  // Print out the code to initialise it
  fprintf(Outfile, "\tmovq\t$%d, %s\n", value, reglist[r]);
  return(r);
}

// Add two registers together and return
// the number of the register with the result
int cgadd(int r1, int r2) {
  fprintf(Outfile, "\taddq\t%s, %s\n", reglist[r1], reglist[r2]);
  free_register(r1);
  return(r2);
}

// Multiply two registers together and return
// the number of the register with the result
int cgmul(int r1, int r2) {
  fprintf(Outfile, "\timulq\t%s, %s\n", reglist[r1], reglist[r2]);
  free_register(r1);
  return(r2);
}

// Subtract the second register from the first and
// return the number of the register with the result
int cgsub(int r1, int r2) {
  fprintf(Outfile, "\tsubq\t%s, %s\n", reglist[r2], reglist[r1]);
  free_register(r2);
  return(r1);
}

// Divide the first register by the second and
// return the number of the register with the result
int cgdiv(int r1, int r2) {
  fprintf(Outfile, "\tmovq\t%s,%%rax\n", reglist[r1]);
  fprintf(Outfile, "\tcqo\n");
  fprintf(Outfile, "\tidivq\t%s\n", reglist[r2]);
  fprintf(Outfile, "\tmovq\t%%rax,%s\n", reglist[r1]);
  free_register(r2);
  return(r1);
}

// Call printint() with the given register
void cgprintint(int r) {
  fprintf(Outfile, "\tmovq\t%s, %%rdi\n", reglist[r]);
  fprintf(Outfile, "\tcall\tprintint\n");
  free_register(r);
}

// Load a value from a variable into a register.
// Return the number of the register
int cgloadglob(char *identifier) {
  // Get a new register
  int r = alloc_register();

  // Print out the code to initialise it
  fprintf(Outfile, "\tmovq\t%s(\%%rip), %s\n", identifier, reglist[r]);
  return (r);
}

// Store a register's value into a variable
int cgstorglob(int r, char *identifier) {
  fprintf(Outfile, "\tmovq\t%s, %s(\%%rip)\n", reglist[r], identifier);
  return (r);
}

// Generate a global symbol
void cgglobsym(char *sym) {
  fprintf(Outfile, "\t.comm\t%s,8,8\n", sym);
}

// Parse one or more statements
void statements(void) {
  while (1) {
    switch (Token.token) {
    case T_PRINT:
      print_statement();
      break;
    case T_INT:
      var_declaration();
      break;
    case T_IDENT:
      assignment_statement();
      break;
    case T_EOF:
      return;
    default:
      fatald("Syntax error, token", Token.token);
    }
  }
}

void print_statement(void) {
  struct ASTnode *tree;
  int reg;
    
  // Match a 'print' as the first token
  match(T_PRINT, "print");

  // Parse the following expression and
  // generate the assembly code
  tree = binexpr(0);
  reg = genAST(tree, -1);
  cgprintint(reg);
  freeall_registers();

  // Match the following semicolon
  // and stop if we are at EOF
  semi();
}

void assignment_statement(void) {
  struct ASTnode *left, *right, *tree;
  int id;

  // Ensure we have an identifier
  ident();

  // Check it's been defined then make a leaf node for it
  if ((id = findglob(Text)) == -1) {
    fatals("Undeclared variable", Text);
  }
  right = mkastleaf(A_LVIDENT, id);

  // Ensure we have an equals sign
  match(T_EQUALS, "=");

  // Parse the following expression
  left = binexpr(0);

  // Make an assignment AST tree
  tree = mkastnode(A_ASSIGN, left, right, 0);

  // Generate the assembly code for the assignment
  genAST(tree, -1);
  freeall_registers();

  // Match the following semicolon
  semi();
}

// Ensure that the current token is t,
// and fetch the next token. Otherwise
// throw an error 
void match(int t, char *what) {
  if (Token.token == t) {
    scan(&Token);
  } else {
    printf("%s expected on line %d\n", what, Line);
    exit(1);
  }
}

// Match a semicon and fetch the next token
void semi(void) {
  match(T_SEMI, ";");
}
void ident(void) {
  match(T_IDENT, "identifier");
}

// Print out fatal messages
void fatal(char *s) {
  fprintf(stderr, "%s on line %d\n", s, Line); exit(1);
}

void fatals(char *s1, char *s2) {
  fprintf(stderr, "%s:%s on line %d\n", s1, s2, Line); exit(1);
}

void fatald(char *s, int d) {
  fprintf(stderr, "%s:%d on line %d\n", s, d, Line); exit(1);
}

void fatalc(char *s, int c) {
  fprintf(stderr, "%s:%c on line %d\n", s, c, Line); exit(1);
}

// Parse the declaration of a variable
void var_declaration(void) {

  // Ensure we have an 'int' token followed by an identifier
  // and a semicolon. Text now has the identifier's name.
  // Add it as a known identifier
  match(T_INT, "int");
  ident();
  addglob(Text);
  cgglobsym(Text);
  semi();
}

// Determine if the symbol s is in the global symbol table.
// Return its slot position or -1 if not found.
int findglob(char *s) {
  int i;

  for (i = 0; i < Globs; i++) {
    if (*s == *Gsym[i].name && !strcmp(s, Gsym[i].name))
      return (i);
  }
  return (-1);
}

// Get the position of a new global symbol slot, or die
// if we've run out of positions.
static int newglob(void) {
  int p;

  if ((p = Globs++) >= NSYMBOLS)
    fatal("Too many global symbols");
  return (p);
}

// Add a global symbol to the symbol table.
// Return the slot number in the symbol table
int addglob(char *name) {
  int y;

  // If this is already in the symbol table, return the existing slot
  if ((y = findglob(name)) != -1)
    return (y);

  // Otherwise get a new slot, fill it in and
  // return the slot number
  y = newglob();
  Gsym[y].name = strdup(name);
  return (y);
}