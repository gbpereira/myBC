#include <ctype.h>
#include <stdio.h>
#include "tokens.h"
#include "lexer.h"

void skipspaces(FILE * tape)
{
	int head;
	while( isspace(head = getc(tape))){
		if (head == '\n'){
			return;
		}
	}
	ungetc(head, tape);
}
/*
 * ID = [A-Za-z][_A-Za-z0-9]*
 */
char lexeme[MAXIDLEN+1];
token_t isID(FILE *tape)
{
	lexeme[0] = getc(tape);
	if (isalpha(lexeme[0])) {
		int i  = 1;
		while(
		  isalnum(lexeme[i] = getc(tape))
		  || lexeme[i] == '_'
		);
		ungetc(lexeme[i], tape);
		lexeme[i] = 0;
		return ID;
	}
	ungetc(lexeme[0], tape);
	return 0;
}
/*
 * NUM = [1-9][0-9]* | 0
 */
token_t isNUM(FILE *tape)
{
	int token = 0;
	int i;
	if (isdigit(lexeme[0] = getc(tape))) {
		if (lexeme[0] == '0') {
			i = 1;
		}
		else {
			for (i = 1; isdigit(lexeme[i] = getc(tape)); i++) {
				ungetc(lexeme[i], tape);
			}
			token = UINT;
			if (lexeme[i] == '.'){
			token = FLTP;
			i++;
			while (isdigit(lexeme[i] = getc(tape)))	i++;
			ungetc(lexeme[i], tape);
			}
			else {
				ungetc(lexeme[i], tape);
			}
		}
	}
	else if (lexeme[0] == '.') {
		if (isdigit(lexeme[1]) == getc(tape)) {
			int i = 2;
			token = FLTP;
			while (isdigit(lexeme[i] = getc(tape)))	i++;
			ungetc(lexeme[i], tape);
		}
		else {
			ungetc(lexeme[1], tape);
			ungetc(lexeme[0], tape);
		}
	}
	if (token) {
		i = isEE(i, tape);
		lexeme[i] = 0;
		return token;
	}

	/* epsilon transition is simulated here: */
	ungetc(lexeme[0], tape);
	return 0;
};

token_t gettoken(FILE *tape)
{
	int token;
	skipspaces(tape);
	if ( token = isID(tape) ) return token;
	if ( token = isNUM(tape) ) return token;
	return getc(tape);
};

int isEE(int i, FILE *file)
{
	return 1;
}
