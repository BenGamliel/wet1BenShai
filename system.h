
#ifndef PP_SYSTEM_H
#define PP_SYSTEM_H


#include "avlStruct.h"
#include "Course.h"
#include "library.h"
#include "scheduleMatrix.h"
#include "HoursAndTrees.h"
#include "HoursAndCounters.h"

class System{
    AVLTree<Course *,int> *Courses;
    scheduleMatrix *Matrix;
    HoursAndTrees *HourTree;
    HoursAndCounters *HourCount;

public:
    System(const int k,const int r){
        this->Courses = new AVLTree<Course *,int>();
        this->Matrix = new scheduleMatrix(k,r);
    }

    StatusType addLecture(int hour,int room,int courseId);

    StatusType getCourseId(int hour,int room,int *courseId);

    StatusType deleteLecture(int hour,int room);

    StatusType changeCourseId(int old, int new_);

    StatusType CalculateScheduleEfficiency(float *efficiency);

    StatusType getAllRoomsByHour(int hour,int **rooms, int *numOfRooms);

    StatusType GetAllLecturesByCourse(int courseId,int **hours,int **rooms,int *numOfLectures);

};


StatusType System::addLecture(int hour,int room,int courseId){
    if(courseId <= 0 || hour < 0 || room < 0)
        return INVALID_INPUT;
    Lecture *le = Matrix->getLecture(hour,room); /* O(1) */
    if(le != nullptr){
        return FAILURE;
    }
    Lecture *l = new Lecture(room,hour);
    AVLNode<Course *,int> *node = Courses->findBYKey(courseId); /* O(log(n)) */
    if(node == NULL){
        Course *c = new Course(courseId);
        Courses->insert(c,courseId); /* O(log(n)) */
        l->setCourse(c);
        c->addLectureToCourse(l);   /* O(log(m))  */
        return SUCCESS;
    }
    l->setCourse(node->getData());
    node->getData()->addLectureToCourse(l);  /* O(log(m))  */
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

StatusType System::deleteLecture(int hour, int room) {
    if(room < 0 || hour < 0){
        return INVALID_INPUT;
    }
    Lecture *l = Matrix->getLecture(hour,room);
    if(l == nullptr)
        return FAILURE;
    Matrix->removeLectureFromMatrix(hour,room);
    HourCount->removeLuctureInHour(hour);
    HourTree->freeAClass(hour,room);
    Course *c = l->getCourse();
    Lecture_Key lk(l->getHour(),l->getRoom());
    c->removeLectureFromCourse(lk);
    if(c->getNum()==0){
        Courses->deleteBYKey(c->getId());
    }
    return SUCCESS;
}

StatusType System::changeCourseId(int old, int new_) {
    if(old <= 0 || new_ <= 0)
        return INVALID_INPUT;
    AVLNode<Course *,int> *node = Courses->findBYKey(old);
    if(node == NULL)
        return FAILURE;


}




#endif //PP_SYSTEM_H
