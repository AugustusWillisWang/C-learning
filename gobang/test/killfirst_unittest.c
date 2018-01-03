#include "killfirst.h"

int main()
{
    SetUp(1, 1, 2);
    SetUp(1, 1, 1);
    SetUp(1, 2, 1);
    SetUp(1, 3, 1);
    CK(TestKillPoint(1, 4));
    CK(TestKillPoint(1, 0));
    CK(TestKillPoint(1, 0));
    CK(TestKillPoint(1, 4));
    int a;
    scanf("%d", a);
    SetUp(1, 1, 1);
}