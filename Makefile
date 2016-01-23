CFLAGS = -Wall -g
mylibdir = ../my-lib

all:
	gcc $(CFLAGS) -c -fPIC -iquote$(mylibdir) mysort.c -lmylib
	gcc -shared -L$(mylibdir) -Wl,-rpath,$(mylibdir) -o libmysort.so mysort.o -lmylib


