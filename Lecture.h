#ifndef PP_LECTURE_H
#define PP_LECTURE_H

#include "avlStruct.h"

class Course;

class Lecture_Key{
    int hour;
    int room;
public:
    Lecture_Key() : hour(0),room(0){};

    Lecture_Key(int hour_,int room_) : hour(hour_),room(room_){};

    friend bool operator==(const Lecture_Key &k1, const Lecture_Key &k2);



    friend std::ostream &operator<<(std::ostream &os, const Lecture_Key lec);

    Lecture_Key &operator=(const Lecture_Key &k1){
        this->hour=k1.hour;
        this->room=k1.room;
        return *this;
    }

    int getRoom() const {
        return this->room;
    }

    int getHour() const {
        return this->hour;
    }

};

bool operator==(const Lecture_Key &k1, const Lecture_Key &k2){
    return k1.room==k2.room && k1.hour==k2.hour;
}

std::ostream &operator<<(std::ostream &os, const Lecture_Key &lec) {
    return os << "[Hour: "  << lec.getHour() << ", Room: " << lec.getRoom()<< "]";
}

class Lecture{
    int room;
    int hour;
    Course *c;
public:
    Lecture() : room(0), hour(0){
        c = NULL;
    }

    Lecture(int room_,int hour_) : room(room_), hour(hour_){
        c=NULL;
    }

    ~Lecture(){};

    Course *getCourse(){
        return this->c;
    }

    int getHour() const{
        return this->hour;
    }

    int getRoom() const{
        return this->room;
    }

    void setCourse(Course *course){
        this->c=course;
    }


};


class compareLectures{
public:
    compareLectures(){};

    bool operator()(const Lecture_Key &k1, const Lecture &k2) { // p1 is first
        if (k1.getHour() > k2.getHour())
            return false;
        else if (k2.getHour() == k1.getHour())
            return k1.getRoom() > k2.getRoom();
        else
            return true;
    }
};

#endif //PP_LECTURE_H
