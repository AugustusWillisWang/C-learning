#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "charlib.h"
#include"support.h"
// #define SIZE 15  //BOUNDRY
#define CHARSIZE 2
#define SIZE BOUNDRY
// void initRecordBorard(void);
// void recordtoDisplayArray(void);
// void displayBoard(void);

int clearscreen()
{
    // system("cls");
    // system("clear");
}

//����ʹ�õ���GBK���룬ÿһ�������ַ�ռ��2���ֽڡ�

//���̻���ģ�� 
char display_board_array[SIZE][SIZE*CHARSIZE+1] = 
{
		"���өөөөөөөөөөөөө�",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"���۩۩۩۩۩۩۩۩۩۩۩۩۩�"
};
//������������ʾ���� 
// char display_board_array[SIZE][SIZE*CHARSIZE+1];
 
char play1Pic[]="��";//������;
char play1CurrentPic[]="��"; 

char play2Pic[]="��";//������;
char play2CurrentPic[]="��";


int _lastposia = -1;
int _lastposib = -1;

int PrintBoard()
{
    // char display_board_array[BOUNDRY][BOUNDRY*CHARSIZE+1];

    // char play1Pic[]="��";//������;
    // char play1CurrentPic[]="��";

    // char play2Pic[]="��";//������;
    // char play2CurrentPic[]="��";

    //������������;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (board[a][b] == BLACK)
            {
                display_board_array[a][b * CHARSIZE] = play1Pic[0];
                display_board_array[a][b * CHARSIZE + 1] = play1Pic[1];
            }
            if (board[a][b] == WHITE)
            {
                display_board_array[a][b * CHARSIZE] = play2Pic[0];
                display_board_array[a][b * CHARSIZE + 1] = play2Pic[1];
            }
        }
    }
    //������һ��������λ��
    if (_lastposia >= 0 && _lastposia < BOUNDRY)
    {
        if (_lastposib >= 0 && _lastposib < BOUNDRY)
        {
            if (board[_lastposia][_lastposib] == BLACK)
            {
                display_board_array[_lastposia][_lastposib * CHARSIZE] = play1CurrentPic[0];
                display_board_array[_lastposia][_lastposib * CHARSIZE + 1] = play1CurrentPic[1];
            }
            if (board[_lastposia][_lastposib] == WHITE)
            {
                display_board_array[_lastposia][_lastposib * CHARSIZE] = play2CurrentPic[0];
                display_board_array[_lastposia][_lastposib * CHARSIZE + 1] = play2CurrentPic[1];
            }
        }
    }
    for (int a = 0; a < BOUNDRY; a++)
    {
        printf("%s %d\n", display_board_array[a], BOUNDRY - a);
    }
    printf("ABCDEFGHIJKLMNO\n");
    // ShowBoardArray();
}

//���scanf("%d%d", &a, &b);
int getinput(int *a, int *b)
{
    int ra;
    char rb;
    AdvancedScanf(&ra, &rb);
    // scanf("%d %c", &ra, &rb);
    // 15 B -> 0 1
    // CK(rb);
    CK(BOUNDRY - ra);
    CK((int)(rb - 'A'));
    *a = BOUNDRY - ra;

    *b = (int)(rb - 'A');
}