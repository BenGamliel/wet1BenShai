//
// Created by Ben on 4/25/2019.
//

#ifndef DSWET1SHAY_SCHEDULEMATRIX_H
#define DSWET1SHAY_SCHEDULEMATRIX_H

#include "../../Documents/GitHub/wet1Lucky/Lecture.h"
#include <stdio.h>


//int course_number;
//int room;
//int hour;
//Course *c;

class lecturePoiner {
    Lecture* _data;
public:
    friend class Lecture;
     explicit lecturePointer(const Lecture* lucture){
        _data=lucture;//verify later when given lucture if points proparly
    }
    int getLectureCourseNumber(){
        return _data->getCourseNumber();
    }
    int getLectureCourseHour(){
        return _data->getHour();
     }
     int getLectureCourseRoom(){
        return _data->getRoom();
     }
    
    
    ~lecturePoiner()= default{
    }
};

class scheduleMatrix {
unsigned int _hours;
unsigned int _rooms;
lecturePoiner** _schedule;
public:
    /* the allocation
     * int rows = ..., cols = ...;
int** matrix = new int*[rows];
for (int i = 0; i < rows; ++i)
    matrix[i] = new int[cols];
     
     delete part
     for (int i = 0; i < rows; ++i)
    delete [] matrix[i];
delete [] matrix;
     
     */
    scheduleMatrix(unsigned int hours, unsigned int rooms):_hours(hours),_rooms(rooms),_schedule(nullptr){
        try {
            _schedule = new lecturePoiner* [hours];
        }
        catch(std::bad_alloc&){
            delete _schedule;//maybe not needed here (delete)
        }
        int init_row_counter=0;
        try{
    for (int i=0;i<rooms;i++){
        _schedule[i]=new lecturePoiner[rooms];
        init_row_counter++;
        }
    }
        catch(std::bad_alloc&){
            for (int j=0;j<init_row_counter;j++){
                delete []_schedule[j];//to be tested!
            }
            delete [] _schedule;
        }
    }
    ~scheduleMatrix(){
        try {
            for (int i = 0; i < _hours; i++) {
                delete[] _schedule[i];
            }
        }
            catch(std::bad_alloc&){
                printf("delete in scheduleMatrix failed l \n");
            }
        }
    
};



#endif //DSWET1SHAY_SCHEDULEMATRIX_H
