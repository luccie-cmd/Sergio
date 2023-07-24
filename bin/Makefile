CC=gcc
CFLAGS=-Wall -Wextra -Wswitch-enum -std=c11 -I../include

build:
	$(CC) $(CFLAGS) -o Sergio ../src/cpu.c ../src/insts.c ../src/main.c ../src/util.c
	$(CC) $(CFLAGS) -o test ../src/cpu.c ../src/insts.c ../src/main2.c ../src/util.c