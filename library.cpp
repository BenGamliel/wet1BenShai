#include "library.h"

#include <iostream>
#include "system.h"

void *Init(int hours, int rooms){
    System *DS = new System(hours,rooms);
    return (void *) DS;
}

StatusType AddLecture(void *DS, int hour, int roomID, int courseID){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((System *) DS)->addLecture(hour,roomID,courseID);
}

StatusType GetCourseID(void *DS, int hour, int roomID, int *courseID){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((System *)DS)->getCourseId(hour,roomID,courseID);
}

StatusType DeleteLecture(void *DS, int hour, int roomID){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((System *)DS)->deleteLecture(hour,roomID);
}

StatusType ChangeCourseID(void *DS, int oldCourseID, int newCourseID){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((System *)DS)->changeCourseId(oldCourseID,newCourseID);
}

StatusType CalculateScheduleEfficiency(void *DS, float *efficiency){
    if(!DS){
        return INVALID_INPUT;
    }
    return ((System*)DS)->CalculateScheduleEfficiency(efficiency);
}

StatusType GetAllFreeRoomsByHour(void *DS, int hour, int **rooms, int* numOfRooms){
    if(DS==NULL){
        return INVALID_INPUT;
    }
    return ((System*)DS)->getAllRoomsByHour(hour,rooms,numOfRooms);
}

StatusType GetAllLecturesByCourse(void *DS, int courseID, int **hours, int **rooms, int *numOfLectures){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((System *)DS)->GetAllLecturesByCourse(courseID,hours,rooms,numOfLectures);
}

void Quit(void** DS){
    if(DS != NULL && (*DS) != NULL)
        delete ((System *)(*DS));
    (*DS) = NULL;
}