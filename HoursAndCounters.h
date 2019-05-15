//
// Created by Ben on 4/25/2019.
//

#ifndef DSWET1SHAY_HOURSANDCOUNTERS_H
#define DSWET1SHAY_HOURSANDCOUNTERS_H

#include "stdio.h"

bool HoursAndCountersTest();

class HoursAndCounters {
    int _hours;
    int _rooms;
    int* _hoursCounters;
    double _totalSum;
    double numberOfRooms;

public:
    //HoursAndCounter Counstractor input: a given value to init the array
    // O(n) as n is hours value
    explicit HoursAndCounters(int hours,int rooms) :_hours(hours),_rooms(rooms),_totalSum(0){
        _hoursCounters = new  int[hours];
        for (int i = 0; i < hours; i++) {
            _hoursCounters[i] = 0;
        }
        numberOfRooms=_hours*_rooms;
        }
    //Destractor free array
    ~HoursAndCounters(){
        delete[]_hoursCounters;//verify this is the way to free a full array
    }
    void addLectureInHour(int hour){
        if(_hoursCounters[hour]==0){
            _totalSum++;
        }
        _hoursCounters[hour]++;
    }
    void removeLuctureInHour(int hour){
        _hoursCounters[hour]--;
        if(_hoursCounters[hour]==0){
            if(_hoursCounters[hour]==0){
                return;
            }
            _hoursCounters[hour]--;
        }
    }
    unsigned int getTotalSum(){
        return _totalSum;
    }
    void getEfiiciency(float* efficiency){
        *efficiency=(float)(_totalSum/numberOfRooms);
    }
};


#endif //DSWET1SHAY_HOURSANDCOUNTERS_H
