//Copyright (c) 2017-2018 Augustus Wang
//自注释风格的函数和变量名命名, 应该不用太多注释....
//主程序
#define TIMEIT
#define TEST
#include "timer.h"          //性能分析, 计时相关
#include "support.h"        //棋盘定义, 数据结构定义, 基础情况判断以及其他共用部分, 写成头文件以方便单元测试
#include "forbidden_move.h" //禁手判断

#include "algo_basic.h"  //大猩猩下棋
#include "algo_linear.h" //一层两岁小孩下棋(别看了, 没用的, 注释也不存在的)
#include "algo_point.h"  //一层三岁小孩下棋(别看了, 没用的, 注释也不存在的)
// #include "algo_final.h"//Alphabet剪枝加各种优化
#include "algo_rebuild.h" //Alphabet剪枝加各种优化(重构) (算法核心)
#include "printboard.h"   //显示棋盘所用的函数
#include "socket.h"       //自动对战接口定义

//支持:
//禁手判断
//棋谱保存

//使用了以下算法:
//AlphaBeta剪枝
//zobrist hash 置换表
//历史启发搜索
//迭代加深搜索
//只针对改变部分的快速局面评分函数

//同步进行胜手优先搜索(没开)
//贪心启发搜索搜索(没开)

//因为使用多线程会导致跨平台出现麻烦, 所以并没有考虑多线程算法
//否则, 可以同时开启VCF, 并将基本的AlphaBeta剪枝替换成极小窗口搜索来多线程执行

//若没有特别说明, int形的函数表示一个操作的, 如 SetUpBoard()返回0代表正常执行. 名如 Weight()的函数会返回名称所对应的值. 形如 Is_Tested()为真时返回1, 否则返回0
//有特殊返回值的函数会另行说明

//程序在windows10下使用gcc编译通过
/*
Todo:
// 调整hash表
// 通过棋盘变化赋权
补注释
// _Judgewin
// _StartTimer(4)
*/

int Algo_Choosed = ALGO_BASIC; //默认使用算法Random
int player = 0;

FILE *log_file; //初始化日志文件指针

int PvpMode();    //人人主程序
int PveMode();    //人机主程序
int SocketMode(); //与其他程序进行无人值守对战用
int SetUpBoard(); //初始化棋盘
int PrintBoard(); //显示棋盘
int JudgeWin();   //判断胜利,若有一方胜利返回对应的color,否则返回0
// int JudgeWinOriginal();  //判断胜利,若有一方胜利返回对应的color,否则返回0,第一次写的垃圾代码
// int JudgeWinPlus();      //判断胜利,若有一方胜利返回对应的color,否则返回0,简化后的未测试代码
int GenWeight();         //产生权重
int MakeMove();          //电脑落子
int Abs();               //绝对值
int ManualSetUpAll();    //手动设置当前棋盘(调试用)
int ManualSetUp();       //手动设置当前棋盘某一位置(调试用)(pvp用)
int ForcedManualSetUp(); //手动设置当前棋盘某一位置(调试用)(无限制修改)
int _Tester();           //判断胜负时使用的子函数
int Save();              //保存当前操作到棋谱
int DisplayLog();        //显示棋谱

