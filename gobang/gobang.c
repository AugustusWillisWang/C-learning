#include "lazy.h"
#define BOUNDRY 19
#define BLACK 1
#define WHITE 2
#define NORMAL 0
#define CLEAR 1

#define TEST          \
    ManualSetUpAll(); \
    JudgeWin();

int board[BOUNDRY][BOUNDRY];
int printboard[BOUNDRY][BOUNDRY];

int PvpMode();
int PveMode();
int SocketMode();     //与其他程序进行无人值守对战用
int SetUpBoard();     //初始化棋盘
int PrintBoard();     //显示棋盘
int ShowBoardArray(); //简单显示棋盘
int JudgeWin();       //判断胜利,若有一方胜利返回对应的color,否则返回0
int JudgeWinPlus();   //判断胜利,若有一方胜利返回对应的color,否则返回0,简化后的未测试代码
int GenWeight();      //产生权重
int MakeMove();       //电脑落子
int Abs();
int ManualSetUpAll();    //手动设置当前棋盘(调试用)
int ManualSetUp();       //手动设置当前棋盘某一位置(调试用)(pvp用)
int ForcedManualSetUp(); //手动设置当前棋盘某一位置(调试用)(无限制修改)
int _Tester();           //判断胜负时使用的子函数
int Save();              //保存当前操作到棋谱
int InitializeSaving();  //初始化保存文件

int main(int argc, char *argv[])
{
    SetUpBoard();
    int mode_choosed;
    if (argc == 1)
    {
        puts("--------------------------------------");
        LICENSE;
        puts("");
        puts("Run without parameter.");
        puts("Tips: you can also run this program with paramter. ");
        puts("Please choose game mode. 1:pvp 2:pve 3: pevpe 4:test 0:exit");
        scanf("%d", &mode_choosed);
        // fflush(stdin);//windows
        setbuf(stdin, NULL); //For all OSs, clear buf to eat \n
    }
    else
    {
        mode_choosed = atoi(argv[1]);
    }

    switch (mode_choosed)
    {
    case 1:
        PvpMode();
        break;
    case 2:
        PveMode();
        break;
    case 3:
        SocketMode();
        break;
    case 4:
        TEST
            BP;
        break;
    case 0:
        exit(0);
    default:
        // puts("Invaild input, please input again.");
        // break;
        puts("Use test mode as default.");
        TEST;
        BP;
    }
    puts("Gobang.c finished successfully.");
}

int PvpMode()
{
    int a;
    int b;
    int movecnt = 1;
    int colornow = BLACK;
    while (!JudgeWin())
    {
        for (int i = 0; i < 10; i++)
            puts("");
        LICENSE;
        puts("------------------------------------------");
        puts("This is pvp mode.");
        puts("The board now is:");
        ShowBoardArray();
        puts("------------------------------------------");
        printf("This is move %d.\n", movecnt);
        printf("Turn for the %s side.\n", (colornow == BLACK ? "black" : "white"));
        puts("Please input your coordinate, the format is like \"a b\"");
        printf("a,b ranges from 0 to %d\n", BOUNDRY - 1);
        scanf("%d%d", &a, &b);
        while (ManualSetUp(a, b, colornow))
            scanf("%d%d", &a, &b);
        ;
        movecnt++;
        if (colornow == BLACK)
        {
            colornow = WHITE;
        }
        else
        {
            colornow = BLACK;
        }
    }
    printf("Game finished in move %d.\n", movecnt);
    puts("--------------------------------------");
    ShowBoardArray();
    puts("--------------------------------------");

    BP;
    return 0;
}

int PveMode()
{
    int a;
    int b;
    int movecnt = 1;
    int colornow = BLACK;

    for (int i = 0; i < 10; i++)
        puts("");
    LICENSE;
    puts("------------------------------------------");
    puts("This is pve mode.");
    puts("Please choose your side: 1 for the black and 2 for the white");
    int player;
    scanf("%d", &player);
    while (player != 1 || player != 2)
    {
        puts("Wrong input!\nPlease choose your side: 1 for the black and 2 for the white");
        scanf("%d", &player);
    }
    setbuf(stdin, NULL); //For all OSs, clear buf to eat \n

    while (!JudgeWin())
    {
        for (int i = 0; i < 10; i++)
            puts("");
        LICENSE;
        puts("------------------------------------------");
        puts("This is pve mode.");
        puts("The board now is:");
        ShowBoardArray();
        puts("------------------------------------------");
        printf("This is move %d.\n", movecnt);
        printf("Turn for the %s side.\n", (colornow == BLACK ? "black" : "white"));
        puts("Please input your coordinate, the format is like \"a b\"");
        printf("a,b ranges from 0 to %d\n", BOUNDRY - 1);
        scanf("%d%d", &a, &b);
        while (ManualSetUp(a, b, colornow))
            scanf("%d%d", &a, &b);
        ;
        movecnt++;
        if (colornow == BLACK)
        {
            colornow = WHITE;
        }
        else
        {
            colornow = BLACK;
        }
    }
    printf("Game finished in move %d.\n", movecnt);
    puts("--------------------------------------");
    ShowBoardArray();
    puts("--------------------------------------");

    BP;
    return 0;
}

