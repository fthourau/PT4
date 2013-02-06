.PHONY: clean, proper, launch, rebuild

# Directories
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = head

# All objects created
OBJECTS = $(OBJ_DIR)/main.o $(OBJ_DIR)/utilitarian.o $(OBJ_DIR)/ustarheader.o \
			$(OBJ_DIR)/options.o $(OBJ_DIR)/archive.o

# Compiler and compilation's options
CC = gcc
CFLAGS = -g -W -Wall
CNORM = --std=c99

# Linker special reference
LDLIBS = -lm

# Program's name
EXEC = tar

all: $(OBJECTS)
		$(CC) $(CNORM) $^ $(LDLIBS) -o $(EXEC) $(CFLAGS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
		$(CC) $(CNORM) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/utilitarian.o: $(SRC_DIR)/utilitarian.c $(INC_DIR)/utilitarian.h
		$(CC) $(CNORM) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/ustarheader.o: $(SRC_DIR)/ustarheader.c $(INC_DIR)/ustarheader.h
		$(CC) $(CNORM) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/options.o: $(SRC_DIR)/options.c $(INC_DIR)/options.h
		$(CC) $(CNORM) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/archive.o: $(SRC_DIR)/archive.c $(INC_DIR)/archive.h $(SRC_DIR)/ustarheader.c $(INC_DIR)/ustarheader.h
		$(CC) $(CNORM) -c $< -o $@ $(CFLAGS)

clean:
		rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.bak

proper: clean
		rm -rf $(EXEC)

launch:
		./$(EXEC)

rebuild: proper all