FILE *InitializeSaving(); //初始化保存文件
int main(int argc, char *argv[])
{
    //初始化棋盘
    SetUpBoard();

    //mode选择

    int mode_choosed;
    char log_name[30];
    if (argc == 1)
    {
        puts("--------------------------------------");
        LICENSE;
        puts("");
        puts("Run without parameter.");
        puts("Tips: you can also run this program with paramter. ");
        puts("-p pvp, -e pve, -b human uses black, -w human uses white, -r read log, -1, -2, -3, -s,-auto, -test, etc. \n");
        puts("Please choose game mode. 1:pvp 2:pve 3: unusedfunction 4:test 5:display log 0:exit");
        scanf("%d", &mode_choosed);
        // fflush(stdin);//windows
        setbuf(stdin, NULL); //For all OSs, clear buf to eat \n
    }
    else //参数处理
    {
        while (--argc)
        {
            argv++;
            if (!strcmp(*argv, "-p"))
            {
                mode_choosed = 1; //pvpmode
                puts("mode_choosed = 1");
                continue;
            }
            if (!strcmp(*argv, "-e"))
            {
                mode_choosed = 2; //pvemode
                puts("mode_choosed = 2");
                continue;
            }
            if (!strcmp(*argv, "-auto"))
            {
                mode_choosed = 3; //自动对战模式
                puts("mode_choosed = 3");

                continue;
            }
            if (!strcmp(*argv, "-test")) //测试模式
            {
                mode_choosed = 4;
                puts("mode_choosed = 4");

                continue;
            }
            if (!strcmp(*argv, "-b")) //玩家执黑
            {
                player = BLACK;
                puts("player = BLACK");
                continue;
            }
            if (!strcmp(*argv, "-w")) //玩家执白
            {
                player = WHITE;
                puts("player = WHITE");
                continue;
            }
            if (!strcmp(*argv, "-r")) //读取日志
            {
                --argc;
                ++argv;
                memcpy(log_name, *argv, 30);
                goto showlog;
                continue;
            }
            if (!strcmp(*argv, "-1")) //选择算法1
            {
                Algo_Choosed = 1;
                puts("Algo_Choosed = 1");

                continue;
            }
            if (!strcmp(*argv, "-2")) //选择算法2
            {
                Algo_Choosed = 2;
                puts("Algo_Choosed = 2");

                continue;
            }
            if (!strcmp(*argv, "-3")) //选择算法3
            {
                Algo_Choosed = 3;
                puts("Algo_Choosed = 3");

                continue;
            }
            if (!strcmp(*argv, "-s")) //测试用
            {
                _usesimpletest = 1;
                puts("_usesimpletest=1");

                continue;
            }
            if (!strcmp(*argv, "-log")) //此次对战保留日志(默认不保存)
            {
                set_savelog = 1;
                puts("set_savelog=1");

                continue;
            }
        }
    }

    switch (mode_choosed)
    {
    case 1:
        log_file = InitializeSaving(); //初始化日志
        PvpMode();
        break;
    case 2:
        log_file = InitializeSaving();
        PveMode();
        break;
    case 3:
        log_file = InitializeSaving();
        SocketMode();
        break;
    case 4:
        log_file = InitializeSaving();
#ifdef TEST
#include "test.h" //在TEST模式下, 直接执行test.h里的语句 只要在头文件中定义宏TEST
#endif
        BP;
        break;
    case 5:
    {
        fgets(log_name, 30, stdin); //日志读取, 不是必需的部分就不详注了
    showlog:
        log_file = fopen(log_name, "r");
        DisplayLog();
        break;
    }
    case 0:
        exit(0);
    default:
        // puts("Invaild input, please input again.");
        // break;
        puts("Use test mode as default.");
        TEST;
        BP;
    }
    fflush(log_file); //write log.
    fclose(log_file); //close log.
    puts("Gobang.c finished successfully.");
}

