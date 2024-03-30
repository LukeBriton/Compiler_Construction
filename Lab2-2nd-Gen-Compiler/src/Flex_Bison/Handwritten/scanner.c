/*
* Handwritten version of scanner for calculator
*/
# include <stdio.h>
# include "parser.tab.h"
FILE *yyin;
static int seeneof = 0;
int
yylex(void)
{
	if(!yyin) yyin = stdin;
	if(seeneof) return 0; /* saw EOF last time */
	while(1) {
		int c = getc(yyin);

		if(isdigit(c)) {
			int i = c - '0';
			
			while(isdigit(c = getc(yyin)))
				i = (10*i) + c-'0';
			yylval = i;
			if(c == EOF) seeneof = 1;
			else ungetc(c, yyin);
			return NUMBER;
		}
		
		switch(c) {
			case '+': return ADD; case '-': return SUB;
			case '*': return MUL; case '|': return ABS;
			case '(': return OP; case ')': return CP;
			case '\n': return EOL;
			case ' ': case '\t': break; /* ignore these */
			case EOF: return 0; /* standard end-of-file token */
				
			case '/': c = getc(yyin);
			if(c == '/') { /* it's a comment */
				while((c = getc(yyin)) != '\n')
					if(c == EOF) return 0; /* EOF in comment line */
				break;
			}
			if(c == EOF) seeneof = 1; /* it's division */
			else ungetc(c, yyin);
			return DIV;
			default: yyerror("Mystery character %c\n", c); break;
		}
	}
}