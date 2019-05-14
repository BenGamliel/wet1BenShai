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
//
//class Lecture {
//    Lecture* _data;
//public:
////    friend class Lecture;
//    /*
//     * default constracot for Lecture used when init the scheduale matrix
//     */
//    explicit Lecture(){
//        _data= nullptr;
//    }
//    /*
//     * Lecture constractor with a given lecture
//     * used to insert real lecture into the scheduleMatrix
//     */
//    explicit Lecture(Lecture* lecture){
//        _data=lecture;//verify later when given lucture if points proparly
//    }
//    ~Lecture()= default;
//
//    void changeLecture(Lecture* newLecture){
//        if(!newLecture){
//            _data=nullptr;
//            return;
//        }
//        _data=newLecture;
//    }
//    Lecture* getLecture(){
//        return this->_data;
//    }
//    int getLectureCourseNumber(){//TODO shai needs to implament relavent func
//        if(!_data){
//            return -1;
//        }
//        Course *c = _data->getCourse();
//        return c->getId();
//    }
//    int getLectureCourseHour(){
//        if(!_data){
//            return -1;
//        }
//        return _data->getHour();
//     }
//     int getLectureCourseRoom(){
//         if(!_data){
//             return -1;
//         }
//        return _data->getRoom();
//     }
//
//};

class scheduleMatrix {
 int hours_;
 int rooms_;
Lecture*** schedule_;
public:

    scheduleMatrix( int hours,  int rooms):hours_(hours),rooms_(rooms),schedule_(nullptr){
        try {
            schedule_ = new Lecture** [hours];
        }
        catch(std::bad_alloc&){
            delete schedule_;//maybe not needed here (delete)
        }
        int init_row_counter=0;
        try{
    for (int i=0;i<rooms_;i++){
        schedule_[i]=new Lecture*[rooms];
        init_row_counter++;
        }
    }
        catch(std::bad_alloc&){
            for (int j=0;j<init_row_counter;j++){
                delete []schedule_[j];//to be tested!
            }
            delete [] schedule_;
        }
    }
    ~scheduleMatrix(){
        try {
            for (int i = 0; i < hours_; i++) {
                delete[] schedule_[i];
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
   void insertLectureToMatrix(Lecture *lecature,int hour,int roomId){
        if((!lecature)||(hour<0)||(roomId<0)){
            return;
        }
        schedule_[hour][roomId]= lecature;
    }
    void removeLectureFromMatrix(int hour,int roomId){
        if((hour<0)||(roomId<0)){
            return;
        }
        schedule_[hour][roomId] = nullptr;
       
   }
    /*
     * param hour and roomID if param <0 (invalid input) return nullptr
     * else return pointer to given hour and room
     */
    Lecture* getLecture(int hour,int roomId){
        if((hour<0)||(roomId<0)) {
            return nullptr;
        }
        return schedule_[hour][roomId];
    }
//    void getCourseId(int hour,int roomId,int* courseId){
//        if((roomId<0)||(hour<0)||(!courseId)){
//            return;
//        }
//        schedule_[hour][roomId]->getCourse()->getNum()
//    }
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