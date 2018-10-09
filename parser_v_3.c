/**@@<parser.c>::**/

#include <stdlib.h>
#include <stdio.h>
#include <tokens.h>
#include <parser.h>

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

T_entry:

F_entry:

	switch(lookahead){
	   case ID:
		match(ID); assgn();
		break;
	   case NUM:
		match(NUM);
		break;
	   default:
		match('('); E(); match(')');
	} 

	if ( lookahead == '*' || lookahead == '/' ) {
		int otimes = lookahead;
		match(otimes);
		goto F_entry;
	}

	if ( lookahead == '+' || lookahead == '-' ) {
		int oplus = lookahead;
		match(otimes);
		goto T_entry;
	}

 }

void F(void)
{	
	switch(lookahead){
	   case ID:
		match(ID); assgn();
		break;
	   case NUM:
		match(NUM);
		break;
	   default:
		match('('); E(); match(')');
	} 
}

void T(void)
{
	if ( lookahead == '*' || lookahead == '/' ) {
		int otimes = lookahead;
		match(otimes);
		goto F_entry;
	}
}

extern char NUM_postfix[];
/*
 * assgn ->  = E
 *         | <>
 */
void assgn(void)
{
	if (lookahead == '=') {
		match('='); E();
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
