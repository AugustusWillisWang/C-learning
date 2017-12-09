//zobrist.h
#include <stdlib.h>
#define SEED 233

int _ndefZobchain = 1;

struct _ZobChain
{
    unsigned long int hash ;
    double weight ;
    struct _ZobChain *next ;
} _ZobChain;


unsigned long int zobrist_table[BOUNDRY][BOUNDRY][2];

int Setupzob()
{
    srand(SEED);
    for (int a = 0; a < BOUNDRY ; a++)
    {
        for (int b = 0; b < BOUNDRY;b++){
            zobrist_table[a][b][0] = rand();
            zobrist_table[a][b][1] = rand();
            
        }
        // printf("%lu ", zobrist_table + i);
    }
    _ZobChain.hash = 0;
    _ZobChain.weight = 0;
    _ZobChain.next = 0;
}

unsigned long int Getzob()
{
    unsigned long int result=0;
    for (int a = 0; a++; a < BOUNDRY)
    {
        for (int b = 0; b < BOUNDRY;b++){
            if(board[a][b]==BLACK){
                result += zobrist_table[a][b][0];
            }
            if(board[a][b]==WHITE){
                result += zobrist_table[a][b][1];                
            }
            
        }
    }
    return result;
}

double FindinZobChain(double **_zobnewweightp)
//Remark: the status of this function is defined at double *_zobnewweight = 0;
// _weight= FindinZobChain();
// if (_zobnewweight == 0) {_weight = newweight();*_zobnewweight=_weight;}
// else goon;
{
    unsigned long int zob = Getzob();
    struct _ZobChain *current = &_ZobChain;
    *_zobnewweightp = 0;
    
    // struct _ZobChain *last = &_ZobChain;
    while(current->next!=0&&current->next->hash<zob){
        current = current->next;
    }
    if(current->next==0){
        current->next = (struct _ZobChain*)malloc(sizeof(_ZobChain));
        current->next->hash = zob;
        current->next->next=0;
        *_zobnewweightp = &(current->next->weight);
        return 0;
        //Be aware to set _zobnewweight to 0 after using;
    }
    if(current->next->hash==zob){
    *_zobnewweightp = 0;
        
        return current->next->weight;
    }
    if(current->next->hash>zob){
        struct _ZobChain *tempnext = current->next;
        current->next =(struct _ZobChain*) malloc(sizeof(_ZobChain));
        current = current->next;
        current->next = tempnext;
        current->hash = zob;
        *_zobnewweightp = &(current->weight);
        return 0;
    }
    return 0;
}
