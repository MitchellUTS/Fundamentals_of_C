CC		= gcc
CFLAGS 	= -Wall -Werror -ansi -lm

OBJ = $(wildcard src/*.c)

EXEC_NAME = inventoryManager
TARGET_NAME = $(EXEC_NAME).out

 all: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET_NAME) $(OBJ)

# ifeq ($(OS), Windows_NT)
# 	DEL_CMD = del

# 	TARGET_NAME = $(EXEC_NAME).exe
# else
# 	DEL_CMD = rm

# 	UNAME = $(shell uname -s)
# 	ifeq ($(UNAME), Linux)
# 		TARGET_NAME = $(EXEC_NAME)
# 	else ifeq ($(UNAME), Darwin)
# 		TARGET_NAME = $(EXEC_NAME).app
# 	endif

# endif

# all: $(OBJ)
# 	$(CC) $(CFLAGS) -o bin/$(TARGET_NAME) $(OBJ)
# 	ECHO "The compiled result is found at bin/$(TARGET_NAME)"

# .PHONY: clean
# clean:
# 	$(DEL_CMD) bin/$(TARGET_NAME)

# OLD MAKE FILE

# #makefile for producing main.out

# ims.exe : main.c main.h core.h cryptography.c compression.c cryptography.h compression.h
# 	gcc -Wall -Werror -ansi -lm -o ims.exe main.c compression.c cryptography.c

# ims.out : main.o cryptography.o compression.o item.o date.o database.o filter.o
# 	gcc -Wall -ansi -lm -o ims.out main.o cryptography.o compression.o item.o date.o database.o filter.o 

# main.o : main.c core.h
# 	gcc -Wall -ansi -lm -c -o main.o main.c  

# # item.o : item.c core.h
# # 	gcc -Wall -ansi -lm -c -o item.o item.c  

# # date.o : date.c core.h
# # 	gcc -Wall -ansi -lm -c -o date.o date.c
	
# # database.o : database.c core.h
# # 	gcc -Wall -ansi -lm -c -o database.o database.c

# # filter.o : filter.c core.h
# # 	gcc -Wall -ansi -lm -c -o filter.o filter.c

# cryptography.o : cryptography.c core.h
# 	gcc -Wall -ansi -lm -c -o cryptography.o cryptography.c

# compression.o : compression.c compression.h
# 	gcc -Wall -ansi -lm -c -o compression.o compression.c