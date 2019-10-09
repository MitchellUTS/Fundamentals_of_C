#makefile for producing main.out

CC = gcc
CFLAGS = -Wall -Werror -ansi -lm

ims.out : main.o item.o date.o database.o filter.o cryptography.o compression.o
	$(CC) $(CFLAGS) -o ims.out main.o item.o date.o database.o filter.o cryptography.o compression.o  

main.o : main.c core.h
	$(CC) $(CFLAGS) -c -o main.o main.c  

item.o : item.c core.h
	$(CC) $(CFLAGS) -c -o item.o item.c  

date.o : date.c core.h
	$(CC) $(CFLAGS) -c -o date.o date.c
	
database.o : database.c core.h
	$(CC) $(CFLAGS) -c -o database.o database.c

filter.o : filter.c core.h
	$(CC) $(CFLAGS) -c -o filter.o filter.c

cryptography.o : cryptography.c core.h
	$(CC) $(CFLAGS) -c -o cryptography.o cryptography.c

compression.o : compression.c compression.h limits.h
	$(CC) $(CFLAGS) -c -o compression.o compression.c