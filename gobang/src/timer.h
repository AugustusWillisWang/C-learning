// Copyright (c) 2017-2018 Augustus Wang
//函数计时器, 分析调用开销用
#ifndef _TIMER_H
#define _TIMER_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#define TIMERWIDTH 10 //时间计数数组上限



#ifdef TIMEIT
long long _time_total[TIMERWIDTH];
long long _time_start[TIMERWIDTH];
int _time_incnt[TIMERWIDTH];

//Cpp写法, 调用汇编语言实现精确计时
// unsigned __int64 GetCycleCount()
// {
//     __asm
//     {
//         _emit 0x0F;
//         _emit 0x31;
//     }
// }

//使用 Windows Api: QueryPerformanceCounter() 实现按cpu周期的精确计时
int StartTimer(int function_index)//开启编号为function_index的计时器
{

    // _time_start[function_index] = clock();
    QueryPerformanceCounter(&_time_start[function_index]);
    _time_incnt[function_index] = 1;
}

int EndTimer(int function_index)//停止编号为function_index的计时器
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

int ShowTimer()//显示当前计数结果
{
    for (int i = 0; i < TIMERWIDTH; i++)
    {
        if (_time_total[i] != 0)
            printf("func%d: %d\n", i,_time_total[i]);
    }
}

int ClearTimer()//清空计数器
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