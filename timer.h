#ifndef _TIMER_H
#define _TIMER_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define TIMERWIDTH 10

#ifdef CLOCKS_PER_SEC
#undef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 10000000000000
#endif

#ifdef TIMEIT
long long _time_total[TIMERWIDTH];
long long _time_start[TIMERWIDTH];
int _time_incnt[TIMERWIDTH];

// unsigned __int64 GetCycleCount()
// {
//     __asm
//     {
//         _emit 0x0F;
//         _emit 0x31;
//     }
// }

int StartTimer(int function_index)
{

    // _time_start[function_index] = clock();
    QueryPerformanceCounter(&_time_start[function_index]);
    _time_incnt[function_index] = 1;
}

int EndTimer(int function_index)
{
    if (_time_incnt[function_index])
    {
        // _time_total[function_index] += (clock() - _time_start[function_index]);
        unsigned long int temp;
        QueryPerformanceCounter(&temp);
        _time_total[function_index] += (temp - _time_start[function_index]);
        _time_incnt[function_index] = 0;
    }
}

int ShowTimer()
{
    for (int i = 0; i < TIMERWIDTH; i++)
    {
        if (_time_total[i] != 0)
            printf("func%d: %d\n", i,_time_total[i]);
    }
}

int ClearTimer()
{
    memset(_time_total, 0, sizeof(_time_total));
    memset(_time_start, 0, sizeof(_time_start));
    memset(_time_incnt, 0, sizeof(_time_incnt));
}
#else

int StartTimer(int function_index){};
int EndTimer(int function_index){};
int ShowTimer(){};
int ClearTimer(){};

#endif

#endif