// 底本 https://github.com/DoctorWkt/acwj
// A Compiler Writing Journey
// 初号机速成单文件杂糅版，代码不具备原创性。

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h> //void exit( int exit_code );
// https://stackoverflow.com/questions/22485822/exit-is-not-working

// Token structure
struct token {
  int token;
  int intvalue;
};

// Tokens
enum {
  T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT
};

// AST node types
enum {
  A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT
};

// Abstract Syntax Tree structure
struct ASTnode {
  int op;                               // "Operation" to be performed on this tree
  struct ASTnode *left;                 // Left and right child trees
  struct ASTnode *right;
  int intvalue;                         // For A_INTLIT, the integer value
};

/* undefined reference to `Line', `Infile', `Putback'...
extern int     Line;
extern int     Putback;
extern FILE    *Infile;
extern_ struct token    Token;
*/
int     Line;
int     Putback;
FILE    *Infile;
struct token    Token;

static int next();
static int skip();
int scan(struct token*);
static int scanint(int c);
static int chrpos(const char*, int);
static void scanfile();
static void init();
static void putback(int);

struct ASTnode *mkastnode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue);
struct ASTnode *mkastleaf(int op, int intvalue);
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue);
int arithop(int tok);
static struct ASTnode *primary(void);
struct ASTnode *binexpr(void);
int interpretAST(struct ASTnode *n);

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
  int c;

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
  default:

    // If it's a digit, scan the
    // literal integer value in
    if (isdigit(c)) {
      t->intvalue = scanint(c);
      t->token = T_INTLIT;
      break;
    }

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

// error: '::main' must return 'int'
// void main(int argc, char *argv[])
int main(int argc, char *argv[]) {
  struct ASTnode *n;
  init();
  
  Infile = fopen(argv[1], "r");
  
  //scanfile();
  scan(&Token);			// Get the first token from the input
  n = binexpr();		// Parse the expression in the file
  printf("%d\n", interpretAST(n));	// Calculate the final result
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
  n->intvalue = intvalue;
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

  // For an INTLIT token, make a leaf AST node for it
  // and scan in the next token. Otherwise, a syntax error
  // for any other token type.
  switch (Token.token) {
    case T_INTLIT:
      n = mkastleaf(A_INTLIT, Token.intvalue);
      scan(&Token);
      return (n);
    default:
      fprintf(stderr, "syntax error on line %d\n", Line);
      exit(1);
  }
}

// Return an AST tree whose root is a binary operator
struct ASTnode *binexpr(void) {
  struct ASTnode *n, *left, *right;
  int nodetype;

  // Get the integer literal on the left.
  // Fetch the next token at the same time.
  left = primary();

  // If no tokens left, return just the left node
  if (Token.token == T_EOF)
    return (left);

  // Convert the token into a node type
  nodetype = arithop(Token.token);

  // Get the next token in
  scan(&Token);

  // Recursively get the right-hand tree
  right = binexpr();

  // Now build a tree with both sub-trees
  n = mkastnode(nodetype, left, right, 0);
  return (n);
}

// List of AST operators
static char *ASTop[] = { "+", "-", "*", "/" };

// Given an AST, interpret the
// operators in it and return
// a final value.
int interpretAST(struct ASTnode *n) {
  int leftval, rightval;

  // Get the left and right sub-tree values
  if (n->left)
    leftval = interpretAST(n->left);
  if (n->right)
    rightval = interpretAST(n->right);

  // Debug: Print what we are about to do
  if (n->op == A_INTLIT)
    printf("int %d\n", n->intvalue);
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
      return (n->intvalue);
    default:
      fprintf(stderr, "Unknown AST operator %d\n", n->op);
      exit(1);
  }
}