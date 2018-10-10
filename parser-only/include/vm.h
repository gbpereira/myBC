#include "lexer.h"
int SymTab_lookup(char *var_name);
int SymTab_insert(char *var_name);
void var_operation(char *, int);
void rvalue( double );
void rvalue(double val);
void numoperation(int op);
void negate(void);
int stack_top;

