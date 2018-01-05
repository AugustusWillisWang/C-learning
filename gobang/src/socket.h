// Copyright (c) 2017-2018 Augustus Wang
#ifndef _SOCKET_H
#define _SOCKET_H
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// #include <windows.h> //windows
// #include <unistd.h>  //linux

//---------------------
//usage:

struct position
{
    int a;
    int b;
};

// computer color: black --> InitializeSocket(1);
// computer color: white --> InitializeSocket(2);
int InitializeSocket(int color);

struct position Transfer(int a, int b);

//------------------------------------

//For windows:

// void _Wait(int waittime)
// {
//     Sleep(waittime);
// }

//For linux:

// void _Wait(int waittime)
// {
//      sleep(waittime);
// }

void _Wait(int waittime)
{
    clock_t endwait;
    endwait = clock() + waittime;
    while (clock() < endwait)
    {
        ;
    }
}

int _RandTime()
{
    return rand() % 50;
}


// BLACK==1;
// WHITE==2;

int _fststep = 0;
int _color = 0;
FILE *_exchangefile;

int InitializeSocket(int color)
{
    _color = color;
    if (color == 1)
    {
        _exchangefile = fopen("swapfile", "w");
        fclose(_exchangefile);
    }
    return 0;
}

int _InvColor(int i)
{
    if (i == 1)
        return 2;
    if (i == 2)
    {
        return 1;
    }
    puts("Invalid socket call!");
}

struct position Transfer(int a, int b)
{
    int col = 0;
    struct position position;
    if (_color == 2 && _fststep == 0)
    {
        do
        {
            while (!(_exchangefile = fopen("swapfile", "r")))
                _Wait(_RandTime());
            fscanf(_exchangefile, "%d %d %d", &position.a, &position.b, &col);
            fclose(_exchangefile);
            _Wait(_RandTime());
            

        } while (col != _InvColor(_color));
        // fclose(_exchangefile);
        _fststep = 1;
        return position;
    }

    _exchangefile = fopen("swapfile", "w");
    fprintf(_exchangefile, "%d %d %d", a, b, _color);
    fclose(_exchangefile);

    do
    {
        while (!(_exchangefile = fopen("swapfile", "r")))
            _Wait(_RandTime());
        fscanf(_exchangefile, "%d %d %d", &position.a, &position.b, &col);
        fclose(_exchangefile);
        _Wait(_RandTime());

    } while (col != _InvColor(_color));
    fclose(_exchangefile);

    return position;
}

int CloseSocket()
{
    system("del swapfile");
}

    // int SocketMain(int a, int b, int color);

#endif