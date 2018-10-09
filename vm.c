#include "vm.h"

double acc = 0;
#define STACKSIZE   128
double stack[STACKSIZE];
int stack_top = -1;

#define SYMTABSIZE 1024
char SymTab[SYMTABSIZE][MAXIDLEN+1];
double SymTab_memory[SYMTABSIZE];
int SymTab_nextentry = 0;

enum {
    RVALUE = 0,/** ID must be used as RECALL **/
    LVALUE,    /** otherwise, it is a STORE **/
};

void var_operation(char *var_name, int var_access)
{
    int address = SymTab_lookup(var_name);
    if (address < 0) {
        SymTab_insert(var_name);
    }
    
    if (var_access == LVALUE) {
        /** lvalue **/
        SymTab_memory[address] = acc;
    } else {
        rvalue(SymTab_memory[address]);
    }
}

void rvalue(double val)
{
        stack[++stack_top] = acc;
        acc = val;
}

void numoperation(int op)
{
    switch(op) {
    case'+':
        acc = stack[stack_top--] + acc;
        break;
    case'-':
        acc = stack[stack_top--] - acc;
        break;
    case'*':
        acc = stack[stack_top--] * acc;
        break;
    case'/':
        acc = stack[stack_top--] / acc;
        break;
    }
}

int SymTab_insert(char *varname)
{
    strcpy(SymTab[SymTab_nextentry], varname);
    SymTab_nextentry++;
}

int SymTab_lookup(char *varname)
{
    int i;
    for (i = 0; i < SymTab_nextentry; i++) {
        if (strcmp(SymTab[i], varname) == 0) {
            return i;
        }
    }
    return -1;
}

void negate(void)
{
    acc *= -1;
}

