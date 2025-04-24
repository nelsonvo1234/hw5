#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    std::vector<int> numShift,
    DailySchedule& sched,
    int row, int col, int prev
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    for(int i = 0; i < avail.size(); i++){
        sched.push_back(std::vector<unsigned int>());
        for(int j = 0; j < dailyNeed; j++){
            sched[i].push_back(INVALID_ID);
        }
    }
    std::vector<int> numShift(avail[0].size());
    return scheduleHelper(avail, dailyNeed, maxShifts, numShift, sched, 0, 0, -1);
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    std::vector<int> numShift,
    DailySchedule& sched,
    int row, int col, int prev
)
{
    std::cout << "Running scheduleHelper" << std::endl;
    if(col >= dailyNeed){
        row += 1;
        col = 0;
        prev = -1;
        std::cout << "Next row" << std::endl;
    }
    if(row >= sched.size()){
        return true;
    }
    // Add your code below
    std::cout << "Starting for loop" << std::endl;
    for(int i = prev + 1; i < avail.size(); i++){
        if(avail[row][i] && numShift[i] < maxShifts){
            numShift[i]++;
            sched[row][col] = i;
            std::cout << i << std::endl;
            if(scheduleHelper(avail, dailyNeed, maxShifts, numShift, sched, row, col+1, i)){
                return true;
            }
            numShift[i]--;
        }
    }
    sched[row][col] = INVALID_ID;
    return false;
    



}

