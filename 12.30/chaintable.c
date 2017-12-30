#include"lazy.h"
struct Node {
    int number;
    struct Node *next;
    struct Node *before;
};

struct Node *chainend;
struct Node *chainstart;
struct Node *lastone;
struct Node *current;

int Add(int num )
{
    if(chainstart==0){
        chainstart=(struct Node *)malloc(sizeof(struct Node));
        chainstart->number = num;
        chainstart->next = 0;
        chainstart->before = 0;
        chainend = chainstart;
        return 0;
    }
    chainend->next = (struct Node *)malloc(sizeof(struct Node));
    chainend->next->before = chainend;
    chainend = chainend->next;
    chainend->number = num;
    chainend->next = 0;
    return 0;
}

int Loop(){
    chainend->next = chainstart;
    chainstart->before = chainend;
}

int Next(){

}


int main()
{
    int n;
    int k;
    puts("n?");
    GET(n);
    puts("k?");
    GET(k);

    for (int i = 1; i <= n;i++){
        Add(i);
    }
    Loop();
    // int q = 10;
    //     current = chainstart;
    // while (q-->0){
    //     printf("%d ", current->number);
    //     current = current->before;
    // }
    // for (int i = 1; i <= n;i++){
    // printf("%d",current)
    current = chainstart;
    int cnt = 0;
    while (n > 1)
    {
        while(++cnt!=k){
            current = current->next;
            printf("cur: %d ", current->number);
            printf("cur k cnt:  %d\n", cnt);
        }
        cnt = 0;
        current->before->before->next = current;
        current->before = current->before->before;
        current = current->next;
        n--;
    }
    CK(n);
    printf("%d", current->number);
    return 0;
}