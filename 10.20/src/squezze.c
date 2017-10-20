#include"lazy.h"

char* squeeze(char* str,char chr){
    int i = 0, j = 0;
    for (; str[i] !='\0'; i++)
    {
        if(str[i]!=chr){
            // CK(str[j]);
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
    return str;
}

char* mycpy(char* dist,char* source){
    int i=0;
    while(dist[i]!='\0'){
        i++;
    }
    int j=0;
    while(source[j]!='\0'){
        dist[i]=source[j];
        i++;
        j++;
    }
    dist[i]='\0';
    return  dist;
}

int main(){
    // char *a = "233333333";
    // CK(LEN("23333333"));
    // CK(LEN(a));

    //以下是自己随便测着玩的
    char t[] = "2311313131";
    puts(t);
    squeeze(t, '1');
    puts(t);
    char p[20]={'1','0','\0'};
    char pp[]="pp";
    char ppp[10]="ppp";
    puts(pp);
    char l[]="200";
    puts(p);
    mycpy(p,l);
    puts(p);
    CK(p[2]);
}