//
// Created by Ben on 5/6/2019.
//

#include "HoursAndTrees.h"
#include "testUnit.h

bool HoursAndTreesCreateAndDeleteTest(){
    HoursAndTrees hourTree(5,4);
    HoursAndTrees hourTree_2(0,0);
    HoursAndTrees hourTree_3(2,1);
    return true;
}

bool HoursAndTreesMethodTest(){
    
    return true;
}

bool HoursAndTreesOperatorTest(){
    
    return true;
}




bool HoursAndTreesTest(){
    RUN_TEST(HoursAndTreesCreateAndDeleteTest);
    RUN_TEST(HoursAndTreesMethodTest);
    RUN_TEST(HoursAndTreesOperatorTest);
    
    return true;
}