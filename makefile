# Simple Makefile for C++ projects

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Source files
SRC_MAIN = $(wildcard *.cpp)             # all cpp in parent dir
SRC_ANN  = $(wildcard libraries/*.cpp)        # all cpp in ann dir
SRC = $(SRC_MAIN) $(SRC_ANN)

# Object files
OBJ = $(SRC:.cpp=.o)

# Target executable
TARGET = main

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
# del /Q *.o ann\*.o $(TARGET)
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean