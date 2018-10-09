#!/usr/bin/make -f

includedpath=./include/

CFLAGS=-g -I$(includedpath)

objlist=lexer.c main.c parser.c vm.c

exec=mybc

$(exec) : $(objlist) $(CC) -o $@ $^

#gcc -o mybc -i . interface.c lexer.c main.c parser.c vm.c

clean: $(RM) *.o

mostlyclean:clean $(RM) *~

indent: lexer.c main.c parser.c vm.c
