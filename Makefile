CC=gcc
CFLAGS=-ggdb -Wall -Werror
all: sample-main.o records.o
	$(CC) $(CFLAGS) $^ -o sample-main

test: tests.o records.o
	$(CC) $(CFLAGS) $^ -o ./test
	-./test

setget: setget.o records.o
	$(CC) $(CFLAG) $^ -o ./setget

%o:%c
	$(CC) $(CFLAGS) $< 

	
records.o: records.c records.h
records.o: records.h
sample-main.o: sample-main.c records.h
