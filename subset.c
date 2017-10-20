#include"lazy.h"

// int printsubset(int* array,int left,int right){
//     //print array
//     for (int i = left; i < right;i++){
//         printf("%d ", array[i]);
//     }
//     printf("\n");
    
//     for (; left < right; left++)
//     {
//         printsubset(array, left, right);
//     }

int pailie(char*A,int all){
    for (int i = 0; i < all;i++){
        int all0 = 1;
        if (A[i])
        {
            printf("%d ", i);
            A[i] = 0;
            int all0 = 1;
            pailie(A, all);
            // printf("\n");
            // pailie(A, all);
            // printf("\n");
        }
        if(all0)
            puts("");
    }
}



int main(){
    char *A = (char*)malloc(100);
    memset(A, 1, 100);
    BP;
    pailie(A, 5);

    // print_subset(5, A, 0);
}