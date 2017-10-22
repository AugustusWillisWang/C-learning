#include"lazy.h"

char A[5];

int PermutationFailed(char* A,int length){
    int no_element_left = 1;
    for (int i = 0; i < length; i++)
    {
        if(A[i]){
            no_element_left = 0;
            printf("%d ", i);
            A[i] = 0;
            PermutationFailed(A, 5);
            A[i] = 1;
        }
    }
    if(no_element_left){
        printf("\n");
    }
}

int Permutation(char* A,int length,int next_to_add /* 1 */){
    int all_element_is_used = 1;
    for (int i = 0; i < length; i++)
    {
        if (A[i]==0){
            all_element_is_used = 0;
            A[i] = next_to_add;
            Permutation(A, 5, next_to_add + 1);
            A[i] = 0;
        }
    }
    if(all_element_is_used){
        for (int j = 0; j < length;j++){
            printf("%d ", A[j]);
        }
        puts("");
    }
}

int main()
{
    memset(A, 1,5);
    PermutationFailed(A,5);
    memset(A, 0,5);
    Permutation(A,5,1);
}