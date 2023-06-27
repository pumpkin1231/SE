cmake_minimum_required(VERSION 3.23)
project(Sudoku)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")

# 添加覆盖率编译参数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

include_directories(Inc)

add_executable(Sudoku main.cpp Src/board.cpp Src/sudoku.cpp)
