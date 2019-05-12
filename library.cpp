#include "library.h"

#include <iostream>
#include "Course.h"

void *Init(int hours, int rooms);

StatusType AddLecture(void *DS, int hour, int roomID, int courseID){
}

StatusType GetCourseID(void *DS, int hour, int roomID, int *courseID);

StatusType DeleteLecture(void *DS, int hour, int roomID);

StatusType ChangeCourseID(void *DS, int oldCourseID, int newCourseID);

StatusType CalculateScheduleEfficiency(void *DS, float *efficiency);

StatusType GetAllFreeRoomsByHour(void *DS, int hour, int **rooms, int* numOfRooms);

StatusType GetAllLecturesByCourse(void *DS, int courseID, int **hours, int **rooms, int *numOfLectures);

void Quit(void** DS);