#makefile for producing main.out

ims.exe : main.c main.h core.h cryptography.c compression.c cryptography.h compression.h
	gcc -Wall -Werror -ansi -lm -o ims.exe main.c compression.c cryptography.c

ims.out : main.o cryptography.o compression.o item.o date.o database.o filter.o
	gcc -Wall -ansi -lm -o ims.out main.o cryptography.o compression.o item.o date.o database.o filter.o 

main.o : main.c core.h
	gcc -Wall -ansi -lm -c -o main.o main.c  

# item.o : item.c core.h
# 	gcc -Wall -ansi -lm -c -o item.o item.c  

# date.o : date.c core.h
# 	gcc -Wall -ansi -lm -c -o date.o date.c
	
# database.o : database.c core.h
# 	gcc -Wall -ansi -lm -c -o database.o database.c

# filter.o : filter.c core.h
# 	gcc -Wall -ansi -lm -c -o filter.o filter.c

cryptography.o : cryptography.c core.h
	gcc -Wall -ansi -lm -c -o cryptography.o cryptography.c

compression.o : compression.c compression.h
	gcc -Wall -ansi -lm -c -o compression.o compression.c