# Version Info
cmake_minimum_required(VERSION 3.10)

# Project Name
project(msk2)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# LLVM
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

llvm_map_components_to_libnames(LLVM_LIBS core native asmparser x86codegen)

# Define paths for headers and source files
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Include directories
include_directories(src)
include_directories(include)
include_directories(${LLVM_INCLUDE_DIRS})

# Collect all source files
file(GLOB SOURCES
    ${SRC_DIR}/*.cpp
)

# Collect all header files (optional, for IDEs)
file(GLOB HEADERS
    ${INCLUDE_DIR}/*.h
)

add_executable(${PROJECT_NAME}
    main.cpp
    ${SOURCES}
    ${HEADERS}  # Optional: Include headers for IDE indexing
)

target_link_libraries(${PROJECT_NAME} ${LLVM_LIBS})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${LLVM_DEFINITIONS})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})








