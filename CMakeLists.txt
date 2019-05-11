cmake_minimum_required(VERSION 3.10)
project(wet1benshai)

set(CMAKE_CXX_STANDARD 11)

add_executable(wet1benshai main.cpp testUnit.h
        HoursAndCounters.h HoursAndCountersTestUnit.cpp
        HoursAndTrees.h HoursAndTreesTestUnit.cpp
        scheduleMatrix.h scheduleMatrixTestUnit.cpp AVL.h)