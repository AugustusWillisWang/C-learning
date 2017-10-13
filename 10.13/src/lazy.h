#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdarg.h>
#include<time.h>

//大写宏
#ifndef _AWSHEAD
    #define _AWSHEAD
    #define SHOW(x) printf(""#x":%d\n", x)
    //显示整数值
    #define GET(x) scanf("%d",&x)
    //读取整数
    #define TRACK(x) (printf("track: "#x":%d\n", x)*0+x)
    //值追踪
    #define CK(x) (printf("track: "#x":%d\n", x)*0+x)
    //值追踪
    #define CP (printf("checkpoint. line:%d\n",__LINE__))
    //检查点
    #define BP (printf("breakpoint. line:%d\n",__LINE__),getchar())
    //断点
    // #define LICENSE() (printf("Augustus Wang (c) 2017\n"),printf("Compiled on %s at %s\n", __DATE__,__TIME__))
    //签名
    #define LICENSE (printf("%s\n",__FILE__),printf("Augustus Wang (c) 2017\n"),printf("Compiled on %s at %s\n", __DATE__,__TIME__))
    //签名
    #define LEN(x) (sizeof(x)/sizeof(x[0]))
    //数组长度
    #define  MAX(x,y) (((x)>(y)) ? (x) : (y))
    #define  MIN(x,y) (((x) < (y)) ? (x) : (y))
#endif

// //小写偷懒用
// #ifndef _AWSHEAD
//     #define _AWSHEAD 
//     #define show(x) printf(""#x":%d\n", x)
//     //显示整数值
//     #define get(x) scanf("%d",&x)
//     //读取整数
//     #define track(x) (printf("track: "#x":%d\n", x)*0+x)
//     //值追踪
//     #define ck(x) (printf("track: "#x":%d\n", x)*0+x)
//     //值追踪
//     // #define cp() (printf("checkpoint. line:%d\n",__LINE__))
//     //检查点
//     #define CP (printf("checkpoint. line:%d\n",__LINE__))
//     //检查点
//     // #define bp() (printf("breakpoint. line:%d\n",__LINE__),getchar())
//     //断点
//     #define BP (printf("breakpoint. line:%d\n",__LINE__),getchar())
//     //断点
//     // #define lisence() (printf("Augustus Wang (c) 2017\n"),printf("Compiled on %s at %s\n", __DATE__,__TIME__))
//     //签名
//     #define LISENCE (printf("%s\n",__FILE__),printf("Augustus Wang (c) 2017\n"), printf("Compiled on %s at %s\n", __DATE__, __TIME__))
// //签名
//     #define len(x) (sizeof(x) / sizeof(x[0]))
// //数组长度
//     #define max(x, y) (((x) > (y)) ? (x) : (y))
//     #define min(x, y) (((x) < (y)) ? (x) : (y))

// #endif
//BY AW
//2017.9.29
