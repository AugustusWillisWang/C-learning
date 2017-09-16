#include"inc.h"
#include<boolen.h>

#define NOPRIME 1
#define PRIME 0
#define UPPER 3000
#define LOWER 100


int 
setup_seive_table(int N)
{
    if(N<2){
        puts("get nothing");
        return -1;
    }
    int estimate=N;
    for (;(double)estimate/(double)ln(estimate)<=1.5*(double)N;estimate++){
    }
    bool list[estimate];
    list = { NOPRIME,
             NOPRIME,
    }
    int posi = 2;
    for (int i = posi; i <= estmate;i++){
        
    }
}

int main()
{
    setup_seive_table(UPPER);
    get_prime(LOWER, UPPER);
    return 0;
}