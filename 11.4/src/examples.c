#include "lazy.h"

//Extern part (eg2,eg3) was not included for it is too easy............

char *trim(char *s)
{
    int n;
    for (n = strlen(s); n >= 0; n--)
    {
        if (s[n] != '\n' || s[n] != '\t' || s[n] != ' ')
            break;
    }
    s[n] = '\0';
}

//goto
int eggoto()
{
    int i = 1;
    while (i)
    {
        i++;
        if (i = 999)
            goto end;
    }
end:
    return 0;
}

int findinline(char* tosearch,char* source){
    // int result=-1;
    int matchedbit = 0;
    if(tosearch[matchedbit]=='\0')
        BOOM("empty target");
    for (int i = 0; source[i] != '\0'; i++)
    {
        while(tosearch[matchedbit]==source[i+matchedbit])
            {matchedbit++;
            if(tosearch[matchedbit]=='\0')
                return i;
            if(source[i+matchedbit]=='\0')
                break;
            }
            matchedbit = 0;
    }
    return -1;
}

char* eg1_find(char* tosearch,char* source,int length){
    char temp[100];
    while(_getline(temp,100)!=-1){
        if((findinline(tosearch, temp))!=-1){
            puts(temp);
        }
    }
}

double atod(char* str){
    int i = 0;
    double result = 0.0;
    double sign = 1;
    //space
    while(isspace(str[i]))
        i++;
    //+-
    while(str[i]=='-'||str[i]=='+'){
        if (str[i]=='-')
            sign *= -1;
        i++;
    }
    while(isdigit(str[i])){
        result = result * 10.0 + str[i] - '0';
        i++;
    }
    if(str[i]=='.'){
        i++;
    }
    double dotpow = 0.1;
    while (isdigit(str[i]))
    {
        result = result + dotpow * (str[i] - '0');
        // printf("%lf\n", result);
        dotpow *= 0.1;
        i++;
    }
    //deal with e
    if(str[i]=='e'){
        i++;
    }
    double power=0;
    double powersign = 1.0;
    while (str[i] == '-' || str[i] == '+')
    {
        if (str[i]=='-')
            powersign *= -1;
        i++;
    }
    while(isdigit(str[i])){
        power = power * 10.0 + str[i] - '0';
        i++;
    }
    if(str[i]=='.'){
        i++;
    }
    double powerpow = 0.1;
    while (isdigit(str[i]))
    {
        power = power + powerpow * (str[i] - '0');
        powerpow *= 0.1;
        i++;
    }
    printf("%lf\n",power);
    return pow(result * sign, power * powersign);
}

int main()
{
    char s[] = "233      ";
    trim(s);
    puts(s);
    CK(findinline("0", "32333333"));
    CK(findinline("333", "32333333"));
    printf("%lf\n", atod(" 2.33e-3"));
}