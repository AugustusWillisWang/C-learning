#include"lazy.h"
    int a[] = {1, 3,5,2,4,1232,52,74,245,574,1,-4};

void swap(int* array, int a, int b){
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

int qs(int* array,int begin, int end){
    if(begin>=end)
        return 0;
    int center = array[(begin+end)/2];
    swap(array, begin, (begin + end) / 2);
    int towrite = begin+1;
    int toseek = begin+1;
    while(toseek<=end){
        if(array[toseek]<center){
            swap(array, toseek, towrite);
            towrite++;
        }
        toseek++;
        // CK(towrite);
        // CK(toseek);
        SHOWALL(a,"int");
        
        // BP;
    }
    swap(array, begin, towrite - 1);
    qs(array, begin, towrite - 2);
    qs(array, towrite, end);
    return 0;

}

int main(){
    SHOWALL(a,"int");
    qs(a, 0, 10);
    SHOWALL(a,"int");
}