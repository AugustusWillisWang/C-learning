//Copyright (c) 2017-2018 Augustus Wang
//charlib.h
//处理用户输入输出的文本

#ifndef CHARLIB
#define CHARLIB
#include <ctype.h>
#include <stdio.h>

#define BUFFSIZE 100

char _inputbuff[BUFFSIZE];

int AdvancedScanf(int *ra, char *rb)//将用户输入的(10,A)转化成board数组中的坐标
{
    fgets(_inputbuff, BUFFSIZE, stdin);
    for (int i = 0; i < BUFFSIZE; i++)
    {
        if (_inputbuff[i] == '\n')
            _inputbuff[i] = '\0';
    }
    if (!strcmp(_inputbuff, "quit"))
        exit(0);
    int i = 0;
    int num = 0;
    char alpha = 0;
    while (_inputbuff[i] != '\0')
    {
        if(isalpha(_inputbuff[i])){
            if (alpha)
            {
                puts("More than 1 alpha!\n");
                alpha = 1;
                return -1;
            }
            else
            {
                alpha = _inputbuff[i];
            }
        }
        if(isdigit(_inputbuff[i])){
            num = num * 10 + _inputbuff[i] - '0';
        }
        i++;
    }
    *ra = num;
    *rb = alpha;
}

//--------------------------------------

char *DelSpaceAddLog(char *input)//为自动生成的棋谱文件命名用
{
    int a = 0;
    int b = 0;
    char *output = (char *)malloc(sizeof(char) * (strlen(input) + 5));
    while (input[a] != '\n')
    {
        if (input[a] != ' ' && input[a] != ':')
        {
            output[b] = input[a];
            b++;
        }
        a++;
    }
    output[b++] = '.';
    output[b++] = 'l';
    output[b++] = 'o';
    output[b++] = 'g';
    output[b++] = '\0';
    return output;
}

#endif