#include "lazy.h"
#define YHMAXLINE 100


int yht()
{
    int line = 1;
    int lastline[YHMAXLINE];
    int thisline[YHMAXLINE];
    memset(lastline, 0, YHMAXLINE * sizeof(int));
    memset(thisline, 0, YHMAXLINE * sizeof(int));
    lastline[0] = 1;
    while (line <= 10)
    {
        for (int i = 0; i < YHMAXLINE; i++)
        {
            if (i > 0)
                thisline[i] = lastline[i] + lastline[i - 1];
            else if (i == 0)
                thisline[i] = lastline[i];
            else if (i == YHMAXLINE)
            {
                BOOM("too big");
            }
        }
        for (int i = 0; thisline[i] != 0; i++)
        {
            printf("%d ", thisline[i]);
        }
        puts("");
        memcpy(lastline, thisline, YHMAXLINE * sizeof(int));
        memset(thisline, 0, YHMAXLINE * sizeof(int));
        line++;
    }
}

double atod(char *str)
{
    int i = 0;
    double result = 0.0;
    double sign = 1;
    //space
    while (isspace(str[i]))
        i++;
    //+-
    while (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (isdigit(str[i]))
    {
        result = result * 10.0 + str[i] - '0';
        i++;
    }
    if (str[i] == '.')
    {
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
    if (str[i] == 'e')
    {
        i++;
    }
    double power = 0;
    double powersign = 1.0;
    while (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            powersign *= -1;
        i++;
    }
    while (isdigit(str[i]))
    {
        power = power * 10.0 + str[i] - '0';
        i++;
    }
    if (str[i] == '.')
    {
        i++;
    }
    double powerpow = 0.1;
    while (isdigit(str[i]))
    {
        power = power + powerpow * (str[i] - '0');
        powerpow *= 0.1;
        i++;
    }
    // printf("%lf\n",power);
    return result * sign*pow(10.0, power * powersign);
}

char *reverse(char *str)
{
    int length = 0;
    while (str[length] != '\0')
        length++;
    // CK(length);
    int first = 0;
    int last = length - 1;
    while (first < last)
    {
        char temp = str[last];
        str[last] = str[first];
        str[first] = temp;
        first++;
        last--;
    }
    return str;
}

char *itoh(int num, char *dist)
{
    int sign = 1;
    if (num < 0)
    {
        sign = -1;
        num = -num;
    }
    int i = 0;
    do
    {
        char write;
        write = num % 16;
        if (write >= 0 && write <= 9)
        {
            write += '0';
        }
        else
        {
            write += 'A' - 10;
        }
        num /= 16;
        dist[i] = write;
        i++;
    } while (num > 0);

    if (sign < 0)
    {
        dist[i] = '-';
        i++;
    }
    dist[i] = '\0';
    reverse(dist);
    return dist;
}

int findinline_right(char* lookfor,char* source){
    // int result=-1;
    int result=-1;
    int matchedbit = 0;
    if(lookfor[matchedbit]=='\0')
        BOOM("empty lookfor target");
    for (int i = 0; source[i] != '\0'; i++)
    {
        while(lookfor[matchedbit]==source[i+matchedbit])
            {matchedbit++;
            if(lookfor[matchedbit]=='\0')
                result= i;
            if(source[i+matchedbit]=='\0')
                break;
            }
            matchedbit = 0;
    }
    return result;
}

int sortjx(int* a,int length){
    if(length==1)
        return 0;
    for (int i = 1; i<length;i++){
        for (int j = i - 1; j >= 0 && a[j] < a[j+1];j--)
        {
            int temp = a[j];
            a[j] = a[j+1];
            a[j+1] = temp;
        }
    }
}

    int getodd()
{
    int num;
    scanf("%d",&num);
    if(num>50||num<0)
        BOOM("length out of range");
    int temp[50];
    memset(temp, 0, 50 * sizeof(int));
    for (int i = 0; i < num;i++){
        scanf("%d",&temp[i]);
    }
    for (int i = 0; i < 50;i++){
        if(temp[i]%2==0)
            temp[i] = 0;
    }
    sortjx(temp, 50);
    // for (int i = 0; i < 10;i++){
    //     CK(temp[i]);
    // }
    int i = 0;
    while (i<50){
        if(temp[i]!=0)
        printf("%d ",temp[i]);
        i++;
    }
    return 0;
}

int main()
{
    yht();
    printf("%g\n", atod(" 2.33e-3"));
    printf("%g\n", atod("-2.33e3"));
    printf("%g\n", atod(" 2.33e3.3"));
    char dist[YHMAXLINE];
    int input;
    scanf("%d", &input);
    puts(itoh(input, dist));
    // puts(itoh(-1615,dist));
    CK(findinline_right("233", "23323323333"));
    // int tt[] = {1, 2, 3, 4, 5};
    // sortjx(tt,5);
    // for(int i = 0; i < 5;i++){
    //     CK(tt[i]);
    // }
    getodd();
}