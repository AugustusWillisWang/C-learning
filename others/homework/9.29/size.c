#include"lazy.h"

int main()
{
    LISENCE;
    SHOW(sizeof(int));
    SHOW(sizeof(char));
    SHOW(sizeof(float));
    SHOW(sizeof(double));
    SHOW(sizeof(short int));
    SHOW(sizeof(long int));
    int sizeofshortint= sizeof(short int);
    SHOW(sizeofshortint);
    int sizeoflongdouble = sizeof(long double);
    SHOW(sizeoflongdouble);
    int sizeoflonglongint = sizeof(long long int);
    SHOW(sizeoflonglongint);

}