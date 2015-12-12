CFLAGS = -Wall -g
mylibdir = ../my-lib

all:
	gcc $(CFLAGS) -c -L$(mylibdir) -fPIC -Wl,-rpath,$(mylibdir) -iquote$(mylibdir) mysort.c -lmylib
	gcc -shared -o libmysort.so mysort.o
clean:
	rm -f mergesort
