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
  T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT
};

/* undefined reference to `Line', `Infile', `Putback'
extern int     Line;
extern int     Putback;
extern FILE    *Infile;
*/
int     Line;
int     Putback;
FILE    *Infile;

static int next();
static int skip();
int scan(struct token*);
static int scanint(int c);
static int chrpos(const char*, int);
static void scanfile();
static void init();
static void putback(int);

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

  // Determine the token based on
  // the input character
  switch (c) {
  case EOF:
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
  
  init();
  
  Infile = fopen(argv[1], "r");
  
  scanfile();
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