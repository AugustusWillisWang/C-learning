#include"lazy.h"
#define LEN 100

char* my_strcpy(char* dest,char* sour){
    int i = 0;
    while(sour[i]!='\0'){
        dest[i] = sour[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int my_strlen(char* str){
    int len = 0;
    while (str[len]!='\0')
        len++;
    return len;
}

int my_gets(char* str){
    char p=0;
    int i=0;
    while ((p = getchar()) != EOF)
    {
        if(p=='\n')
            p = '\0';
        str[i] = p;
        if (p == '\0')
            return 1;//return 1 when get a line without EOF
        i++;
    }
    return 0;//return 0 when get EOF 
}

void clear(char* chararray){
    for (int i = 0; i < LEN;i++){
        chararray[i] = 0;
    }
}

int main()
{
    char a[LEN];
    char b[LEN];
    char temp[LEN];
    clear(a);
    clear(b);
    clear(temp);
    int lena=0;
    int lenb=0;
    while(my_gets(temp)){
        if ( my_strlen(temp) > lena)
        {
            lena = my_strlen(temp);
            my_strcpy(a, temp);
        }
        if(my_strlen(temp)<lena&&my_strlen(temp)>lenb){
            lenb = my_strlen(temp);
            my_strcpy(b, temp);
        }
    }
    show(my_strlen(a));
    show(my_strlen(b));
        show(my_strlen(temp));
        puts(a);
        puts(b);
}