# Compiler and Flags
CC = gcc
CFLAGS = -I./include -Wall -Wextra -g

# Directories
SRC_DIR = ./src
SRC_NOUR_DIR = $(SRC_DIR)/nour
INCLUDE_NOUR_DIR = ./include/nour
BUILD_DIR = $(SRC_NOUR_DIR)/build
OBJ_DIR = $(BUILD_DIR)/obj
LIB_DIR = $(BUILD_DIR)/lib
GEN_DIR = $(BUILD_DIR)/generated

# Python script
FILE_GEN_PY = ./code_generator/run.py

# Library Name
LIB_NAME = libnour.a

# Source Files
SOURCES = $(wildcard $(SRC_NOUR_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_NOUR_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# Default target
all: $(BUILD_DIR) generate $(LIB_DIR)/$(LIB_NAME)

# Create build directories
$(BUILD_DIR):
	mkdir -p $(OBJ_DIR) $(LIB_DIR) $(GEN_DIR)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_NOUR_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Archive library
$(LIB_DIR)/$(LIB_NAME): $(OBJECTS)
	ar rcs $@ $^

# Run Python script
generate:
	python $(FILE_GEN_PY)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
