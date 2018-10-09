/**lexer.h**/
#include <stdio.h>
#define MAXIDLEN 63

/*extern*/ char lexeme[MAXIDLEN+1];

int isEE(int, FILE *);

/*extern*/ double acc ;
double acc;
#define STACKSIZE   128
/*extern*/ double stack[STACKSIZE];
///*extern*/ int stack_top = -1;
#define SYMTABSIZE 1024
/*extern*/ char SymTab[SYMTABSIZE][MAXIDLEN+1];
/*extern*/ double SymTab_memory[SYMTABSIZE];
/*extern*/ int SymTab_nextentry ;
