OBJ_DIR = obj
SRC_DIR = src
INC_DIR = head

CC = gcc 

all:  $(OBJ_DIR)/main.o  $(OBJ_DIR)/optget.o $(OBJ_DIR)/util.o
		$(CC) $(OBJ_DIR)/main.o $(OBJ_DIR)/optget.o $(OBJ_DIR)/util.o -o test  

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/optget.h
		$(CC) -g -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/util.o: $(SRC_DIR)/util.c
		$(CC) -g -c $(SRC_DIR)/util.c  -o $(OBJ_DIR)/util.o  

$(OBJ_DIR)/optget.o: $(SRC_DIR)/optget.c $(INC_DIR)/util.h
		$(CC) -g -c $(SRC_DIR)/optget.c  -o $(OBJ_DIR)/optget.o

clean:
		rm -rf $(OBJ_DIR)/* test

rebuild: clean all
