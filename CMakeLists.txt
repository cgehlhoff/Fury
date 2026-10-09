cmake_minimum_required(VERSION 3.20)

project(Fury LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Fury Fury.cpp board.cpp attacks.cpp movegen.cpp fen.cpp search.cpp)