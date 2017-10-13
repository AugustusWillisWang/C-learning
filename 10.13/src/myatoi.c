#include"lazy.h"

int myatoi(char* str){
    if(str==0){//空指针处理
        puts("point at null.");
        return 0;
    }
    int p = 0;
    int sign = 1;
    int result = 0;

        //deal with sign.
        while(str[p]!=0&&(str[p]<'0'||str[p]>'9')){

            if (str[p]=='-'){
                    sign = -sign;
            }
            else {
                    fprintf(stderr, "Invaild number.");
                    BP;
                    return 0;
            }
            p++;
        }

        //deal with number.
        while (str[p] != '\0'){        
            if(str[p]<'0'||str[p]>'9'){
                fprintf(stderr, "Invaild number.");
                BP;
                return 0;
            }
            result*=10;
            result += (str[p]-'0');
            p++;
        }
        return result*sign;
}

//modify the string itself
char* mytolower(char* str){
    int p = 0;
    while (str[p++]!=0)
        if(str[p]>='a'&&str[p]<='z')str[p]+=(-'a'+'A');
    return str;
}

int main(){
    char a[] = "AaSsDd";
    char b[] = "-233";
    char c[] = "333";
    CK(myatoi(b));
    CK(myatoi(c));
    mytolower(a);
    puts(a);
}