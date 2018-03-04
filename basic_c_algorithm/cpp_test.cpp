#include<cstdio>
#include<algorithm>
using namespace std;

int main(){
    int p[] = {1, 2, 3, 6, 7, 8};
    while(next_permutation(p,p+6)){
        for (int i = 0; i < 6;i++){
            printf("%d ", p[i]);
        }
        printf("\n");
    }
}