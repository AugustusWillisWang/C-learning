#include "lazy.h"

//,运算符的值为最后表达式的值!!!

int eg1eg2()
{
    int a, b, c;
    a = b = 5;
    c = a++, a + b, b += 3;
    CK(a);
    CK(b);
    CK(c);
    a = b = 5;
    c = (a++, a + b, b += 3);
    CK(a);
    CK(b);
    CK(c);
    return 0;
}

int eg3()
{
    int n = 0;
    int a = 5;
    int i;
    if (i > 0)
        for (i = 0; i < n; i++)
            if (a > i)
                printf("a=%d,i=%d,and i>i\n", a, i);
            else
                printf("error!n<0\n");
    return 0;
}

int eg4(){
    int a = 10;
    if(a>5){
        printf("a>5\n");
    }else if (a>0){
        printf("a>0\n");
    }else{
        printf("a<=0\n");
    }
    return 0;
}

int binsearchwithbug(int tosearch, int *array, int length)
{
    int a = (length - 1) / 2;
    if (tosearch == array[a])
    {
        return a;
    }
    else if (length == 1)
    {
        return -1; //会导致问题
    }
    else if (array[a] < tosearch)
    {
        return binsearchwithbug(tosearch, array + a + 1, length - a - 1) + a + 1;
    }
    else
    {
        return binsearchwithbug(tosearch, array, a);
    }
}

int binsearch(int tosearch, int *array, int length)
{
    int low = 0;
    int high = length - 1;
    while (low != high)
    {
        int mid = (low + high) / 2;
        if (tosearch == array[mid])
        {
            return mid;
        }
        else if (tosearch < array[mid])
        {
            high = mid - 1;
        }
        else
            low = mid + 1;
    }
    if (array[low] != tosearch)
    {
        return -1;
    }
    return low;
}

int switcher()
{
    int a=0, b = 0;
    switch (a)
    {
    case 0:
        b++;
    case 1:
        b++;
    case 2:
        b++;
    case 3:
        b++;
    case 4:
        b++;
    case 5:
        b++;
    case 6:
        b++;
    }
    CK(b);
}

int casechrcnt(){
    int cnt = 0;
    int temp = 0;
    while((temp=getchar())!=EOF){
        switch (temp)
        {
        case '\0':
            break;
        case '\n':
            break;
        case '\t':
            break;
        default:
            cnt++;
            }
    }
    return cnt;
}

int my_stirct_atoi(char* str){
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

int my_soft_atoi(char* str){
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
                    //pass
            }
            p++;
        }

        //deal with number.
        while (str[p] != '\0'){        
            if(str[p]<'0'||str[p]>'9'){
                if(str[p]=='-'||str[p]=='+'){
                    BOOM("-+ in number");
                }
                //pass
            }else{
                result*=10;
                result += (str[p]-'0');
                
            }
            p++;
        }
        return result*sign;
}

int myshellsort(int* array, int length){
    for (int gap = length / 2; gap > 0;gap/=2){
        for (int posi_in_gap=0;posi_in_gap<gap;posi_in_gap++){
            for (int i = posi_in_gap + gap; i < length;i+=gap){
                for (int j = i - gap; j >= 0 && array[j] > array[j + gap];j-=gap)
                {
                    int temp = array[j];
                    array[j] = array[j + gap];
                    array[j + gap] = temp;
                }
            }
        }
    }
}

int shellsort(int* array, int length){
    int i, j, gap;
    int temp;
    for (gap = length / 2; gap > 0;gap/=2){
        for (i = gap; i < length;i++){
            for (j = i - gap; j >= 0 && array[j] > array[j + gap];j-=gap){
                temp = array[j];
                array[j] = array[j + gap];
                array[j + gap] = temp;
            }
        }
    }
}

char* reverse(char* str){
    int length = 0;
    while(str[length]!='\0')
        length++;
    CK(length);
    int first = 0;
    int last = length - 1;
    while(first<last){
        char temp = str[last];
        str[last] = str[first];
        str[first] = temp;
        first++;
        last--;
    }
    return str;
}

char* myitoa(int num){
    int sign = 1;
    if(num<0){
        sign = -1;
        num *= -1;
    }
    char* str=(char*)malloc(sizeof(char)*34);
    // CP;
    int i = 0;
    do
    {
        str[i] = num % 10+'0';
        num /= 10;
        i++;
    } while (num > 0);
    if(sign==1){
        str[i] = '\0';
    }else{
        str[i] = '-';
        str[i + 1] = '\0';
    }
    // CP;
    reverse(str);
    return str;
}

int A[7] = {1, 2, 3, 4, 5, 6, 7};
// char str[] = "1234567";
int main()
{
    LICENSE;
    eg1eg2();
    eg3();
    CK(binsearch(6, A, 7));
    CK(binsearch(2, A, 7));
    CK(binsearch(1, A, 7));
    CK(binsearch(233, A, 7));
    switcher();
    CK(my_soft_atoi(" - -2 3 33"));
    CK(my_stirct_atoi("---2333"));
    char teststr[] = "2333";
    puts(reverse(teststr));
    puts(myitoa(-233));
    CK(casechrcnt());
}