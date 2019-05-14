//
// Created by Ben on 4/25/2019.
//

#ifndef DSWET1SHAY_SCHEDULEMATRIX_H
#define DSWET1SHAY_SCHEDULEMATRIX_H

#include "Lecture.h"
#include "Course.h"




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
                for (int j=0;j<rooms;j++){
                    schedule_[i][j]= nullptr;
                }
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
        if((schedule_[hour][roomId]== nullptr)||(schedule_[hour][roomId]==NULL)){
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



#endif