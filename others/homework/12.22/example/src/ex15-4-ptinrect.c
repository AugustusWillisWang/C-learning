#include "geo.h"
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)<(b)?(b):(a))

int ptinrect(struct point p,struct rect r)
{
    return p.x>=r.pt1.x&&p.x<r.pt2.x&&p.y>=r.pt1.y&&p.y<r.pt2.y;
};