int SocketMode()
{
    BP;
    return 0;
}

int SetUpBoard()
{
    memset(board, 0, sizeof(int) * BOUNDRY * BOUNDRY);
    return 0;
}

int PrintBoard()
{
    // ┠ ┨┯ ┷┏┓┗ ┛┳⊥﹃﹄┌ ┐└ ┘∟
    return 0;
}

int ShowBoardArray()
{
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            printf("%d ", board[a][b]);
        }
        printf("\n");
    }
    printf("\n");
    // CP;
    // printf("-----------------------------------------------------\n");
    return 0;
}

int JudgeWin()
{
    //判断胜利,应该是最高效的算法了
    //第一次写的有点丑
    int color = 0;
    int cnt = 0;
    int max = 0;
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            switch (color)
            {
            case 0:
                if (board[a][b] == WHITE)
                {
                    color = WHITE;
                    cnt++;
                    if (cnt > max)
                        max = cnt;
                }
                else if (board[a][b] == BLACK)
                {
                    color = BLACK;
                    cnt++;
                    if (cnt > max)
                        max = cnt;
                }
                break;
            case BLACK:
                if (board[a][b] == WHITE)
                {
                    color = WHITE;
                    cnt = 1;
                    if (cnt > max)
                        max = cnt;
                }
                else if (board[a][b] == BLACK)
                {
                    color = BLACK;
                    cnt++;
                    if (cnt > max)
                        max = cnt;
                }
                else if (board[a][b] == 0)
                {
                    color = 0;
                    cnt = 0;
                    if (cnt > max)
                        max = cnt;
                }
                break;
            case WHITE:
                if (board[a][b] == WHITE)
                {
                    color = WHITE;
                    cnt++;
                    if (cnt > max)
                        max = cnt;
                }
                else if (board[a][b] == BLACK)
                {
                    color = BLACK;
                    cnt = 1;
                    if (cnt > max)
                        max = cnt;
                }
                else if (board[a][b] == 0)
                {
                    color = 0;
                    cnt = 0;
                    if (cnt > max)
                        max = cnt;
                }
                break;
            }
            if (max == 5)
            {
                if (color == WHITE)
                {
                    printf("White wins!\n");
                }
                else if (color == BLACK)
                {
                    printf("Black wins!\n");
                }
                return color;
            }
        }
        max = 0;
        cnt = 0;
        color = 0;
    }
    //row
    color = 0;
    cnt = 0;
    max = 0;
    for (int b = 0; b < BOUNDRY; b++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            switch (color)
            {
            case 0:
                if (board[a][b] == WHITE)
                {
                    color = WHITE;
                    cnt++;
                    if (cnt > max)
                        max = cnt;
                }
                else if (board[a][b] == BLACK)
                {
                    color = BLACK;
                    cnt++;
                    if (cnt > max)
                        max = cnt;
                }
                break;
            case BLACK:
                if (board[a][b] == WHITE)
                {
                    color = WHITE;
                    cnt = 1;
                    if (cnt > max)
                        max = cnt;
                }
                else if (board[a][b] == BLACK)
                {
                    color = BLACK;
                    cnt++;
                    if (cnt > max)
                        max = cnt;
                }
                else if (board[a][b] == 0)
                {
                    color = 0;
                    cnt = 0;
                    if (cnt > max)
                        max = cnt;
                }
                break;
            case WHITE:
                if (board[a][b] == WHITE)
                {
                    color = WHITE;
                    cnt++;
                    if (cnt > max)
                        max = cnt;
                }
                else if (board[a][b] == BLACK)
                {
                    color = BLACK;
                    cnt = 1;
                    if (cnt > max)
                        max = cnt;
                }
                else if (board[a][b] == 0)
                {
                    color = 0;
                    cnt = 0;
                    if (cnt > max)
                        max = cnt;
                }
                break;
            }
            if (max == 5)
            {
                if (color == WHITE)
                {
                    printf("White wins!\n");
                }
                else if (color == BLACK)
                {
                    printf("Black wins!\n");
                }
                return color;
            }
        }
        max = 0;
        cnt = 0;
        color = 0;
    }
    //dig2
    color = 0;
    cnt = 0;
    max = 0;
    for (int aplusb = 0; aplusb < 2 * (BOUNDRY - 1); aplusb++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = aplusb - a;
            if (b >= 0 && b < BOUNDRY)
            {
                switch (color)
                {
                case 0:
                    if (board[a][b] == WHITE)
                    {
                        color = WHITE;
                        cnt++;
                        if (cnt > max)
                            max = cnt;
                    }
                    else if (board[a][b] == BLACK)
                    {
                        color = BLACK;
                        cnt++;
                        if (cnt > max)
                            max = cnt;
                    }
                    break;
                case BLACK:
                    if (board[a][b] == WHITE)
                    {
                        color = WHITE;
                        cnt = 1;
                        if (cnt > max)
                            max = cnt;
                    }
                    else if (board[a][b] == BLACK)
                    {
                        color = BLACK;
                        cnt++;
                        if (cnt > max)
                            max = cnt;
                    }
                    else if (board[a][b] == 0)
                    {
                        color = 0;
                        cnt = 0;
                        if (cnt > max)
                            max = cnt;
                    }
                    break;
                case WHITE:
                    if (board[a][b] == WHITE)
                    {
                        color = WHITE;
                        cnt++;
                        if (cnt > max)
                            max = cnt;
                    }
                    else if (board[a][b] == BLACK)
                    {
                        color = BLACK;
                        cnt = 1;
                        if (cnt > max)
                            max = cnt;
                    }
                    else if (board[a][b] == 0)
                    {
                        color = 0;
                        cnt = 0;
                        if (cnt > max)
                            max = cnt;
                    }
                    break;
                }
                if (max == 5)
                {
                    if (color == WHITE)
                    {
                        printf("White wins!\n");
                    }
                    else if (color == BLACK)
                    {
                        printf("Black wins!\n");
                    }
                    return color;
                }
            }
        }
        max = 0;
        cnt = 0;
        color = 0;
    }

    //dig1
    color = 0;
    cnt = 0;
    max = 0;
    for (int aminusb = -(BOUNDRY - 1); aminusb < (BOUNDRY - 1); aminusb++)
    {
        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = a - aminusb;
            if (b >= 0 && b < BOUNDRY)
            {
                switch (color)
                {
                case 0:
                    if (board[a][b] == WHITE)
                    {
                        color = WHITE;
                        cnt++;
                        if (cnt > max)
                            max = cnt;
                    }
                    else if (board[a][b] == BLACK)
                    {
                        color = BLACK;
                        cnt++;
                        if (cnt > max)
                            max = cnt;
                    }
                    break;
                case BLACK:
                    if (board[a][b] == WHITE)
                    {
                        color = WHITE;
                        cnt = 1;
                        if (cnt > max)
                            max = cnt;
                    }
                    else if (board[a][b] == BLACK)
                    {
                        color = BLACK;
                        cnt++;
                        if (cnt > max)
                            max = cnt;
                    }
                    else if (board[a][b] == 0)
                    {
                        color = 0;
                        cnt = 0;
                        if (cnt > max)
                            max = cnt;
                    }
                    break;
                case WHITE:
                    if (board[a][b] == WHITE)
                    {
                        color = WHITE;
                        cnt++;
                        if (cnt > max)
                            max = cnt;
                    }
                    else if (board[a][b] == BLACK)
                    {
                        color = BLACK;
                        cnt = 1;
                        if (cnt > max)
                            max = cnt;
                    }
                    else if (board[a][b] == 0)
                    {
                        color = 0;
                        cnt = 0;
                        if (cnt > max)
                            max = cnt;
                    }
                    break;
                }
                if (max == 5)
                {
                    if (color == WHITE)
                    {
                        printf("White wins!\n");
                    }
                    else if (color == BLACK)
                    {
                        printf("Black wins!\n");
                    }
                    return color;
                }
            }
        }
        max = 0;
        cnt = 0;
        color = 0;
    }
}

