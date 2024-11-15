# Compiler and Flags
CC = gcc
CFLAGS = -I./include -Wall -Wextra -g

# Directories
SRC_NOUR_DIR = ./src/nour
INCLUDE_NOUR_DIR = ./include/nour
BUILD_DIR = $(SRC_NOUR_DIR)/build
OBJ_DIR = $(BUILD_DIR)/obj
LIB_DIR = $(BUILD_DIR)/lib

# Source and Object Files
SRC_FILES = $(wildcard $(SRC_NOUR_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_NOUR_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Library Name
LIB_NAME = libnour.a

# Targets
all: make_dir $(LIB_DIR)/$(LIB_NAME)

# Ensure necessary directories exist
make_dir:
	mkdir -p $(BUILD_DIR) $(OBJ_DIR) $(LIB_DIR)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_NOUR_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build the static library
$(LIB_DIR)/$(LIB_NAME): $(OBJ_FILES)
	ar rcs $@ $^

# Clean build directories
clean:
	rm -rf $(BUILD_DIR)
