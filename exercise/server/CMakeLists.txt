cmake_minimum_required(VERSION 3.5)
project(XO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Board.cpp
    Board.h
    Game_logic.cpp
    Game_logic.h
    Harness.h
    Input_con.h
    Input_Interface.h
    main.cpp
    Output_con.h
    Output_Interface.h)

add_executable(XO ${SOURCE_FILES})