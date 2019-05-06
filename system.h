
#ifndef PP_SYSTEM_H
#define PP_SYSTEM_H


#include "avlStruct.h"
#include "Course.h"
#include "library.h"

class System{
    AVLTree<Course *,int> *Courses;
public:
    System(){
        this->Courses = new AVLTree<Course *,int>();
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
    /* check in the matrix if exist lecture in this hour and room,
     * if not add it*/
    Lecture *l = new Lecture(room,hour);
    if(l == NULL)
        return ALLOCATION_ERROR;
    AVLNode<Course *,int> *node = Courses->findBYKey(courseId);
    if(node == NULL){
        Course *c = new Course(courseId);
        if(c == NULL)
            return ALLOCATION_ERROR;
        Courses->insert(c,courseId);
        c->addLectureToCourse(l);
        return SUCCESS;
    }
    Course *c = node->getData();
    c->addLectureToCourse(l);
    return SUCCESS;
}

StatusType System::getCourseId(int hour, int room, int *courseId) {
    if(courseId == NULL || room < 0 || hour < 0)
        return INVALID_INPUT;
    /* check in the matrix if they have a lecture in the hour and room given
     * if yes: return the course number
     * else: return FAILURE*/
}

StatusType System::deleteLecture(int hour, int room) {
    if(room < 0 || hour < 0){
        return INVALID_INPUT;
    }
    /**return from the matrix if have lecture
     * if yes:return pointer to the courese and delete it
     * else: FAILURE
     */

}




#endif //PP_SYSTEM_H
