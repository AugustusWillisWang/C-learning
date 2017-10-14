#include<stdio.h>
#include"lazy.h"

long long int fact(int input){
    long long int pro = 1;
    if(input<0){
        printf("wrong fact!");
        return 1;
    }
    if(input>100)
        puts("Warning: too big input may cause trouble!\n");
    while (input > 0)
    {
        pro *= input;
        input--;
    }
    // CK(pro);
    return pro;
}
int main(){
    int z;
    double sum = 0;
    scanf("%d", &z);
    if(z<0)
    printf("wrong input!");
    for (; z > -1;z--){
        sum += 1.0 / (double)fact(z);
    }
    printf("%lf\n", sum);
    return 0;
}