// Copyright (c) 2017-2018 Augustus Wang
// 将要测试的代码写在此处, 使用命令行参数 -test 即可运行

#define TEST
// int tm[BOUNDRY][BOUNDRY];
// memset(tm, 0, sizeof(tm));
// int (*t)[BOUNDRY];
// t=SavePWMartix(tm);
// DBG_ShowPWM(tm);

// SetUp(2, 3, 1);
// UpdatePositionWeight(2, 3, 1, tm);
// DBG_ShowPWM(tm);


// SetUp(3, 3, 1);
// UpdatePositionWeight(3, 3, 1, tm);
// DBG_ShowPWM(tm);


// SetUp(5, 3, 1);
// UpdatePositionWeight(5, 3, 1, tm);
// DBG_ShowPWM(tm);
// SetUp(6, 3, 1);
// UpdatePositionWeight(6, 3, 1, tm);
// DBG_ShowPWM(tm);
// // SetUp(2, 3, 1);
// RecoveryPWMartix(tm, t);
// DBG_ShowPWM(tm);


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

// int p = GenerateFBDWeight();

// SetUp(2, 3, 1);
// p=UpdateFBDWeight(2,3,p);
// int m=GenerateFBDWeight();
// CK(p);
// CK(m);

// SetUp(2, 4, 1);
// p=UpdateFBDWeight(2,4,p);
// m=GenerateFBDWeight();
// CK(p);
// CK(m);


// SetUp(2, 5, 1);
// p=UpdateFBDWeight(2,5,p);
// m=GenerateFBDWeight();
// CK(p);
// CK(m);


int p = GenerateFBDWeight();
SetUp(2, 5, 1);
struct fbd_weight result;
result = UpdateFBDWeight(2, 5, p);
p = GenerateFBDWeight();
CK(p);
CK(result.weight);

SetUp(2, 6, 1);
// struct fbd_weight result;
result = UpdateFBDWeight(2, 6, p);
p = GenerateFBDWeight();
CK(p);
CK(result.weight);

SetUp(2, 7, 1);
// struct fbd_weight result;
result = UpdateFBDWeight(2, 7, p);
p = GenerateFBDWeight();
CK(p);
CK(result.weight);
SetUp(2, 8, 2);
// struct fbd_weight result;
result = UpdateFBDWeight(2, 8, p);
p = GenerateFBDWeight();
CK(p);
CK(result.weight);

//   if (original_weight != GenerateFBDWeight())
//                 printf("bommmmmmm%d %d %d\n", GenerateFBDWeight(), original_weight,depth);
PrintBoard();
// CK(ForbidMove(2, 6, 1));