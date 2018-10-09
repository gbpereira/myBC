/**@<parser.c>::**/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "tokens.h"
#include "vm.h"
// #include <interface.h>
#include "parser.h"
#include "keywords.h"

enum {RVALUE = 0, LVALUE};

/*-----------------------------------
EBNF syntax:
	
mybc-> { cmd }  cmdquot


-------------------------------------------*/
int cmdquit(void);
void cmd(void);

void boot(void){lookahead = gettoken(source_code);}

void
mybc (void)
{
	/*#1*/boot();/**/
	while (! cmdquit() ){
		cmd();
	}	
}

/*-----------------------------------
	cmd -> {expr } cmdend
	
	cmdend -> ; | \n
-------------------------------------------*/
int cmdquit(void){
	switch(lookahead) {
	case QUIT:
	case EXIT:
	case LOGOUT:
	case BYE:
	case EOF:
		match(lookahead);
		return 1;
	}
	return 0;

}

int cmdend(void){
	switch(lookahead){
	case ';': case '\n':
		match(lookahead);
		return 1;	
	}
	return 0;
}

void
cmd(void)
{
	if (! cmdend()) {
		expr();
		/**/printf("%lg\n",acc);/**/
		_getche();
		switch(lookahead){
		case ';':
			match(';');
			break;
		default:
			match('\n');
		}
	}	
}
/*-----------------------------------

CMDQUIT = QUIT | EXIT | LOGOUT|BYE|QOF

-------------------------------------------*/

char *keywords[] = {
	"quit",
	"exit",
	"logout",
	"bye",
};
/*
enum{
	QUIT =      20148,
	EXIT,
	LOGOUT,
	BYE,				
};
*/
/* LL(1) recursive parser
 *  
 *                                   /---<---(+)---<----\
 *                                   |                              |
 *                                   |  /--<--(*)--<--\  |  
 *                                   |  |                       |  |
 *expr -->--['+''-']----------- fact  ---------->---
 *

fact -> ID | UINT | FLT | (expr)

mybc -> expr $


 */


void expr(void)
{
    /**/int otimes = 0, oplus = 0, isnegate = 0;/**/

    /** ['+''-'] **/

    switch(lookahead){
    case'+':
        match('+');
        break;
    case'-':
        /**1**/isnegate = '-';/**/
        match('-');
    }

T_entry:

F_entry:

	fact();

	/*1'*/
	if (isnegate) {
        	negate();
	        isnegate = 0;
	}
	/**/
	if (otimes) {
	        numoperation(otimes);
        	otimes = 0;
	}
	/**/
	if (oplus) {
        	numoperation(oplus);
		oplus = 0;
	}

	if ( lookahead == '*' || lookahead == '/' ) {
		/**/
		otimes = lookahead;
		stack[++stack_top] = acc;
		/**/
		match(otimes);
	        goto F_entry;
	} 

	if ( lookahead == '+' || lookahead == '-' ) {
		oplus = lookahead;
		match(oplus);
        	goto T_entry;
	} 

}

void fact(void)
{
    /**/int var_access;/**/
    /**/char var_name[MAXIDLEN];/**/
	switch(lookahead){
    case ID:
        /**/strcpy(var_name,lexeme);/**/
		match(ID); 
		/**/var_access=assgn();/**/
        /**/var_operation(var_name,var_access);/**/
		break;
	case UINT:
	case FLTP:
        /**/rvalue(atof(lexeme));/**/
		match(lookahead);
		break;
	default:
		match('('); expr(); match(')');
	}
}
/*
 * assgn ->  = expr
 *         | <>
 */
int assgn(void)
{
	if (lookahead == '=') {
		match('='); expr();
		return RVALUE;
	} else {
		return LVALUE;
	}

}

void match(int expected_token)
{
	if (expected_token == lookahead) {
		lookahead = gettoken(source_code);
	}
	else {
		fprintf(stderr,
			"token mismatch... exiting\n");
		exit(-2);
	}
}

