#include"lazy.h"

int Combination(char* A,int length,int current_position/* 0 */){
    if(current_position==length){
        for (int i = 0; i < length; i++)
        {
            if(A[i])
                printf("%d ", i);
        }
        puts("");
        return 0;
    }
    // CK(current_position);
    A[current_position] = 1;
    Combination(A, 5, current_position+1);
    A[current_position] = 0;
    Combination(A, 5, current_position+1);
}

int Bincomb(int number_of_elements){
    // if(number_of_elements>31)
        // BOOM("the set is too big");
    for (int i = 0; i < ((1 << (number_of_elements)));i++){
        int j = i;
        int numnow = 1;
        while (j > 0)
        {
            if(j%2)
                printf("%d ", numnow);
            numnow++;
            j /= 2;
        }
        puts("");
    }
}

int main(){
    LICENSE;
    char A[5];
    memset(A, 1, 5);
    Combination(A, 5, 0);
    Bincomb(5);
}