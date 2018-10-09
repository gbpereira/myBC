#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "main.h"

///*extern*/
FILE *source_code;

/*extern*/ double acc;

int 
main(int argc, const char *argv[])
{
	source_code = stdin;

	if(argc > 1){
		source_code = fopen(argv[1], "r");
		mybc();
	}
	return 0;
}
