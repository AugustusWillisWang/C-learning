#include"lazy.h"
#define MAXLEN 100

char* dec(char* str){
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'F' && str[i] <= 'Z')
        {
            str[i] -= 5;
        }
        else if(str[i]>='A'&&str[i]<='E'){
            str[i] -= (5 - 26);
        }
        else if(str[i]>='f'&&str[i]<='z'){
            str[i] -= (5);
        }
        else if(str[i]>='a'&&str[i]<='e'){
            str[i] -= (5 - 26);
        }
        i++;
    }
    return str;
}

int main(){
    char temp[MAXLEN];
    scanf("%s", temp);
    dec(temp);
    puts(temp);
}