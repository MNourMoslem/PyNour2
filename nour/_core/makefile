# Compiler and Flags
CC = gcc
PY_INCLUDE = C:/Users/Abed/anaconda3/include
PY_LIBS = C:/Users/Abed/anaconda3/libs
PY_LIBNAME = python3
CFLAGS = -I./include -I$(PY_INCLUDE) -L$(PY_LIBS) -Wall -Wextra -g -l$(PY_LIBNAME)
SETUP_PY = ./setup.py

# Directories
SRC_DIR = ./src
SRC_NOUR_DIR = $(SRC_DIR)/nour
INCLUDE_NOUR_DIR = ./include/nour
BUILD_DIR = $(SRC_NOUR_DIR)/build
OBJ_DIR = $(BUILD_DIR)/obj
LIB_DIR = $(BUILD_DIR)/lib
GEN_DIR = $(BUILD_DIR)/generated
PYD_OUT_DIR = $(BUILD_DIR)

# Python script
FILE_GEN_PY = ./code_generator/run.py

# Library Name
LIB_NAME = libnour.a

# Source Files
SOURCES = $(wildcard $(SRC_NOUR_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_NOUR_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# Default target
all: $(BUILD_DIR) generate $(LIB_DIR)/$(LIB_NAME) setup

# Create build directories
$(BUILD_DIR):
	mkdir -p $(OBJ_DIR) $(LIB_DIR) $(GEN_DIR)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_NOUR_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -l$(PY_LIBNAME)

# Archive library
$(LIB_DIR)/$(LIB_NAME): $(OBJECTS)
	ar rcs $@ $^

# Run Python script
generate:
	python $(FILE_GEN_PY)

setup: $(LIB_DIR)/$(LIB_NAME)
	gcc -shared -fPIC -I$(PY_INCLUDE)  -L$(PY_LIBS)\
	 -I./include -L./src/nour/build/lib ./src/nour/pynour_module.c -o $(PYD_OUT_DIR)/nour.pyd -lnour -l$(PY_LIBNAME)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
