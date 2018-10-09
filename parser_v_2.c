	/**@@<parser.c>::**/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tokens.h>
#include <parser.h>
#include <lexer.h>

/* LL(1) recursive topdown parser 
*
* E ->  T ( oplus T  )
*
* T ->  F ( otimes F )
*
* F -> ID | UINT |  FLT | (  E  )
*
* Simplifying a little further:
*
*/

void E(void) 
{

	/**/int otimes = 0, oplus =0, isnegate  = 0/**/;

	switch(lookahead){
	case '+':
		match('+');
		break;
	case '-':
		isnegate = '-'/*1*/;
		match('-');
		break;
	}

T_entry:

F_entry:

	F();

	/**/
	if(isnegated) {
		negate();
		isnegated = 0;/*1'*/
	}
	if(otimes) {
		numoperation(otimes);
		otimes = 0;/*2'*/
	}
	if(oplus) {
		numoperation(oplus);
		oplus = 0;/*3'*/
	}
	/**/


	if ( lookahead == '*' || lookahead == '/' ) {
		otimes = lookahead;
		match(otimes);/*2*/
		goto F_entry;
	}
	if ( lookahead == '+' || lookahead == '-' ) {
		oplus = lookahead;
		match(otimes);/*3*/
		goto T_entry;
	}
 }

void F(void)
{	
	/**/int var_acess /**/;
	/**/char var_name[MAXIDLEN]/**/;
	switch(lookahead){
	case ID:
		/**/strcpy(var_name, lexeme);/**/;
		match(ID); /*4*/var_acess = /**/ assgn();
		/**/var_operation(var_name,var_access)/**/;
		break;
	case UINT:
	case FLTP:
		//match(FLTP);
		/**/rvalue(atof(lexeme))/**/;
		match(lookahead);
		break;
	default:
		match('('); E(); match(')');
	} 
}

extern char NUM_postfix[];
/*
 * assgn ->  = E
 *         | <>
 */
enum {
	RVALUE = 0, 	/**Id must be  used as RECALL **/
	LVALUE,		 /** otherwise, it is a STORE **/
};

int assgn(void)
{
	if (lookahead == '=') {
		match('=');  E();
	} else {
		;
	}
}

int lookahead;

void match (int expected_token)
{
	if (expected_token == lookahead) {
		lookahead = gettoken(source_code);
	} else {
		fprintf(stderr,
		"token mismatch... exiting\n");
		exit(-2);
	}
}

double acc = 0;
#define STACKSIZE   128
double stack[STACKSIZE];
int stack_top = -1;

#define SYNTABSIZE 1024
char SymTab[SYNTABSIZE][MAXIDLEN+1];
double SymTab_memory[SYNTABSIZE];
int SymTab_nextentry = 0;

void var_operation(char *var_name, int var_acess)
{
	int adress = SymTab_lookup(var_name);
	if(address < 0) {
		SymTab_insert(var_name);
	}
	
	if(var_acess == LVALUE) {
		/**lvalue**/
		SymTab_memory[address] =  acc;
	} else {
		rvalue( SymTab_memory[address];
	}
}

void rvalue(double val)
{
	stack[++stack_top] = acc;
	acc = val;
}

void numoperation(int op)
{
	switch(op){
	case '+':
		acc = stack[stack_top--] + acc;
		break;
	case '-':
		acc = stack[stack_top--] - acc;
		break;
	case '*':
		acc = stack[stack_top--] * acc;
		break;
	case '/':
		acc = stack[stack_top--] / acc;
		break;
	}
}

void SymTab_insert(char *varname)
{
	strcpy(SymTab[SymTab_nextentry],varname);
	SymTab_nextentry++;
}

int SymTab_lookup(char *varname)
{	
	int i;
	for (i = 0; i < SymTab_nextentry); i++)
	{
		if (strcmp(SymTab[i],varname) == 0) {
			return i;
		}
	}
	return -1;
}

void negated(void)
{
	acc *= -1;
}