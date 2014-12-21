# Very simple makefile at the moment.
# Server Makefile for Pinkie Project
CC=g++

CFLAGS= -c -Wall

all: pink

pink: main.o pink.o
	$(CC) main.o pink.o -o pinkie

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

pink.o: pink.cpp
	$(CC) $(CFLAGS) pink.cpp

clean:
	rm -rf *.o pinkie 
