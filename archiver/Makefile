.PHONY: clean, proper, rebuild, test

# Directories
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = head
TST_DIR = test

# All objects created
OBJECTS = $(OBJ_DIR)/main.o $(OBJ_DIR)/ustarheader.o $(OBJ_DIR)/create.o \
			$(OBJ_DIR)/extract.o  $(OBJ_DIR)/add.o $(OBJ_DIR)/delete.o \
			$(OBJ_DIR)/update.o $(OBJ_DIR)/list.o $(OBJ_DIR)/diff.o \
		 	$(OBJ_DIR)/options.o $(OBJ_DIR)/utilitarian.o \
		 	$(OBJ_DIR)/optionhandling.o $(OBJ_DIR)/filehandling.o \
		 	$(OBJ_DIR)/archivehandling.o $(OBJ_DIR)/errors.o

# Compiler and compilation's options
CC = gcc
CFLAGS = -g -W -Wall
CNORM = --std=c99

# Linker special reference
LDLIBS = -lm

# Program's name
CMD_NAME = tar
TST_NAME = tarTest

all: $(OBJECTS)
		$(CC) $(CNORM) $^ $(LDLIBS) -o $(CMD_NAME) $(CFLAGS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
		$(CC) $(CNORM) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h 
		$(CC) $(CNORM) -c $< -o $@ $(CFLAGS)

clean:
		rm -rf $(OBJ_DIR)/*.o $(OBJ_DIR)/*.bak

proper: clean
		rm -rf $(CMD_NAME)

rebuild: proper all

test:
		./$(TST_DIR)/$(TST_NAME)
