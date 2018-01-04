#include"inc.h"

int main(int argc,char* argv[])
{
    if(argc==2){
        int f = atoi(argv[1]);
        double c = (f - 32) * 5 / 9;
        showd(c);
        return 0;
    }

    if(argc==1){
        int f = 0;
        int c;
        while(f<=300){
            double c = (f - 32) * 5 / 9;
            printf("%d\t%lf\n", f, c);
            f += 20;
        }
        return 0;
    }
}