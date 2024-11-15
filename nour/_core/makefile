CC = gcc
CFLAGS = -I./include/

SRC_NOUR_DIR = ./src/nour
INCLUDE_NOUR_DIR = ./inlcude/nour
BUILD_DIR = $(SRC_NOUR_DIR)/build
OBJ_DIR = $(BUILD_DIR)/obj
LIB_DIR = $(BUILD_DIR)/lib

all : make_dir compile_src

OBJ_OFILES = $(wildcard $(OBJ_NOUR_DIR)/*.o)

make_dir: 
	mkdir -p $(BUILD_DIR) $(OBJ_DIR) $(LIB_DIR)

compile_src:
	$(CC) $(CFLAGS) $(SRC_NOUR_DIR)/*.c -o $(OBJ_DIR)

clean:
	rm -rf $(BUILD_DIR)