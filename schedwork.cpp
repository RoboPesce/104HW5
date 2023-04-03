#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

bool workerInDay(const Day& day, Worker_T worker);

bool scheduleBuilder(size_t day, size_t worker_ind, DailySchedule& sched, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts);

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

    // default day for schedule initialization 
    // (removes the need for 1 extra loop :))
    Day default_day(dailyNeed, INVALID_ID);
    // expand schedule to allow iteration
    // number of days = avail.size()
    sched.resize(avail.size(), default_day);

    return scheduleBuilder(0, 0, sched, avail, dailyNeed, maxShifts);    
}

bool scheduleBuilder(size_t day, size_t worker_ind, DailySchedule& sched, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts)
{
    if(day == avail.size()) return true;

    size_t next_day = day;
    size_t next_worker_ind = worker_ind + 1;
    if(next_worker_ind == dailyNeed)
    {
        next_worker_ind = 0;
        next_day++;
    }

    // we can start at worker_ind instead of 0 because by the time we get to
    // checking the worker_ind'th slot to fill, we will have tried at least
    // the first worker_ind # of workers. saves just a little time and energy
    for(Worker_T worker = worker_ind; worker < avail[day].size(); worker++)
    {
        // check if worker is available that day
        if(avail[day][worker] == 0) continue;

        // check if worker has already worked that day
        if(workerInDay(sched[day], worker)) continue;

        // check how many shifts the worker has done already
        if(day >= 1) // prevent error with unsigned 0 - 1 != -1
        {
            unsigned int shift_count = 0;
            for(size_t pday = 0; pday < day; pday++) if(workerInDay(sched[pday], worker)) shift_count++;
            if(shift_count >= maxShifts) continue;
        }

        // if we made it here, worker is valid for now
        sched[day][worker_ind] = worker;
        if (scheduleBuilder(next_day, next_worker_ind, sched, avail, dailyNeed, maxShifts)) 
            return true;
    }

    sched[day][worker_ind] = INVALID_ID;
    
    return false;
}

bool workerInDay(const Day& day, Worker_T worker)
{
    for(size_t i = 0; i < day.size(); i++) 
    {
        if(day[i] == worker) return true;
        if(day[i] == INVALID_ID) return false;
    }
    return false;
}