#include "support.h"
#include "zobrist.h"

int main()
{
    Setupzob();
    unsigned long int zob=Getzob();
    unsigned long int zob2=Getzob2();
    struct findresult result;
    SetUp(1, 1, 1);
    zob = NextHash(1,1,zob,1);
    zob2 = NextHash2(1,1,zob2,1);
    result = FindInHashTable(zob, zob2, 1, 1);
    SetUp(1, 12, 2);
    SetUp(1,3,1);

}