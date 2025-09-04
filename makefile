# Simple Makefile for C++ projects

CXX = g++
CXXFLAGS := -Wall -Wextra -std=c++17 -I./libraries -I./libraries/functions -I./libraries/layers -I./libraries/optimizers

# Project structure
LIB_DIR = libraries
BUILD_DIR = build

# Source files
SRC_MAIN = $(wildcard *.cpp)             # all cpp in parent dir
SRC_LIBRARIES  = $(wildcard $(LIB_DIR)/*.cpp)        # all cpp in libraries dir
SRC_LIBRARIES_FOLDER = $(wildcard $(LIB_DIR)/*/*.cpp)  # all cpp in subdirs of libraries dir
SRC = $(SRC_MAIN) $(SRC_LIBRARIES) $(SRC_LIBRARIES_FOLDER) # combine all source files

# # Find all .cpp files recursively inside libraries and root
# SRC := $(wildcard ./*.cpp) \
#         $(wildcard $(LIB_DIR)/*.cpp) \
#         $(wildcard $(LIB_DIR)/*/*.cpp)

# Object files
OBJ = $(SRC:%.cpp=$(BUILD_DIR)/%.o)

# Target executable
TARGET = main

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)


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
	
.PHONY: all clean