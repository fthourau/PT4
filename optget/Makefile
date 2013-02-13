OBJ_DIR = obj
SRC_DIR = src
INC_DIR = head

CC = gcc
LDLIBS = -lm
CNORM = --std=c99

all:  $(OBJ_DIR)/main.o $(OBJ_DIR)/optget.o $(OBJ_DIR)/util.o $(OBJ_DIR)/options.o $(OBJ_DIR)/ustarheader.o $(OBJ_DIR)/utilitarian.o $(OBJ_DIR)/archive.o
		$(CC) $(CNORM) $(OBJ_DIR)/main.o $(OBJ_DIR)/optget.o $(OBJ_DIR)/util.o $(OBJ_DIR)/options.o $(OBJ_DIR)/ustarheader.o $(OBJ_DIR)/utilitarian.o $(OBJ_DIR)/archive.o $(LDLIBS) -o test  

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/optget.h
		$(CC) -g -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/util.o: $(SRC_DIR)/util.c
		$(CC) -g -c $(SRC_DIR)/util.c  -o $(OBJ_DIR)/util.o  

$(OBJ_DIR)/optget.o: $(SRC_DIR)/optget.c $(INC_DIR)/util.h
		$(CC) -g -c $(SRC_DIR)/optget.c  -o $(OBJ_DIR)/optget.o

$(OBJ_DIR)/options.o: $(SRC_DIR)/options.c $(INC_DIR)/options.h
		$(CC) -g -c $(SRC_DIR)/options.c -o $(OBJ_DIR)/options.o

$(OBJ_DIR)/ustarheader.o: $(SRC_DIR)/ustarheader.c $(INC_DIR)/ustarheader.h
		$(CC) -g -c $(SRC_DIR)/ustarheader.c -o $(OBJ_DIR)/ustarheader.o

$(OBJ_DIR)/utilitarian.o: $(SRC_DIR)/utilitarian.c $(INC_DIR)/utilitarian.h
		$(CC) -g -c $(SRC_DIR)/utilitarian.c -o $(OBJ_DIR)/utilitarian.o
$(OBJ_DIR)/archive.o: $(SRC_DIR)/archive.c $(INC_DIR)/archive.h
		$(CC) -g -c $(SRC_DIR)/archive.c -o $(OBJ_DIR)/archive.o
clean:
		rm -rf $(OBJ_DIR)/* test one.txt txo.txt

rebuild: clean all
