cmake_minimum_required(VERSION 3.6)
project(pp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES library.cpp library.h Course.h Lecture.h system.h avlStruct.h HoursAndTrees.h
        HoursAndTrees.cpp HoursAndCounters.h scheduleMatrix.h scheduleMatrix.cpp main.cpp auxFunction.h)
add_library(pp ${SOURCE_FILES})