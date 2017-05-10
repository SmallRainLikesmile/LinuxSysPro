DIR_LIB = ./lib
DIR_SRC = ./memallot
DIR_OBJ = ./obj
DIR_BIN = ./bin
DIR_INC = ./include

SRC = $(wildcard ${DIR_SRC}/*.c ${DIR_LIB}/*.c)
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC}))

TARGET = $(basename $(notdir $(wildcard ${DIR_SRC}/*.c)))

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc
CFLAGS = -g -Wall -I${DIR_INC}

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ) -o $@


${DIR_OBJ}/%.o:${DIR_LIB}/%.c
	$(CC) $(CFLAGS) -c $< -o $@

${DIR_OBJ}/%.o:${DIR_SRC}/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm ${DIR_OBJ}/*.o -rf