int GenWeight()
{
    //产生权重
}

int MakeMove()
{
    //电脑落子
}

int Abs(int input)
{
    if (input < 0)
    {
        input = -input;
    }
    return input;
}

int ManualSetUpAll() //手动设置当前棋盘(调试用)
{
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            scanf("%d", &board[a][b]);
        }
    }
    setbuf(stdin, NULL); //For all OSs, clear buf to eat \n
    puts("Setup the board manually to:");
    ShowBoardArray();
    return 0;
}

int ManualSetUp(int a, int b, int color) //手动设置当前棋盘某一位置(调试用)
{
    if (a >= 0 && a < BOUNDRY && b >= 0 && b < BOUNDRY && (color == 0 || color == BLACK || color == WHITE))
    {
        if (board[a][b] != 0)
        {
            puts("Wrong input, please input again!");
            return -1;
        }
        board[a][b] = color;
        return 0;
    }
    puts("Wrong input, please input again!");
    return -1;
}

int ForcedManualSetUp(int a, int b, int color) //手动设置当前棋盘某一位置(调试用)(无视规则)
{
    if (a >= 0 && a < BOUNDRY && b >= 0 && b < BOUNDRY && (color == 0 || color == BLACK || color == WHITE))
    {
        board[a][b] = color;
        return 0;
    }
    puts("Wrong input, setup failed!");
    return -1;
}

