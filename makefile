# Simple Makefile for C++ projects

CXX = g++
CFLAGS = -MMD -MP
CXXFLAGS := $(CFLAGS) -fdiagnostics-color=always -g -Wall -Wextra -std=c++17 \
-I./libraries \
-I./libraries/functions \
-I./libraries/layers \
-I./libraries/optimizers \
-I./libraries/activations \
-I./libraries/loss

LDLIBS = # -lfmt -I./vcpkg/packages/fmt_x64-windows/include/fmt

# Project structure
LIB_DIR = libraries
BUILD_DIR = build_files

# Source files
SRC_MAIN = $(wildcard *.cpp)             # all cpp in parent dir
SRC_LIBRARIES  = $(wildcard $(LIB_DIR)/*.cpp)        # all cpp in libraries dir
SRC_LIBRARIES_FOLDER = $(wildcard $(LIB_DIR)/*/*.cpp)  # all cpp in subdirs of libraries dir
SRC = $(SRC_MAIN) $(SRC_LIBRARIES) $(SRC_LIBRARIES_FOLDER) # combine all source files

# # Find all .cpp files recursively inside libraries and root
# SRC := $(wildcard ./*.cpp) \
#         $(wildcard $(LIB_DIR)/*.cpp) \
#         $(wildcard $(LIB_DIR)/*/*.cpp)

# Object and dependency files
OBJ = $(SRC:%.cpp=$(BUILD_DIR)/%.o)
DEP = $(SRC:%.cpp=$(BUILD_DIR)/%.d)

# Target executable
TARGET = main

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LDLIBS)


# Compile .cpp to .o and keep object files in build directory
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean
# del /Q *.o libraries\*.o $(TARGET)
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Build and run
run: all
	./$(TARGET)
	
.PHONY: all clean run