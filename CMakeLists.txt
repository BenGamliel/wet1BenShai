cmake_minimum_required(VERSION 3.6)
project(pp2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES mainTrue.cpp auxFunction.h avlStruct.h
        Course.h HoursAndCounters.h Lecture.h library.cpp
        HoursAndTrees.cpp HoursAndTrees.h library.h scheduleMatrix.h scheduleMatrix.cpp system.h)
add_executable(pp2 ${SOURCE_FILES})