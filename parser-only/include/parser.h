#include <stdio.h>

/* parser components */
void expr(void);
void fact(void);
int assgn(void);
/* lexer to parser interface */
int lookahead;
void match(int expected);
int gettoken(FILE *source_code);
/* main code input/output buffer declaration */
FILE *source_code;
FILE *object_code;

/**   Semantic actions are temporarilly placed here:  **/
void var_operation(char *, int);
void rvalue( double );
int SymTab_lookup(char *var_name);
int SymTab_insert(char *var_name);
void negated(void);
void numoperation(int op);