int PvpMode() //人人对战
//自注释风格的函数和变量名命名, 应该不用太多注释....
{
    int a;
    int b;
    int movecnt = 1;
    colornow = BLACK;
    while (!JudgeWin())
    {
        clearscreen();
        LICENSE;
        puts("------------------------------------------");
        puts("This is pvp mode.");
        puts("The board now is:");
        PrintBoard();
        // ShowBoardArray();
        puts("------------------------------------------");
        printf("This is move %d.\n", movecnt);
        printf("Turn for the %s side.\n", (colornow == BLACK ? "black" : "white"));
        puts("Please input your coordinate, the format is like \"10 A\"");
        printf("a,b ranges from 0 to %d\n", BOUNDRY - 1);
        // scanf("%d%d", &a, &b);
        getinput(&a, &b);

#ifdef ENABLEFBDMOVE
        while (TestTipForbidMove(a, b, colornow) || ManualSetUp(a, b, colornow))
            // scanf("%d%d", &a, &b);
            getinput(&a, &b);
#else
        while (ManualSetUp(a, b, colornow))
            // scanf("%d%d", &a, &b);
            getinput(&a, &b);
#endif
        Save(a, b);
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
    // ShowBoardArray();
    PrintBoard();
    puts("--------------------------------------");

    BP;
    return 0;
}

int PveMode() //人机对战
{
    int a;
    int b;
    int movecnt = 1;
    int computermove = 0;

    colornow = BLACK;

    clearscreen();
    LICENSE;
    puts("------------------------------------------");
    puts("This is pve mode.");
    puts("Please choose the Algo: 0 for Random, 1 for ALGO_LINEAR, 2 for ALGO_POINT, 3 for ALGO_AlphaBeta");
    if (ALGO_BASIC == Algo_Choosed)
        scanf("%d", &Algo_Choosed);
    puts("Please choose your side: 1 for the black and 2 for the white");
    if (0 == player)
        scanf("%d", &player);
    while (player != 1 && player != 2)
    {
        puts("Wrong input!\nPlease choose your side: 1 for the black and 2 for the white");
        scanf("%d", &player);
    }

    if (player == 1)
    {
        computermove = WHITE;
    }
    else
    {
        computermove = BLACK;
    }

    setbuf(stdin, NULL); //For all OSs, clear buf to eat \n (清理缓冲区以避免之前错误输入的影响)

    while (!JudgeWin())
    {
        if (colornow != computermove)
        {
            clearscreen();
            LICENSE;
            puts("------------------------------------------");
            puts("This is pve mode.");
            puts("The board now is:");
            // ShowBoardArray();
            PrintBoard();
            ShowMove(a, b, Inverse(colornow)); //顺便显示当前走子位置

            puts("------------------------------------------");
            printf("This is move %d.\n", movecnt);
            printf("Turn for the %s side.\n", (colornow == BLACK ? "black" : "white"));
            puts("Please input your coordinate, the format is like \"10 A\"");
            printf("a,b ranges from 0 to %d\n", BOUNDRY - 1);
            // scanf("%d%d", &a, &b);
            getinput(&a, &b);

#ifdef ENABLEFBDMOVE
            while (TestTipForbidMove(a, b, colornow) || ManualSetUp(a, b, colornow))
                // scanf("%d%d", &a, &b);
                getinput(&a, &b);
#else
            while (ManualSetUp(a, b, Inverse(colornow))
                // scanf("%d%d", &a, &b);
                getinput(&a, &b);
#endif
            ;
        }
        else
        {
            clearscreen();
            LICENSE;
            puts("------------------------------------------");
            puts("This is pve mode.");
            puts("The board now is:");
            // ShowBoardArray();
            PrintBoard();
            ShowMove(a, b, colornow); //顺便显示当前走子位置

            puts("------------------------------------------");
            printf("This is move %d.\n", movecnt);
            printf("Turn for the %s side.\n", (colornow == BLACK ? "black" : "white"));
            // puts("Please input your coordinate, the format is like \"10 A\"");
            printf("a,b ranges from 0 to %d\n", BOUNDRY - 1);
            MakeMove(&a, &b);
            ManualSetUp(a, b, colornow);
        }
        // UpdatePositionWeight(a, b, colornow, greedy_matrix);
        UpdateThreat(a, b, colornow, colornow);
        DBG_ShowPWM(threat_martix);
        Save(a, b);
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
    // ShowBoardArray();
    PrintBoard();

    puts("--------------------------------------");

    BP;
    return 0;
}

int SocketMode() //无人值守自动对战模式, 使用的接口定义参见socket.h
{
    int a;
    int b;
    int movecnt = 1;
    int computermove = 0;

    colornow = BLACK;

    clearscreen();
    LICENSE;
    puts("------------------------------------------");
    puts("This is socket mode.");
    puts("Please choose the Algo: 0 for Random, 1 for ALGO_LINEAR, 2 for ALGO_POINT, 3 for ALGO_AlphaBeta");
    if (ALGO_BASIC == Algo_Choosed)
        scanf("%d", &Algo_Choosed);
    puts("Please choose your side: 1 for the black and 2 for the white");
    if (0 == player)
        scanf("%d", &player);
    while (player != 1 && player != 2)
    {
        puts("Wrong input!\nPlease choose your side: 1 for the black and 2 for the white");
        scanf("%d", &player);
    }

    if (player == 1)
    {
        computermove = WHITE;
    }
    else
    {
        computermove = BLACK;
    }
    InitializeSocket(computermove);
    setbuf(stdin, NULL); //For all OSs, clear buf to eat \n

    struct position position;
    while (!JudgeWin())
    {
        if (colornow != computermove)
        {
            position = Transfer(0, 0);
            clearscreen();
            LICENSE;
            puts("------------------------------------------");
            puts("This is socket mode.");
            puts("The board now is:");
            // ShowBoardArray();
            PrintBoard();

            puts("------------------------------------------");
            printf("This is move %d.\n", movecnt);
            printf("Turn for the %s side.\n", (colornow == BLACK ? "black" : "white"));
            // puts("Please input your coordinate, the format is like \"10 A\"");
            // printf("a,b ranges from 0 to %d\n", BOUNDRY - 1);
            // scanf("%d%d", &a, &b);
            // position=Transfer(a, b);
            a = position.a;
            b = position.b;
            // getinput(&a, &b);

#ifdef ENABLEFBDMOVE
            if (TestTipForbidMove(a, b, colornow))
            {
                puts("Forbidden move detected!");
            }
#endif
        }
        else
        {
            clearscreen();
            LICENSE;
            puts("------------------------------------------");
            puts("This is socket mode.");
            puts("The board now is:");
            // ShowBoardArray();
            PrintBoard();

            puts("------------------------------------------");
            printf("This is move %d.\n", movecnt);
            printf("Turn for the %s side.\n", (colornow == BLACK ? "black" : "white"));
            MakeMove(&a, &b);
            position = Transfer(a, b);
            ManualSetUp(a, b, colornow);
        }
        Save(a, b);
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
    // ShowBoardArray();
    PrintBoard();

    puts("--------------------------------------");

    BP;
    return 0;
}

int SetUpBoard() //初始化棋盘记录数组
{
    memset(board, 0, sizeof(int) * BOUNDRY * BOUNDRY);
    return 0;
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
    PrintBoard();

    return 0;
}

int ManualSetUp(int a, int b, int color) //设置当前棋盘某一位置(程序用)
{
    if (a >= 0 && a < BOUNDRY && b >= 0 && b < BOUNDRY && (color == 0 || color == BLACK || color == WHITE))
    {
        if (board[a][b] != 0)
        {
            puts("Wrong input, please input again!");
            setbuf(stdin, NULL);
            return -1;
        }
        board[a][b] = color;
        _lastposia = a;
        _lastposib = b;
        return 0;
    }
    puts("Wrong input, please input again!");
    setbuf(stdin, NULL);
    return -1;
}

int ForcedManualSetUp(int a, int b, int color) //设置当前棋盘某一位置(调试用)
{
    if (a >= 0 && a < BOUNDRY && b >= 0 && b < BOUNDRY && (color == 0 || color == BLACK || color == WHITE))
    {
        board[a][b] = color;
        return 0;
    }
    puts("Wrong input, setup failed!");
    return -1;
}
int Save(int a, int b) //保存当前操作到棋谱
{
    fprintf(log_file, "%d %d\n", a, b);
}

int DisplayLog() //显示已有棋谱
{

    int a;
    int b;
    int movecnt = 1;
    colornow = BLACK;
    while (!JudgeWin())
    {
        fscanf(log_file, "%d %d", &a, &b);
        CK(a);
        CK(b);
        if (ManualSetUp(a, b, colornow))
        {
            puts("Wrong log format.");
            exit(-1);
        }
        // Save(a, b);

        clearscreen();

        LICENSE;
        puts("------------------------------------------");
        puts("This is display mode.");
        puts("The board now is:");
        // ShowBoardArray();
        PrintBoard();

        puts("------------------------------------------");
        printf("This is move %d.\n", movecnt);
        printf("Turn for the %s side.\n", (colornow == BLACK ? "black" : "white"));
        // puts("Please input your coordinate, the format is like \"a b\"");
        // printf("a,b ranges from 0 to %d\n", BOUNDRY - 1);

        movecnt++;
        if (colornow == BLACK)
        {
            colornow = WHITE;
        }
        else
        {
            colornow = BLACK;
        }
        puts("Press any key to continue.");
        getchar();
    }
    printf("Game finished in move %d.\n", movecnt - 1);
    puts("--------------------------------------");
    // ShowBoardArray();
    PrintBoard();

    puts("--------------------------------------");

    BP;
    return 0;
}

FILE *InitializeSaving() //初始化保存文件
{
    if (set_savelog)
    {
        time_t time_now;
        time_now = time(NULL);
        char *log_name = DelSpaceAddLog(ctime(&time_now));
        printf("Log file is saved at %s \n", log_name);
        log_file = fopen(log_name, "a+");
        // char log_name_str[] = ctime(&time_now);
        // log_file = fopen(log_name_str, "a");
        return log_file;
    }
    else
    {
        char *log_name = "tempfile";
        printf("No log is recquired.\n");
        log_file = fopen(log_name, "a+");
        // char log_name_str[] = ctime(&time_now);
        // log_file = fopen(log_name_str, "a");
        return log_file;
    }
}

int MakeMove(int *ap, int *bp) //人机对战算法调用函数, 通过不同的配置调用不同的算法
{
    switch (Algo_Choosed)
    {

#ifdef ALGO_BASIC

    case ALGO_BASIC:
        return AlgoBasic(ap, bp);
#endif
#ifdef ALGO_LINEAR

    case ALGO_LINEAR:
        return AlgoLinear(ap, bp);
#endif
#ifdef ALGO_POINT

    case ALGO_POINT:
        return AlgoPoint(ap, bp);
#endif
#ifdef ALGO_FINAL
    case ALGO_FINAL:
        return AlgoFinal(ap, bp);
#endif
#ifdef ALGO_REBUILD
    case ALGO_REBUILD:
        return AlgoRebuild(ap, bp);
#endif
    }
}