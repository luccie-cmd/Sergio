CC=gcc
CFLAGS=-Wall -Wextra -Wswitch-enum -std=c11 -I../include
LIBS= ../src/cpu.c ../src/insts.c ../src/util.c

build:
	$(CC) $(CFLAGS) -o Sergio ../src/main.c $(LIBS)
	$(CC) $(CFLAGS) -o test ../src/main2.c $(LIBS)