
#ifndef PP_SYSTEM_H
#define PP_SYSTEM_H


#include "avlStruct.h"
#include "Course.h"
#include "library.h"
#include "scheduleMatrix.h"
#include "HoursAndTrees.h"
#include "HoursAndCounters.h"
#include "auxFunction.h"
#include <stdlib.h>

#define nullptr 0

class System{
    AVLTree<Course *,int> *Courses;
    scheduleMatrix *Matrix;
    HoursAndTrees *HourTree;
    HoursAndCounters *HourCount;

public:
    System(const int hours,const int rooms){
        this->Courses = new AVLTree<Course *,int>();
        this->Matrix = new scheduleMatrix(hours,rooms);
        this->HourTree=new HoursAndTrees(hours,rooms);
        this->HourCount=new HoursAndCounters(hours,rooms);
    }

    void addCourse(int courseId_, int numOfLec, AVLTree<Lecture *,Lecture_Key,compareLectures> *t){
        Course *c = new Course(courseId_,numOfLec,t);
        this->Courses->insert(c,courseId_);
    }

    void deleteCourse(int courseId_) {
        Course *c = Courses->findBYKey(courseId_)->getData();
        Courses->deleteBYKey(courseId_);
        delete c;
    }



    StatusType addLecture(int hour,int room,int courseId);


    StatusType getCourseId(int hour,int room,int *courseId);


    StatusType deleteLecture(int hour,int room);


    StatusType changeCourseId(int old, int new_);

    StatusType CalculateScheduleEfficiency(float *efficiency) {
        if(!efficiency){
            return FAILURE;
        }
        this->HourCount->getEfiiciency(efficiency);
        return SUCCESS;
    }

    StatusType getAllRoomsByHour(int hour,int **rooms, int *numOfRooms){
        if((!rooms)||(!numOfRooms)||(hour<0)){
            return FAILURE;
        }
        this->HourTree->getAllFreeRoomsByHour(hour,rooms,numOfRooms);
        return SUCCESS;

    }

    StatusType GetAllLecturesByCourse(int courseId,int **hours,int **rooms,int *numOfLectures);

    ~System(){
        Course **SysCurse = new Course *[this->Courses->getSize()];
        this->Courses->inOrderToArray(SysCurse);
        for (int i = 0; i < this->Courses->getSize(); i++) {
            delete SysCurse[i];
        }
        delete[] SysCurse;
        delete this->Courses;
    }

};

StatusType System::addLecture(int hour,int room,int courseId){
    if(courseId <= 0 || hour < 0 || room < 0)
        return INVALID_INPUT;
    Lecture* temp = Matrix->getLecture(hour,room); /* O(1) */
    if(temp != nullptr){
        return FAILURE;
    }
    Lecture *lecture = new Lecture(room,hour);
    Matrix->insertLectureToMatrix(lecturePoitner(lecture),hour,room);
    AVLNode<Course *,int> *node = Courses->findBYKey(courseId); /* O(log(n)) */
    if(node == NULL){
        Course *c = new Course(courseId);
        Courses->insert(c,courseId); /* O(log(n)) */
        lecture->setCourse(c);
        c->addLectureToCourse(lecture);   /* O(log(m))  */
        return SUCCESS;
    }
    lecture->setCourse(node->getData());
    node->getData()->addLectureToCourse(lecture);  /* O(log(m))  */
    HourTree->scheduleAClass(hour,room);
    HourCount->addLectureInHour(hour);
    return SUCCESS;
}

StatusType System::getCourseId(int hour, int room, int *courseId) {
    if(courseId == NULL || room < 0 || hour < 0)
        return INVALID_INPUT;
    Lecture *l = Matrix->getLecture(hour,room);
    if(l == nullptr)
        return FAILURE;
    *courseId = l->getCourse()->getId();
    return SUCCESS;
}
//        this->Matrix->getLecture(hour,room)->getCourseNumber();//TODO the same as above


StatusType System::deleteLecture(int hour, int room) {
    if(room < 0 || hour < 0){
        return INVALID_INPUT;
    }
    Lecture *lecture = Matrix->getLecture(hour,room);
    if(lecture == nullptr)
        return FAILURE;
    Matrix->removeLectureFromMatrix(hour,room);
    HourCount->removeLuctureInHour(hour);
    HourTree->freeAClass(hour,room);

    Course *course = lecture->getCourse();
    Lecture_Key lk(lecture->getHour(),lecture->getRoom());
    course->removeLectureFromCourse(lk);
    if(course->getNum()==0){
        Courses->deleteBYKey(course->getId());
    }
    return SUCCESS;
}


StatusType System::changeCourseId(int old, int new_) {
    if(old <= 0 || new_ <= 0)
        return INVALID_INPUT;
    AVLNode<Course *,int> *node = Courses->findBYKey(old);
    if(node == NULL)
        return FAILURE;
    AVLNode<Course *,int> *node1 = Courses->findBYKey(new_);
    if(node1 == NULL){
        node->getData()->setId(new_);
        return SUCCESS;
    }
    AVLTree<Lecture *,Lecture_Key,compareLectures> *lectureTree = unionTrees(node->getData()->getLecturesTree(),
                                                                             node1->getData()->getLecturesTree(),
                                                                             node->getData()->getNum(),node1->getData()->getNum());
    this->deleteCourse(old);
    this->deleteCourse(new_);
    this->addCourse(new_,lectureTree->getSize(),lectureTree);
    return SUCCESS;
}


StatusType System::GetAllLecturesByCourse(int courseId, int **hours, int **rooms, int *numOfLectures) {
    if(courseId <= 0 || hours == NULL || rooms == NULL || numOfLectures == NULL)
        return INVALID_INPUT;
    AVLNode<Course *,int> *node = Courses->findBYKey(courseId);
    if(node==NULL)
        return FAILURE;
    *hours = (int *) malloc(node->getData()->getLecturesTree()->getSize() * sizeof(**hours));
    *rooms = (int *) malloc(node->getData()->getLecturesTree()->getSize() * sizeof(**rooms));
    if(!*hours || !*rooms)
        return ALLOCATION_ERROR;
    Lecture_Key *keys = new Lecture_Key[node->getData()->getLecturesTree()->getSize()];
    node->getData()->getLecturesTree()->inOrderToArrayKeys(&keys);
    for(int i=0;i < node->getData()->getNum()-1; i++){
        (*hours)[i] = keys[i].getHour();
        (*rooms)[i] = keys[i].getRoom();
    }
    *numOfLectures = node->getData()->getNum();
    delete[] keys;
    return SUCCESS;
}




#endif //PP_SYSTEM_H