int _Tester(int a, int b, int mode) //if mode==CLEAR, set cnt,max,color=0
{
    static int cnt;
    static int max;
    static int color;
    if (mode == CLEAR)
    {
        cnt = 0;
        max = 0;
        color = 0;
    }
    switch (color)
    {
    case 0:
        if (board[a][b] == WHITE)
        {
            color = WHITE;
            cnt++;
            if (cnt > max)
                max = cnt;
        }
        else if (board[a][b] == BLACK)
        {
            color = BLACK;
            cnt++;
            if (cnt > max)
                max = cnt;
        }
        break;
    case BLACK:
        if (board[a][b] == WHITE)
        {
            color = WHITE;
            cnt = 1;
            if (cnt > max)
                max = cnt;
        }
        else if (board[a][b] == BLACK)
        {
            color = BLACK;
            cnt++;
            if (cnt > max)
                max = cnt;
        }
        else if (board[a][b] == 0)
        {
            color = 0;
            cnt = 0;
            if (cnt > max)
                max = cnt;
        }
        break;
    case WHITE:
        if (board[a][b] == WHITE)
        {
            color = WHITE;
            cnt++;
            if (cnt > max)
                max = cnt;
        }
        else if (board[a][b] == BLACK)
        {
            color = BLACK;
            cnt = 1;
            if (cnt > max)
                max = cnt;
        }
        else if (board[a][b] == 0)
        {
            color = 0;
            cnt = 0;
            if (cnt > max)
                max = cnt;
        }
        break;
    }
    if (max == 5)
    {
        if (color == WHITE)
        {
            printf("White wins!\n");
        }
        else if (color == BLACK)
        {
            printf("Black wins!\n");
        }
        return color;
    }
}

int JudgeWinPlus()
{
    //判断胜利,应该是最高效的算法了
    //使用static简化了代码

    for (int a = 0; a < BOUNDRY; a++)
    {
        int mark = CLEAR;
        for (int b = 0; b < BOUNDRY; b++)
        {
            _Tester(a, b, mark);
            mark = NORMAL;
        }
    }
    for (int b = 0; b < BOUNDRY; b++)
    {
        int mark = CLEAR;
        for (int a = 0; a < BOUNDRY; a++)
        {
            _Tester(a, b, mark);
            mark = NORMAL;
        }
    }
    for (int aplusb = 0; aplusb < 2 * (BOUNDRY - 1); aplusb++)
    {
        int mark = CLEAR;

        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = aplusb - a;
            if (b >= 0 && b < BOUNDRY)
            {
                _Tester(a, b, mark);
                mark = NORMAL;
            }
        }
    }
    for (int aminusb = -(BOUNDRY - 1); aminusb < (BOUNDRY - 1); aminusb++)
    {
        int mark = CLEAR;

        for (int a = 0; a < BOUNDRY; a++)
        {
            int b = a - aminusb;
            if (b >= 0 && b < BOUNDRY)
            {
                _Tester(a, b, mark);
                mark = NORMAL;
            }
        }
    }
}

int Save();             //保存当前操作到棋谱
int InitializeSaving(); //初始化保存文件

/*
测试用例 棋盘

0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 2 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 1 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 1 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
*/

/*
测试用例 棋谱

0 0
9 0
1 % 0
10   0
2 0 
   11 0
3 0
19 19
12 0
4 0
14 0 
5 0

*/