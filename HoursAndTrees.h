//
// Created by Ben on 4/25/2019.
//

#ifndef DSWET1SHAY_HOURSANDTREES_H
#define DSWET1SHAY_HOURSANDTREES_H

#include "avlStruct.h"
#include <iostream>

class compareInt{
public:
    compareInt(){};

    bool operator()(const int LH,const int RH) { // p1 is first
        return LH==RH;
    }

    ~compareInt(){};
};

class HoursAndTrees {
private:
    int _numOfHours;
    int _numOfClass;
    AVLTree<int,int,compareInt>** _hourTreesClasses;
public:
    //constractor build new array -every node of the array holds a full avl tree
    //with the number of possible class to fill with a course (means the avl tree holds all avilable class and every
    //of the array represent an hour
    //each hour(int) in the tree means this hour is avilable to be used
    HoursAndTrees( int numOfHours,  int numOfClass):_numOfHours(numOfHours),_numOfClass(numOfClass){
        try {
            _hourTreesClasses = new AVLTree<int,int,compareInt>*[numOfHours];
        }
        catch(std::bad_alloc&) {
            printf("bad alloc in HoursAndTrees constractor for col(hours) allocation\n");
        }
        int init_counter=0;
        int* classValueArray;
        classValueArray=new int(_numOfHours);
        for (int i=0;i<numOfClass;i++){
            classValueArray[i]=i;
        }

        try {
            for (int j = 0; j < numOfClass; j++) {
                _hourTreesClasses[j] = new AVLTree<int,int,compareInt>(classValueArray,numOfClass);
                init_counter++;
            }
        }
        catch(std::bad_alloc&) {
            printf("bad alloc in HoursAndTrees constractor for rows(class) allocation\n");

            for(int i=0;i<init_counter;i++){
                delete []_hourTreesClasses[i];
            }
            delete [] _hourTreesClasses;
        }
//        delete classValueArray;//TODO recheck here
    printf("hello\n");
    }

    ~HoursAndTrees(){
        for(int i=0;i<_numOfClass;i++){ //double check if this needs to be num of classes or num of hours (anyway test if all is free)
            delete []_hourTreesClasses[i];
        }
        delete [] _hourTreesClasses;
    }


    void scheduleAClass(int hour, int theClass){
        _hourTreesClasses[theClass]->deleteBYKey(hour);

    }
    void freeAClass(int hour, int theClass) {
        _hourTreesClasses[theClass]->insert(hour,hour);

    }
    //getAllFreeRoomsByHour will return a malloc array contains all the room avilable in given hour
    //numOfRooms gets the size of the tree
    //*rooms gets a malloc array with the given size (numOfRooms)
    //InOrderToArray load the tree with the given hour to the rooms array
    void getAllFreeRoomsByHour(int hour,int **rooms,int* numOfRooms){
        if((!numOfRooms)||(!rooms)||(hour<0)){
            numOfRooms= nullptr;
            rooms= nullptr;
            return;
        }
        *numOfRooms=_hourTreesClasses[hour]->getSize();
        *rooms = (int*)malloc(sizeof(int)*(*numOfRooms));
        _hourTreesClasses[hour]->inOrderToArray(*rooms);
    }

};




#endif