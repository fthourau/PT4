OBJ_DIR = obj
SRC_DIR = src
INC_DIR = head

CC = gcc 

test :  $(OBJ_DIR)/getopt.o  $(OBJ_DIR)/util.o
		$(CC) $(OBJ_DIR)/getopt.o $(OBJ_DIR)/util.o -o test  

$(OBJ_DIR)/util.o : $(SRC_DIR)/util.c $(INC_DIR)/util.h
		$(CC) -g -c $(SRC_DIR)/util.c  -o $(OBJ_DIR)/util.o  

$(OBJ_DIR)/getopt.o : $(SRC_DIR)/getopt.c $(OBJ_DIR)/util.o
		$(CC) -g -c $(SRC_DIR)/getopt.c  -o $(OBJ_DIR)/getopt.o

clean:
		rm -rf $(OBJ_DIR)/*.o test
