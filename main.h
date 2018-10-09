/* The initial symbol is abstracted as the following
 * procedure: */
#include <stdio.h>
#pragma once

/*extern*/	FILE *source_code;

void mybc(void);
/*/*extern*/ int lookahead;	
int gettoken(FILE *source_code);

