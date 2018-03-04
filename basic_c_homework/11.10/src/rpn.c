#include "lazy.h"
#define STACKSIZE 10

//This rpn is different from the class version. It doesnot deal with the spaces between signals and numbers.
//For a better instance, see the new version in examples.c
double stack[STACKSIZE];
char temp[STACKSIZE];
int posi = 0;

double push(double pushed)
{
    if (posi == STACKSIZE)
        BOOM("stack boomed!");
    stack[posi] = pushed;
    posi++;
}

double pop()
{
    if (posi == 0)
        BOOM("stack empty!");
    posi--;
    // CK(posi);
    return stack[posi];
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
    return result * sign * pow(10.0, power * powersign);
}

double rpn() //PLZ give input completly correct!
{
    //deal with str;
    puts("This rpn is different from the class version. \n It doesnot deal with the spaces between signals and numbers. \n For a better instance, see the new version in examples.c \n");
    char b;
    int poptemp;
    int i = 0;
    while ((b = getchar()) != '\n')
    {

        switch (b)
        {
        case '+':
            temp[i] = '\0';
            push(atod(temp));
            push(pop() + pop());
            i = 0;
            memset(temp, 0, STACKSIZE * sizeof(char));
            break;
        case '-':
            temp[i] = '\0';

            push(atod(temp));
            poptemp = pop();
            push(pop() - poptemp);
            i = 0;
            memset(temp, 0, STACKSIZE * sizeof(char));
            break;
        case '*':
            temp[i] = '\0';

            push(atod(temp));
            push(pop() * pop());
            i = 0;
            memset(temp, 0, STACKSIZE * sizeof(char));
            break;
        case '/':
            temp[i] = '\0';

            push(atod(temp));
            poptemp = pop();
            if (poptemp == 0)
                BOOM("0 as divider!");
            push(pop() / poptemp);
            i = 0;
            memset(temp, 0, STACKSIZE * sizeof(char));
            break;
        case ' ':
            // CP;
            temp[i] = '\0';
            push(atod(temp));
            i = 0;
            memset(temp, 0, STACKSIZE * sizeof(char));
            break;
        default:
            temp[i] = b;
            i++;
            // CP;
            break;
        }
        SHOWALL(stack, "double");
        SHOWALL(temp, "char");
        CK(posi);
    }
    return pop();
}



int main()
{

    // push(99);
    // push(88);
    // CK(pop());
    // double b = pop();
    // BP;
    puts("//PLZ give input completly correct! EG:1 1 1++");
    printf("%lf", rpn());
}