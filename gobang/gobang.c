// Copyright (c) 2017-2018 Augustus Wang 
#include "support.h"
#include "forbidden_move.h"

#include "algo_basic.h"
#include "algo_linear.h"
#include "algo_point.h"
#include "algo_final.h"
#include "printboard.h"

#define TEST              \
    ManualSetUp(1, 2, 1); \
    PrintBoard();

/*
Todo:

timer
board
point weight Gen
better algo
*/

int Algo_Choosed = ALGO_BASIC; //Ĭ��ʹ���㷨Random
int player = 0;

FILE *log_file; //��ʼ����־�ļ�ָ��

int PvpMode();    //����������
int PveMode();    //�˻�������
int SocketMode(); //�����������������ֵ�ض�ս��
int SetUpBoard(); //��ʼ������
int PrintBoard(); //��ʾ����
int JudgeWin();   //�ж�ʤ��,����һ��ʤ�����ض�Ӧ��color,���򷵻�0
// int JudgeWinOriginal();  //�ж�ʤ��,����һ��ʤ�����ض�Ӧ��color,���򷵻�0,��һ��д����������
// int JudgeWinPlus();      //�ж�ʤ��,����һ��ʤ�����ض�Ӧ��color,���򷵻�0,�򻯺��δ���Դ���
int GenWeight();         //����Ȩ��
int MakeMove();          //��������
int Abs();               //����ֵ
int ManualSetUpAll();    //�ֶ����õ�ǰ����(������)
int ManualSetUp();       //�ֶ����õ�ǰ����ĳһλ��(������)(pvp��)
int ForcedManualSetUp(); //�ֶ����õ�ǰ����ĳһλ��(������)(�������޸�)
int _Tester();           //�ж�ʤ��ʱʹ�õ��Ӻ���
int Save();              //���浱ǰ����������
int DisplayLog();        //��ʾ����

FILE *InitializeSaving(); //��ʼ�������ļ�


int main(int argc, char *argv[])
{

    //��ʼ������
    SetUpBoard();

    //modeѡ��
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
    else
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
                mode_choosed = 3;
                puts("mode_choosed = 3");
                
                continue;
            }
            if (!strcmp(*argv, "-test"))
            {
                mode_choosed = 4;
                puts("mode_choosed = 4");
                
                continue;
            }
            if (!strcmp(*argv, "-b"))
            {
                player = BLACK;
                puts("player = BLACK");                
                continue;
            }
            if (!strcmp(*argv, "-w"))
            {
                player = WHITE;
                puts("player = WHITE");                                
                continue;
            }
            if (!strcmp(*argv, "-r"))
            {
                --argc;
                ++argv;
                memcpy(log_name, *argv, 30);
                goto showlog;
                continue;
            }
            if (!strcmp(*argv, "-1"))
            {
                Algo_Choosed = 1;
                puts("Algo_Choosed = 1");                
                
                continue;
            }
            if (!strcmp(*argv, "-2"))
            {
                Algo_Choosed = 2;
                puts("Algo_Choosed = 2");                
                
                continue;
            }
            if (!strcmp(*argv, "-3"))
            {
                Algo_Choosed = 3;
                puts("Algo_Choosed = 3");                
                
                continue;
            }
            if (!strcmp(*argv, "-s"))
            {
                _usesimpletest=1;
                puts("_usesimpletest=1");                
                
                continue;
            }
            if (!strcmp(*argv, "-log"))
            {
                set_savelog=1;
                puts("set_savelog=1");                
                
                continue;
            }
        }
    }

    switch (mode_choosed)
    {
    case 1:
        log_file = InitializeSaving();
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
        TEST
            BP;
        break;
    case 5:
    {
        //= "SunOct290114402016xxxxxxxxxx.log"; //�̶�log_name����,��ע�ⲻҪ������10 31
        fgets(log_name, 30, stdin);
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

int PvpMode()
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

        while (TestTipForbidMove(a,b,colornow)||ManualSetUp(a, b, colornow))
            // scanf("%d%d", &a, &b);
            getinput(&a, &b);

        ;
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

int PveMode()
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

    setbuf(stdin, NULL); //For all OSs, clear buf to eat \n

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

            puts("------------------------------------------");
            printf("This is move %d.\n", movecnt);
            printf("Turn for the %s side.\n", (colornow == BLACK ? "black" : "white"));
            puts("Please input your coordinate, the format is like \"10 A\"");
            printf("a,b ranges from 0 to %d\n", BOUNDRY - 1);
            // scanf("%d%d", &a, &b);
            getinput(&a, &b);

            while (TestTipForbidMove(a,b,colornow)||ManualSetUp(a, b, colornow))
                // scanf("%d%d", &a, &b);
                getinput(&a, &b);

            ;
        }
        else
        {
            MakeMove(&a, &b);
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

int ManualSetUpAll() //�ֶ����õ�ǰ����(������)
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

int ManualSetUp(int a, int b, int color) //���õ�ǰ����ĳһλ��(������)
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

int ForcedManualSetUp(int a, int b, int color) //�ֶ����õ�ǰ����ĳһλ��(������)(���ӹ���)
{
    if (a >= 0 && a < BOUNDRY && b >= 0 && b < BOUNDRY && (color == 0 || color == BLACK || color == WHITE))
    {
        board[a][b] = color;
        return 0;
    }
    puts("Wrong input, setup failed!");
    return -1;
}

int Save(int a, int b) //���浱ǰ����������
{
    ShowMove(a, b, colornow);
    fprintf(log_file, "%d %d\n", a, b);
}

int DisplayLog()
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

FILE *InitializeSaving() //��ʼ�������ļ�
{
    //��ʼ��log�ļ�,��������.
    if(set_savelog){
    time_t time_now;
    time_now = time(NULL);
    char *log_name = DelSpaceAddLog(ctime(&time_now));
    printf("Log file is saved at %s \n", log_name);
    log_file = fopen(log_name, "a+");
    // char log_name_str[] = ctime(&time_now);
    // log_file = fopen(log_name_str, "a");
    return log_file;
    }else{
        char *log_name = "tempfile";
        printf("No log is recquired.");
        log_file = fopen(log_name, "a+");
        // char log_name_str[] = ctime(&time_now);
        // log_file = fopen(log_name_str, "a");
        return log_file;
    }
}

int MakeMove(int *ap, int *bp)
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