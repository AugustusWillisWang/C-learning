#include"inc.h"

#define NOPRIME 1
#define PRIME 0
#define UPPER 3000
#define LOWER 100

char list[UPPER+1];

int 
setup_seive_table(int N)
{
    list[0] = list[1] = NOPRIME;
    for (int i=2; i <= sqrt(N);i++){
        if(list[i]==PRIME){
            int product;
            for (int p = 2; (product=p * i) <= N; p++){
                list[product] = NOPRIME;
            }
        }
    }
    return 0;
}

int 
get_prime(int lower,int upper)
{
    for (int i = lower; i <= upper;i++){
        if(list[i]==PRIME){
            printf("%d\n", i);
        }
    }
    return 0;
}

int main()
{
    setup_seive_table(UPPER);
    get_prime(LOWER, UPPER);
    return 0;
}