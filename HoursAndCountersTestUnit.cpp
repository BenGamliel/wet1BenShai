//
// Created by Ben on 5/6/2019.
//

#include "HoursAndCounters.h"
#include "testUnit.h

bool HoursAndCountersCreateAndDeleteTest(){
    int hour=4;
    int room=5;
    HoursAndCounters hoursNCounters_1(hour,room);
    hour=room=6;
    HoursAndCounters hoursNCounters_2(hour,room);
    return true;
    
}

bool HoursAndCountersMethodTest(){
    int hour=4;
    int room=5;
    HoursAndCounters hoursNCounters_1(hour,room);
    ASSERT_EQUALS(0,hoursNCounters_1.getTotalSum());
    hoursNCounters_1.addLectureInHour(hour);
    ASSERT_EQUALS(1,hoursNCounters_1.getTotalSum());
    hoursNCounters_1.removeLuctureInHour(hour);
    ASSERT_EQUALS(0,hoursNCounters_1.getTotalSum());
    
    
    return true;
    
}






bool HoursAndCountersTest(){
    RUN_TEST(HoursAndCountersCreateAndDeleteTest);
    RUN_TEST(HoursAndCountersMethodTest);
    RUN_TEST(HoursAndCountersOperatorTest);
    
    return true;
}