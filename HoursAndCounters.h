//
// Created by Ben on 4/25/2019.
//

#ifndef DSWET1SHAY_HOURSANDCOUNTERS_H
#define DSWET1SHAY_HOURSANDCOUNTERS_H

//hello

class HoursAndCounters {
    int _hours;
    unsigned int* _hoursCounters;
    unsigned int _totalSum;
public:
    //HoursAndCounter Counstractor input: a given value to init the array
    // O(n) as n is hours value
    explicit HoursAndCounters(int hours) :_hours(hours),_totalSum(0){
        try {
            _hoursCounters = new unsigned int[hours];
//        _hoursCounters={0};//init new array with the 0 value in all the array
            for (int i = 0; i < hours; i++) {
                _hoursCounters[i] = 0;
            }
        }
        catch(std::bad_alloc&) {
            if(_hoursCounters){
                delete [] _hoursCounters;
            }
        }
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
        _totalSum--;
    }
    }
    unsigned int getTotalSum(){
        return _totalSum;
    }
};


#endif //DSWET1SHAY_HOURSANDCOUNTERS_H
