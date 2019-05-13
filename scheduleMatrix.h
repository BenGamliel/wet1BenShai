//
// Created by Ben on 4/25/2019.
//

#ifndef DSWET1SHAY_SCHEDULEMATRIX_H
#define DSWET1SHAY_SCHEDULEMATRIX_H

#include "Lecture.h"
#include "Course.h"


//int course_number;
//int room;
//int hour;
//Course *c;

class lecturePoiner {
    Lecture* _data;
public:
//    friend class Lecture;
    /*
     * default constracot for lecturePointer used when init the scheduale matrix
     */
    explicit lecturePoiner(){
        _data= nullptr;
    }
    /*
     * lecturePointer constractor with a given lecture
     * used to insert real lecture into the scheduleMatrix
     */
    explicit lecturePoiner(Lecture* lecture){
        _data=lecture;//verify later when given lucture if points proparly
    }
    ~lecturePoiner()= default;
    
    void changeLecture(Lecture* newLecture){
        if(!newLecture){
            _data=nullptr;
            return;
        }
        _data=newLecture;
    }
    Lecture* getLecture(){
        return this->_data;
    }
    int getLectureCourseNumber(){
        if(!_data){
            return -1;
        }
        Course *c = _data->getCourse();
        return c->getId();
    }
    int getLectureCourseHour(){
        if(!_data){
            return -1;
        }
        return _data->getHour();
     }
     int getLectureCourseRoom(){
         if(!_data){
             return -1;
         }
        return _data->getRoom();
     }
     
};

class scheduleMatrix {
unsigned int _hours;
unsigned int _rooms;
lecturePoiner** _schedule;
public:

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
    /*
    * param hour and roomID const lecature ref if param <0 or lecture adress is null (invalid input) return
    * else init a new lecaturePointer with the given param
    */
   void insertLectureToMatrix(Lecture* lecature,int hour,int roomId){
        if((!lecature)||(hour<0)||(roomId<0)){
            return;
        }
        _schedule[hour][roomId].changeLecture(lecature);
    }
    void removeLectureFromMatrix(int hour,int roomId){
        if((hour<0)||(roomId<0)){
            return;
        }
        _schedule[hour][roomId].changeLecture(nullptr);
       
   }
    /*
     * param hour and roomID if param <0 (invalid input) return nullptr
     * else return pointer to given hour and room
     */
    Lecture* getLecture(int hour,int roomId){
        if((hour<0)||(roomId<0)) {
            return nullptr;
        }
        return _schedule[hour][roomId].getLecture();
    }
    void getCourseId(int hour,int roomId,int* courseId){
        if((roomId<0)||(hour<0)||(!courseId)){
            return;
        }
        *courseId=_schedule[hour][roomId].getLectureCourseNumber();
    }
};



#endif //DSWET1SHAY_SCHEDULEMATRIX_H
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