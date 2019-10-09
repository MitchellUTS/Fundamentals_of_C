#makefile for producing main.out

ims.out : main.o item.o date.o database.o filter.o cryptography.o compression.o
	gcc -Wall -ansi -lm -o ims.out main.o item.o date.o database.o filter.o cryptography.o compression.o  

main.o : main.c core.h
	gcc -Wall -ansi -lm -c -o main.o main.c  

item.o : item.c core.h
	gcc -Wall -ansi -lm -c -o item.o item.c  

date.o : date.c core.h
	gcc -Wall -ansi -lm -c -o date.o date.c
	
database.o : database.c core.h
	gcc -Wall -ansi -lm -c -o database.o database.c

filter.o : filter.c core.h
	gcc -Wall -ansi -lm -c -o filter.o filter.c

cryptography.o : cryptography.c core.h
	gcc -Wall -ansi -lm -c -o cryptography.o cryptography.c

compression.o : compression.c compression.h limits.h
	gcc -Wall -ansi -lm -c -o compression.o compression.c