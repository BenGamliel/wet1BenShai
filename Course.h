#ifndef PP_COURSE_H
#define PP_COURSE_H

#include "avlStruct.h"
#include "Lecture.h"

class Course{
    int id;
    int numOfLectures;
    AVLTree<Lecture *,Lecture_Key,compareLectures> *lecturesTree;
public:
    Course(int id_) : id(id_), numOfLectures(0){
        this->lecturesTree = new AVLTree<Lecture *,Lecture_Key,compareLectures>();
    }

    Course(int id_,int numOfLectures_,AVLTree<Lecture *,Lecture_Key,compareLectures> *t){
        this->id=id_;
        this->numOfLectures=numOfLectures_;
        this->lecturesTree = t;
    }

    int getId() const{
        return this->id;
    }

    void setId(int id_){
        this->id=id_;
    }

    void addLectureToCourse(Lecture *lec);

    void removeLectureFromCourse(const Lecture_Key &k1);

    AVLTree<Lecture *,Lecture_Key,compareLectures> *getLecturesTree();

    ~Course(){
        delete this->lecturesTree;
    }
};

void Course::addLectureToCourse(Lecture *lec) {
    Lecture_Key key(lec->getHour(),lec->getRoom());
    this->lecturesTree->insert(lec,key);
    this->numOfLectures++;
}

void Course::removeLectureFromCourse(const Lecture_Key &k1) {
    this->lecturesTree->deleteBYKey(k1);
    this->numOfLectures--;
}

AVLTree<Lecture *,Lecture_Key,compareLectures> *Course::getLecturesTree() {
    return this->lecturesTree;
}

#endif //PP_COURSE_H
