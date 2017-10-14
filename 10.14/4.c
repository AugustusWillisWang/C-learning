#include"lazy.h"
#define MAXLEN 100

char* enc(char* str){
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 'A' && str[i] <= 'U')
        {
            str[i] += 5;
        }
        else if(str[i]>='V'&&str[i]<='Z'){
            str[i] += (5 - 26);
        }
        else if(str[i]>='a'&&str[i]<='u'){
            str[i] += (5);
        }
        else if(str[i]>='v'&&str[i]<='z'){
            str[i] += (5 - 26);
        }
        i++;
    }
    return str;
}

int main(){
    char temp[MAXLEN];
    scanf("%s", temp);
    enc(temp);
    puts(temp);
}