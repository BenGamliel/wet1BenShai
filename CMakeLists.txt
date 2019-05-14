cmake_minimum_required(VERSION 3.14)
project(Wet1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++0x -DNDBUG -Wall")

add_executable(Wet1 main.cpp
        Course.h Lecture.h
        system.h library.cpp library.h
        HoursAndCounters.h
        HoursAndTrees.h
        scheduleMatrix.h
        avlStruct.h
        auxFunction.h)