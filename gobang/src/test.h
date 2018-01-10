// Copyright (c) 2017-2018 Augustus Wang
// 将要测试的代码写在此处, 使用命令行参数 -test 即可运行

#define TEST
int tm[BOUNDRY][BOUNDRY];
memset(tm, 0, sizeof(tm));
int (*t)[BOUNDRY];
t=SavePWMartix(tm);
DBG_ShowPWM(tm);

SetUp(2, 3, 1);
UpdatePositionWeight(2, 3, 1, tm);
DBG_ShowPWM(tm);


SetUp(3, 3, 1);
UpdatePositionWeight(3, 3, 1, tm);
DBG_ShowPWM(tm);


SetUp(5, 3, 1);
UpdatePositionWeight(5, 3, 1, tm);
DBG_ShowPWM(tm);
SetUp(6, 3, 1);
UpdatePositionWeight(6, 3, 1, tm);
DBG_ShowPWM(tm);
// SetUp(2, 3, 1);
RecoveryPWMartix(tm, t);
DBG_ShowPWM(tm);

// int (*t)[BOUNDRY];
// t=SavePWMartix(tm);
// UpdatePositionWeight(6, 3, 1, tm);
// RecoveryPWMartix(tm, t);

// int t=GenerateWeight();
// colornow = 1;
// SetUp(2, 3, 1);
// t=UpdateWeight(2,3,t);
// SetUp(3, 4, 1);
// t=UpdateWeight(3,4,t);
// SetUp(4, 5, 1);
// t=UpdateWeight(4,5,t);
// SetUp(5, 6, 1);
// t=UpdateWeight(5,6,t);

// CK(t);

// PrintBoard();
