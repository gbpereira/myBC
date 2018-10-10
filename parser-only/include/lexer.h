/**lexer.h**/
#include <stdio.h>
#define MAXIDLEN 63

char lexeme[MAXIDLEN+1];

int isEE(int, int, FILE *);

double acc ;
double acc;
#define STACKSIZE   128
double stack[STACKSIZE];
#define SYMTABSIZE 1024
char SymTab[SYMTABSIZE][MAXIDLEN+1];
double SymTab_memory[SYMTABSIZE];
int SymTab_nextentry ;
