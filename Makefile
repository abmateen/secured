#Compiler to use

CC = gcc
CFLAGS=-fPIC -c -Iinclude/ -Llib/

default:secured main

secured: 
	$(CC) $(CFLAGS) src/df.c -o src/df.o
	$(CC) $(CFLAGS) src/pidof.c -o src/pidof.o
	$(CC) $(CFLAGS) src/emailit.c -o src/emailit.o
	$(CC) $(CFLAGS) src/process.c -o src/process.o
	$(CC) -shared -o lib/libsecured.so src/df.o src/pidof.o src/emailit.o src/process.o

main: 
	$(CC) -Iinclude/ -Llib/ src/main.c -o src/secureatcd -lsecured -lpthread
