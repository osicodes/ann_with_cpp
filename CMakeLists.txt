# CMakeLists.txt for the ANN_WITH_CPP project

# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.20.0)

# Define the project name and version
project(main VERSION 1.0.0)

# set_source_files_properties(main.cpp PROPERTIES COMPILE_FLAGS "-Wall -Wextra -std=c++17 -I./libraries -I./libraries/functions -I./libraries/layers -I./libraries/optimizers -I./libraries/activations -I./libraries/loss")

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
# include_directories(${PROJECT_SOURCE_DIR}/libraries)

# Add include directories for the library files
include_directories(
    ./libraries
    ./libraries/functions
    ./libraries/layers
    ./libraries/optimizers
    ./libraries/loss
)

# Define all source files using glob
file(GLOB SRC_LIBRARIES "libraries/*.cpp")
file(GLOB SRC_LIBRARIES_FOLDER "libraries/*/*.cpp")

# Add the executable
set(SOURCE_FILES main.cpp ${SRC_LIBRARIES} ${SRC_LIBRARIES_FOLDER})

# Create the executable target
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Set compiler flags
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
# target_compile_options(${PROJECT_NAME} PRIVATE -g)  # Uncomment for debugging
# target_compile_options(${PROJECT_NAME} PRIVATE -O3)  # Uncomment for optimization

# Optionally, you can specify output directories for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Optionally, you can add custom commands or targets for cleaning up build files
# add_custom_target(clean-all COMMAND ${CMAKE_COMMAND} -P cmake_clean.cmake WORKING_DIRECTORY ${CMAKE_BINARY_DIR} COMMENT "Cleaning all build files")
# file(REMOVE_RECURSE ${PROJECT_SOURCE_DIR}/bin)
# file(REMOVE_RECURSE ${PROJECT_SOURCE_DIR}/CMakeFiles)
# file(REMOVE ${PROJECT_SOURCE_DIR}/CMakeCache.txt)
# file(REMOVE ${PROJECT_SOURCE_DIR}/cmake_install.cmake)
# file(REMOVE ${PROJECT_SOURCE_DIR}/Makefile)
# file(REMOVE ${PROJECT_SOURCE_DIR}/main)
# file(REMOVE ${PROJECT_SOURCE_DIR}/main.debug)

# To build the project, run the following commands in the terminal:
# mkdir build && cd build
# cmake .. # Generate the build files
# cmake --build . # Build the project
# or simply use:
# cmake -S . -B ./build && cd build
# cmake --build . # Build the project

# To run the executable, use:
# ..\bin\main (..\bin\main.exe on Windows)

# To clean up build files, you can run:
# cmake --build . --target clean 
# or manually delete the build directory and its contents.

# Note: Adjust the paths and settings as necessary for your specific project structure and requirements.