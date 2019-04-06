# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the project name
project (examples)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

file(GLOB EXAMPLES_SRC "examples/*.cpp")
# create executable for each example
foreach( file ${EXAMPLES_SRC})
    get_filename_component(EXE_NAME ${file} NAME_WE)
    add_executable(${EXE_NAME} ${file})
    target_include_directories(${EXE_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
endforeach( file ${EXAMPLES_SRC} )
