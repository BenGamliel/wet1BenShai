//
// Created by Ben on 4/25/2019.
//

#ifndef DSWET1SHAY_HOURSANDTREES_H
#define DSWET1SHAY_HOURSANDTREES_H
#include "AVL.h"

class



class HoursAndTrees {
private:
    unsigned int _numOfHours;
    unsigned int _numOfClass;
    AVL<int>** _hourTreesClasses;
public:
    //constractor build new array -every node of the array holds a full avl tree
    //with the number of possible class to fill with a course (means the avl tree holds all avilable class and every
    //of the array represent an hour00000000000000000000000000000000000000000000000000000000000000000000000000000000000000007
    //each hour(int) in the tree means this hour is avilable to be used
    HoursAndTrees(unsigned int numOfHours, unsigned int numOfClass):_numOfHours(numOfHours),_numOfClass(numOfClass){
        try {
            _hourTreesClasses = new AVL *[numOfClass];
        }
        catch(std::bad_alloc&) {
            printf("bad alloc in HoursAndTrees constractor for col(hours) allocation\n");
        }
        int init_counter=0;
        try {
            for (int j = 0; j < numOfClass; j++) {
                _hourTreesClasses[j] = new AVL<int>;
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
        for(int i=0;i<numOfHours;i++){
            for(int j=0;j<numOfClass;j++){
                _hourTreesClasses[i]->insert(j,&_hourTreesClasses[i]);
            }
        }
    }
    
    ~HoursAndTrees(){
        for(int i=0;i<_numOfClass;i++){ //double check if this needs to be num of classes or num of hours (anyway test if all is free)
            delete []_hourTreesClasses[i];
        }
        delete [] _hourTreesClasses;
    }
    

    void scheduleAClass(int hour, int theClass){
        bool res= _hourTreesClasses[hour]->remove(theClass,_hourTreesClasses+hour);
        if(!res) {
            printf("scheduleAclass failed -means the AVL tree didnt remove the node \n");
        }
    }
    void freeAClass(int hour, int theClass) {
        bool res = _hourTreesClasses[hour]->insert(theClass,_hourTreesClasses+hour);
        if (!res) {
            printf("freeAClass failed -means the AVL tree didnt insert the node \n");
        }
    }
};


#endif//DSWET1SHAY_HOURSANDTREES_H
//    bool scheduleAClass( int hour, int class){
//             return _hourTreesClasses[hour]->remove(class,_hourTreesClasses[hour]);
//         }
//         catch(){
//             printf("scheduleAclass failed -means the AVL tree didnt remove the node \n");
//         }
//    }
//    bool freeAClass(unsigned int hour, int class){
//        try {
//            return _hourTreesClasses[hour]->insert(class,_hourTreesClasses[hour]);
//        }
//        catch(){
//            printf("freeAClass failed -means the AVL tree didnt insert the node \n");
//        }
//    }
//    void scheduleAClass(unsigned int hour, int class){
//         _hourTreesClasses[hour]->remove(class,&_hourTreesClasses[hour]);
//    }
//    void freeAClass(unsigned int hour, int class){
//         _hourTreesClasses[hour]->insert(class,&_hourTreesClasses[hour]);
//    }