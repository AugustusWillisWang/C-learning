#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
//#include <windows.h>
//#include <windef.h>
#define SIZE 15
#define CHARSIZE 2
#define block2 7 // �߶�
#define flex2 6 // ���
#define block3 5 // ����
#define flex3 4 // ����
#define block4 3 // ����
#define flex4 2 // ����
#define win 1 // ����
#define zero 0
#define six 8//���������ж�
#define TYPELENGTH ((1<<19)-1)
#define HASHLENGTH ((1<<21)-1)
#define MAXSCORE 9999999
#define FORBIDDEN -100

void initRecordBorard(void);
void recordtoDisplayArray(void);
void displayBoard(void);
void oneplayer(void);
void twoplayers(void);
int ifwin(int player);
void addmove(int x,int y, int player);
int CordinateJudge(int x, char y);
void CordinateTrans(int a, char b);
void zzAI(int a);
void inithash(void);

//����ʹ�õ���GBK���룬ÿһ�������ַ�ռ��2���ֽڡ�

//���̻���ģ��
char aInitDisplayBoardArray[SIZE][SIZE*CHARSIZE+1] =
{
		"���өөөөөөөөөөөөө�",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"�ĩ��������������",
		"���۩۩۩۩۩۩۩۩۩۩۩۩۩�"
};
//������������ʾ����
char aDisplayBoardArray[SIZE][SIZE*CHARSIZE+1];

char play1Pic[]="��";//������;
char play1CurrentPic[]="��";

char play2Pic[]="��";//������;
char play2CurrentPic[]="��";

//���������ڼ�¼���̸��
int aRecordBoard[SIZE][SIZE];
int current_x = -1;//
int current_y = -1;//
int x, y, *xp, *yp;
int xin;
char yin;
int playround;//���ڽ��еĻغ���
int player;//��1��2��ʾ���
int first[HASHLENGTH],next[HASHLENGTH], tall = 0;
typedef struct point{
    int x,y;
}rpoint;
struct node{
    int x;
    int y;
} zzAIposition;
//���ڱ�ʾAI���ӵ�λ�õĽṹ
struct b{
    int horizontal;
    int vertical;
    int lean1;
    int lean2;
}condition;
//���ں�������б���ʤ���ж�
int keytime = 0;
int ptime = 0;
int itime = 0;
int order;
int gensize;
char shash[TYPELENGTH+1];

typedef struct{ // hash a line
    unsigned long long key;
    unsigned char num[9];
}ephash;

ephash phash[HASHLENGTH+10];
char hkind,ckind; // 1 for human 1 ; 2 for human 2.
char nboard[SIZE+2][SIZE+2];

char stype[][10] = { // Types . Caution: Some situations have symmetrical types.
    {5,1,1,1,1,1},   // win 0
    {6,0,1,1,1,1,0}, // flex4 1
    {7,0,0,1,1,1,1,2},{7,2,0,1,1,1,1,2},{5,1,1,0,1,1},{5,1,0,1,1,1}, //block4 2-5 //2111101
    {7,2,0,1,1,1,0,0},{7,0,0,1,1,1,0,0},{6,0,1,0,1,1,0}, //flex3 6-8
    {6,0,0,1,1,1,2},{6,0,1,0,1,1,2},{6,0,1,1,0,1,2},{5,1,0,0,1,1},{5,1,0,1,0,1},{7,2,0,1,1,1,0,2}, //block3 9-14
    {6,0,0,1,1,0,0},{6,2,0,1,1,0,0},{7,0,0,1,0,1,0,0},{7,2,0,1,0,1,0,0},{6,0,1,0,0,1,0}, //flex2 15-19
    {6,2,1,1,0,0,0},{6,2,1,0,1,0,0},{6,2,1,0,0,1,0},{5,1,0,0,0,1},{7,2,0,1,0,1,0,2}, //block2 20-24
    {6,1,1,1,1,1,1}// six 25
};
//���ã���һ������ʾ������Ŀ�����漸����ʾ����
const int Dx[]={0,1,1,1,0,-1,-1,-1},
          Dy[]={1,1,0,-1,-1,-1,0,1};//Direction

rpoint nextx; // Next move if killed oppo
bool depret = false; // deeping depsearch factor
int killdep,defencedep,depsearchdep;
unsigned long long power[11] = {1};
void cpower()
{
    for (int i=1;i<=10;++i)
        power[i] = (power[i-1]*37)&TYPELENGTH;
}

void pchash(unsigned long long hash[],char line[],int len,char Stone)
{
 //own 2; zero 1; others 3;i
    hash[0] = 0;
    for (int i=1;i<=len;++i)
        hash[i] = (hash[i-1]*37+((line[i] == Stone)?2:(line[i] == 0 ? 1 : 3)));//&TYPELENGTH;
}

unsigned long long gthash(unsigned long long hash[],int l,int r){
    return (hash[r]-hash[l-1]*power[r-l+1]);//&TYPELENGTH;
}


int main()
{
    char mode[10];
    inithash();
    initRecordBorard();
	recordtoDisplayArray();
	displayBoard();
    printf("Which mode do you want to choose?\n1 for one player\n2 for two players\nYou can presults qunsigned long longt to qunsigned long longt the game.\n");
    scanf("%s",mode);
    if (!strcmp(mode,"quit"))
        exit(0);
    else
    switch(mode[0])
    {
        case '1':printf("Who will be the first?rolling����������������\n");
                 srand((unsigned)time(NULL));
                 order=2;
                if (order == 1)
                    {
                        hkind = 1;
                        ckind = 2;
                    }else
                        {
                            hkind = 2;
                            ckind = 1;
                        }
                    oneplayer();
                 break;
        case '2':twoplayers();
                 break;
    }
    return 0;
}

//��ʼ�����̸��

///////////////////////////////////////////////////////////
//��������: insert
//����: unsigned long long, unsigned char[]
//����ֵ: ��
//����:  ���ϣ���в���ؼ��֣�ִ�к�������ڼ����ж�����ģʽ
///////////////////////////////////////////////////////////
void insert(unsigned long long x,unsigned char mnum[])
{
    itime++;
    int pos = x&HASHLENGTH;
    next[++tall] = first[pos];
    first[pos] = tall;
    phash[tall].key = x;
    for (int i=0;i<=8;++i)
        phash[tall].num[i] = mnum[i];
}

///////////////////////////////////////////////////////////
//��������: ifrecord
//����: unsigned long long
//����ֵ: һ��ָ��unsigned char���͵�ָ��
//����:�ڹ�ϣ����Ѱ�Ҹ��еĹؼ�����û�б���¼�������У������ٽ��м��㡣���ڼ����ж�����
//////////////////////////////////////////////////////////
unsigned char *ifrecord(unsigned long long x){
    ptime++;
    int pos = x&HASHLENGTH;
    for (int k = first[pos]; k; k = next[k]){
        if (phash[k].key == x)
			return phash[k].num;
        keytime++;
    }
    return NULL;
}

//////////////////////////////////////////////////////////
//��������: myqsort
//����: rpoint[], int[], int, int
//����ֵ: ��
//����:�ݹ���������㷨�����ڴӸߵ������и�����ķ���ֵ
/////////////////////////////////////////////////////////
void myqsort(rpoint a[],int s[],int l,int r)
{//qsort
    if (l>=r)
		return;
    int i = l,j = r,tmp = s[l];
    rpoint tp = a[l];
    while(i<j){
        while((s[j] <= tmp) && (i < j)) j--;
	        s[i] = s[j], a[i] = a[j];
        while((s[i] >= tmp) && (i < j)) ++i;
	        s[j] = s[i], a[j] = a[i];
    }
    s[i] = tmp,a[i] = tp;
    myqsort(a,s,l,i-1);
    myqsort(a,s,i+1,r);
}

///////////////////////////////////
//��������: tablecount
//����: unsigned char[], unsigned long long[], int
//����ֵ: ��
//����: ��һ�����ͼ��㺯�������ڼ���ÿһ�е�����
////////////////////////////////////
void tablecount(unsigned char num[],unsigned long long hash[],int len)
{
    for (int i=1;i<=len-4;++i)
    {
        num[shash[gthash(hash,i,i+4)&TYPELENGTH]]++;
        if (i + 5 <= len)
			num[shash[gthash(hash,i,i+5)&TYPELENGTH]]++;
        if (i + 6 <= len)
			num[shash[gthash(hash,i,i+6)&TYPELENGTH]]++;
    }
}

////////////////////////////////////////////////////
//��������: value
//����: char[][], char
//����ֵ: int
//����: ���ø�������Ŀ�������֡�������ǰ���棬����ֵ������ʤ���жϣ���Ҫ���ھ��������
////////////////////////////////////////////////////
int value(char board[][SIZE+2],char Stone)
{
    unsigned char tnum[9];// win 1 ... zero 0
    static char aline[SIZE+2];
    static unsigned long long thash[SIZE+2];
    static unsigned char *tmp;
    for (int i=0;i<=8;++i)
        tnum[i] = 0;
    for(int k=0;k<=3;++k)
    {
        if (k == 0 || k == 2)
            {
            for (int i=1;i<=SIZE;++i)
            {
                int px = ((k == 0) ? i : 1) - Dx[k], py = ((k == 0) ? 1 : i) - Dy[k];
                bool empty = 1;
                for (int j=1;j<=SIZE;++j)
                {
                    aline[j] = board[px += Dx[k]][py += Dy[k]];
                    if (aline[j])
						empty = 0;
                }
                if (empty)
					continue;
                pchash(thash,aline,SIZE,Stone);
                tmp = ifrecord(thash[SIZE]);
                if (tmp == NULL){
                    unsigned char x[9];
                    for (int i=0;i<=8;++i)
                        x[i] = 0;
                    tablecount(x,thash,SIZE);
                    insert(thash[SIZE],x);
                    for (int i=0;i<=8;++i) tnum[i] += x[i];
                }else
					for (int i=0;i<=8;++i) tnum[i] += tmp[i];
            }
        }else{ //k==1||k==3
            int l,r;
            if (k == 3)
				l = 5,r = SIZE;
            if (k == 1)
				l = 1,r = SIZE - 5 + 1;
            for (int i=l;i<=r;++i)
            {
                int px = 1 - Dx[k], py = i - Dy[k];
                int len = (k == 1) ? SIZE - i + 1 : i;
                bool empty = 1;
                for (int j=1;j<=len;++j)
                {
                    aline[j] = board[px += Dx[k]][py += Dy[k]];
                    if (aline[j]) empty = 0;
                }
                if (empty) continue;
                pchash(thash,aline,len,Stone);
                tmp = ifrecord(thash[len]);
                if (tmp == NULL){
                    unsigned char x[9];
                    for (int i=0;i<=8;++i)
                        x[i] = 0;
                    tablecount(x,thash,len);
                    insert(thash[len],x);
                    for (int i=0;i<=8;++i)
                        tnum[i] += x[i];
                }else
					for (int i=0;i<=8;++i)
                        tnum[i] += tmp[i];
            }
            for (int i=2;i<=SIZE-5+1;++i)
            { // i=1 has been calculated before
                int px = i - Dx[k], py = ((k == 1) ? 1 : SIZE) - Dy[k];
                int len = SIZE - i + 1;
                bool empty = 1;
                for (int j=1;j<=len;++j)
                {
                    aline[j] = board[px += Dx[k]][py += Dy[k]];
                    empty = 0;
                }
                if (empty)
					continue;
                pchash(thash,aline,len,Stone);
                tmp = ifrecord(thash[len]);
                if (tmp == NULL)
                    {
                    unsigned char x[9];
                    for (int i=0;i<=8;++i) x[i] = 0;
                    tablecount(x,thash,len);
                    insert(thash[len],x);
                    for (int i=0;i<=8;++i) tnum[i] += x[i];
                }else
					for (int i=0;i<=8;++i) tnum[i] += tmp[i];
            }
        }
    }
    if (tnum[win] > 0)
		return MAXSCORE;
    int result = 0;
    if (tnum[flex4] > 0)
		return 100000; // Alive Four
    if (tnum[block4] >= 2||(tnum[block4]==1&&tnum[flex3]>0))
		return 100000;// Double GFour || One GFour+AThree
    if (tnum[flex3] >= 2)
		return 7500; //Double AThree
    result += 1000 * (tnum[flex3] + tnum[block4]);
    result += 100 * (tnum[block3] + tnum[flex2]);
    result += 10 * (tnum[block2]);
    return result;
}

bool defencemode = false;// ��������ģʽת��
int nStep = 0; // presultent total step

//////////////////////////////////////////////////////////
//��������: pointvalue
//����: char[][], rpoint, char
//����ֵ: int
//����: ���ø�������Ŀ������һ����������ֵ����������ʱѡ�����������㣬�Լ���������
//////////////////////////////////////////////////////////
int pointvalue(char board[][SIZE+2],rpoint p,char Stone)
{
    unsigned char tnum[9],onum[9];// win 1 ... zero 0
    static char aline[SIZE+2];
    char oppo = (Stone == 1 ? 2 : 1);
    static unsigned long long thash[SIZE+2];
    static unsigned char *tmp;
    for (int i=0;i<=8;++i)
        tnum[i] = onum[i] = 0;
    for (int k=0;k<=3;++k)
    {
        int l,r,px,py;
        for (px = p.x, py = p.y, r = 0; r < 6 && board[px+Dx[k]][py+Dy[k]] != -1; r++, px += Dx[k], py += Dy[k]);
        for (px = p.x, py = p.y, l = 0; l < 6 && board[px-Dx[k]][py-Dy[k]] != -1; ++l, px -= Dx[k], py -= Dy[k]);
        px -= Dx[k],py -= Dy[k];
        bool empty = 1;
        for (int j=1;j<=l+r+1;++j)
        {
            aline[j] = board[px+=Dx[k]][py+=Dy[k]];
            if (aline[j]) empty = 0;
        }
        if (empty) continue;

        aline[l+1] = Stone;
        pchash(thash,aline,l+r+1,Stone);
        tmp = ifrecord(thash[l+r+1]);
        if (tmp == NULL){
            unsigned char x[9];
            for (int i=0;i<=8;++i) x[i] = 0;
            tablecount(x,thash,l+r+1);
            insert(thash[l+r+1],x);
            for (int i=0;i<=8;++i) tnum[i] += x[i];
        }else for (int i=0;i<=8;++i) tnum[i] += tmp[i];

        aline[l+1] = oppo;
        pchash(thash,aline,l+r+1,oppo);
        tmp = ifrecord(thash[l+r+1]);
        if (tmp == NULL){
            unsigned char x[9];
            for (int i=0;i<=8;++i)
                x[i] = 0;
            tablecount(x,thash,l+r+1);
            insert(thash[l+r+1],x);
            for (int i=0;i<=8;++i)
                onum[i] += x[i];
        }else for (int i=0;i<=8;++i) onum[i] += tmp[i];
    }

    //owner's score is double than oppo
    if (tnum[win] > 0) return MAXSCORE;

    if (Stone == 1){// CHECK 1 FORBIDDEN POINT   JUST A SIMPLIFIED VERSION
        if (tnum[six]) return FORBIDDEN;   // six
        if (tnum[flex3] >= 2) return FORBIDDEN;  //DOUBLE ALIVE THREE
        if (tnum[flex4] + tnum[block4] >= 2) return FORBIDDEN; // DOUBLE FOUR
    }
//���ڽ���
    tnum[block4] -= tnum[six], onum[block4] -= onum[six];// on such a condition as oooxoo
    if (onum[win] > 0) return MAXSCORE>>1;
    int result = 0;
    if (tnum[flex4] > 0) return 100000;
    if (onum[flex4] > 0) return 50000;
    if (tnum[block4] >= 2) return 100000;
    if (tnum[block4] == 1 && tnum[flex3] > 0) return 75000; // ����
    if (onum[block4] >= 2) return 50000;
    if (onum[block4] == 1 && onum[flex3] > 0) return 50500;
    if (defencemode) if (tnum[block4]) return 60000;
    if (tnum[block4]) return 10000;
    if (tnum[flex3] >= 2) result += 7500; //Double AThree
    if (onum[flex3] >= 2) result += 3750;
    result += 1000 * (tnum[flex3]+tnum[block4]) + 500 * (onum[flex3]+onum[block4]);
    result += 100 * (tnum[block3]+tnum[flex2]) + 50 * (onum[block3]+onum[flex2]);
    result += 10 * (tnum[block2])+5*(onum[block2]);
    return result;

}

////////////////////////////////////////////////
//��������: bestpoint
//����: rpoint[], char[][], char, int
//����ֵ: int
//����:���Ծ������������ʱ��������������õļ����㣬��¼���������������Ӷ����м�֦����������
////////////////////////////////////////////////
int bestpoint(rpoint pts[],char board[][SIZE+2],char kind,int factor){ // factor 2 usage
    int size=0,px,py;
    static bool used[SIZE+1][SIZE+1];//�����ж��Ƿ�ʹ�ã������Ǳ߽�ֵ
    static int sre[SIZE*SIZE+10];
    int nearpoint = (nStep <= 2) ? 1 : 2;
    for (int i=1;i<=SIZE;++i)
        for (int j=1;j<=SIZE;++j)
            used[i][j] = 0;
            //��ʼδ����
    for (int i=1;i<=SIZE;++i)
        for (int j=1;j<=SIZE;++j)
            if (board[i][j])
                {
                for (int k=0;k<=7;++k)
                {
                    px = i + Dx[k],py = j + Dy[k];
                    for (int l=1;l<=nearpoint;++l)
                        if (1 <= px && px <= SIZE && 1 <= py && py <= SIZE)
                    if (board[px][py] == 0 && !used[px][py])
                        {
                            pts[++size] = (rpoint){px,py},used[px][py] = 1;
                            sre[size] = pointvalue(board,pts[size],kind);
                            px += Dx[k], py += Dy[k];
                        }
          }
    }
    defencemode = false;// close this mode��ʾ�����ͷ���
    myqsort(pts,sre,1,size);
    if (sre[1] >= MAXSCORE)
		return -1; //�Ѿ���ʤ��
    if (sre[1] >= (MAXSCORE>>1))
		return 1;//OPPO win
    if (sre[1] >= 100000)
		return -1; //����
    if (factor >= 100){// �ҵ���ʤ��VCF
        if (sre[1]==FORBIDDEN)
			return FORBIDDEN;//if the max score point is FORBIDDEN��ʾ���ֲ�������
        int len = 0;
        for (int i=1;i<=size;++i)
            if (sre[i] >= factor)
                len++;
            else break;
        return len;
    }
    return size > gensize ? gensize : size; //select preferential points
}


///////////////////////////////////////////////
//��������: termpoint
//����: char[][], int, bool, char
//����ֵ: bool
//����: ���㵱ǰ�������Ƿ���ɱ�壬������ģ��
///////////////////////////////////////////////
bool termpoint(char board[][SIZE+2],int dep,bool iskiller,char kind)
{
    //if true,kler wins
    if (!dep)
		return depret = true,false;
    rpoint rpts[SIZE*SIZE+1]; // 225/8 approx 30  far more than reality
    int rnum = bestpoint(rpts,board,kind,iskiller ? 1000 : (defencemode = true,50000)); //����ģʽ
    if (rnum == FORBIDDEN)
		return !iskiller;
    if (rnum == 0)
		return false;
    if (rnum == -1)
		return nextx=rpts[1],iskiller;//Ѱ����һ���Ƿ���ɱ��
    for (int q=1;q<=rnum;++q)
    {
        int i = rpts[q].x, j = rpts[q].y;
        board[i][j] = kind;
        bool t = (board,dep-1,!iskiller,kind==1?2:1);
        board[i][j] = zero;
        if ( iskiller && t)
			return nextx = rpts[q],true;
        if (!iskiller && !t)
			return false;
    }
    return !iskiller;
}

/////////////////////////////////////////////////////
//��������: depsearch
//����: char [][], int, char, int, int
//����ֵ: int
//����:���ݹ��������棬����������Ծ���������֣�ȡ������ߵķ��ء����ã����ᣭ�������֦���������ʽ���������м��١�
//////////////////////////////////////////////////////
int depsearch(char board[][SIZE+2],int dep,char kind,int alpha,int beta)
{
    if (!dep)
        {
        depret = false;
        if (killdep != 0 && termpoint(board,killdep,1,kind))
			return MAXSCORE;//��ɱ��
        return (depret?1.5:1) * value(board,ckind) - value(board,hkind);
        }
    bool depfactor = false;
    if (dep == 1)
    {
        depret = false;
        if(defencedep != 0 && termpoint(board,defencedep,1,kind))
			return -MAXSCORE;//�Է��Ƿ���ɱ��
        depfactor = depret;
    }
    int maxnum = -2 * MAXSCORE;
    int ishuman=(kind == hkind);//�ж��Ƿ��ǶԷ�
    rpoint rpts[SIZE*SIZE+1];
    int rnum = bestpoint(rpts,board,kind,dep);//�ж��ٸ���õĵ�
    if (rnum == -1)
		return (ishuman?-1:1) * MAXSCORE;
    for (int q=1;q<=rnum;++q){
        int i = rpts[q].x, j = rpts[q].y;
        board[i][j] = kind;
        int t = (ishuman?-1:1) * depsearch(board,dep-1,kind==1?2:1,alpha,beta) * (depfactor?0.6:0.999);//��ȵ�Ԫ��
        board[i][j] = zero;
        if (t > maxnum)
            {
                maxnum = t;
            }//choosed[dep]=(rpoint){i,j};}
        if (ishuman){ //alpha-beta��֦
            if (-maxnum < beta)
				break;
            if (-maxnum < alpha)
                alpha = -maxnum;
        }else{
            if (maxnum > alpha)
				break;
            if (maxnum > beta)
				beta = maxnum;
        }//��֦�㷨
    }
    return (ishuman?-1:1)*maxnum;
}

////////////////////////////////////////////
//��������: inithash
//����: ��
//����ֵ: ��
//����: ��ʼ���������͹�ϣ�����������
/////////////////////////////////////////////
void inithash()
{
    srand(time(0));
    cpower();
    for (int k=0;k<=25;++k)
    {
        static unsigned long long thash[10];
        char rev[10];
        for (int i=1;i<=stype[k][0];++i)
            rev[i] = stype[k][stype[k][0]-i+1]; //symmetry
        pchash(thash,stype[k],stype[k][0],1);
        unsigned long long pt = thash[stype[k][0]]&TYPELENGTH;
        pchash(thash,rev,stype[k][0],1);
        unsigned long long ptr = thash[stype[k][0]]&TYPELENGTH;
        if (k == 0){shash[ptr] = shash[pt] = win;}else
        if (k == 1){shash[ptr] = shash[pt] = flex4;}else
        if (2 <= k && k <= 5){shash[ptr] = shash[pt] = block4;}else
        if (6 <= k && k <= 8){shash[ptr] = shash[pt] = flex3;}else
        if (8 <= k && k <= 14){shash[ptr] = shash[pt] = block3;}else
        if (15 <= k && k <= 19){shash[ptr] = shash[pt] = flex2;}else
        if (20 <= k && k <= 24){shash[ptr] = shash[pt] = block2;}else
        if (k == 25){shash[ptr] = shash[pt] = six;}
    }
}

/////////////////////////////////////////////////
//��������: zzAI
//����: int
//����ֵ: ��
//����: AI��������
//���ȵ����������������ɱ�壬���У���ֱ�����ӡ�
//����ѡ������ϵģ���㣬ʹ�ã��������еݹ��������֣�ȡ��ߵ÷ֵĵ���Ϊ���ӵ㡣�����������һ�£��������
/////////////////////////////////////////////////
void zzAI(int a)
{
   	srand((unsigned)time(NULL));
	int p = rand() % 6;//��������ѿ��ַ��������ѡȡ����ֹ���ÿ��ֿ�
	if(a == 1){
		switch (p)
		{
			case 0 : zzAIposition.x = 7; zzAIposition.y = 7; break;
			case 1 : zzAIposition.x = 6; zzAIposition.y = 7; break;
			case 2 : zzAIposition.x = 5; zzAIposition.y = 7; break;
			case 3 : zzAIposition.x = 6; zzAIposition.y = 8; break;
			case 4 : zzAIposition.x = 5; zzAIposition.y = 8; break;
			case 5 : zzAIposition.x = 5; zzAIposition.y = 9; break;
		}
		printf("Unluckily,zzAI first!\n");
	}
	else{
		static rpoint que[SIZE*SIZE+1];
    	int tal = 1;
    	int maxnum = -2*MAXSCORE;
    	nStep++;
		rpoint rpts[SIZE*SIZE+1];

		int rnum = bestpoint(rpts,nboard,ckind,50);
		if (rnum == 1)
        {
			nboard[rpts[1].x][rpts[1].y] = ckind;
			zzAIposition.x = (int)rpts[1].x-1;
			zzAIposition.y = (int)rpts[1].y-1;
			return;
		} // ��ֻ��һ��ѡ��ʱ
		int ntime = clock();

	   for(int dep = 1; /*(clock()-ntime) <= 3*CLOCKS_PER_SEC&&*/dep <= 10; dep+=1)
        {
        printf("Playround :%d\n",playround);
        depret = false;
        int t2 = clock();
        	if (termpoint(nboard,dep,true,ckind))
            {
            	if(nboard[nextx.x][nextx.y] == 0)
            	{
               		printf("%d %c\n",SIZE-nextx.x+1,nextx.y+'A'-1);
                	nboard[nextx.x][nextx.y]=ckind;
                	int t = depsearch(nboard,depsearchdep,hkind,2*MAXSCORE,maxnum);
                	printf("%d \n",t);
                	if (t >= -2000) {
						zzAIposition.x = (int)nextx.x - 1;
						zzAIposition.y = (int)nextx.y - 1;
						return;
					}
                	nboard[nextx.x][nextx.y] = zero;
                	break;
            	}else break;
        	}
        	if (clock() - t2 >= 2.0 * CLOCKS_PER_SEC) break;
        	if (!depret) break; //no solution to kill directly
    	}
    	printf("termination failed.\n");

		printf("AI is thinking...please wait��������");
    	for (int q=1;q<=rnum;++q)
    	{
        	int i = rpts[q].x, j = rpts[q].y;
        	nboard[i][j] = ckind;
        	int t = depsearch(nboard,depsearchdep,hkind,2*MAXSCORE,maxnum);// odd -> human's leaf
        	printf("%.2f%%\n",(float)q/rnum*100);
        	nboard[i][j] = zero;
        	if (t > maxnum) {
            	maxnum = t, tal = 1, que[0] = (rpoint){i,j};
            	if (t > (MAXSCORE>>1)) break;
        	}
        	else if (t == maxnum) {que[tal++] = (rpoint){i,j};}// printf("~~%d %d\n",i,j);}
        	if (clock()-ntime >= 20 * CLOCKS_PER_SEC) break;
    	}
   		for (int i=0;i<=tal-1;++i)
            printf("%d %d\n",que[i].x,que[i].y);
   		int ptt = rand()%tal;
   		nboard[que[ptt].x][que[ptt].y] = ckind;
		zzAIposition.x = (int)que[ptt].x-1;
		zzAIposition.y = (int)que[ptt].y-1;
	}
}

void oneplayer()
{
    int p, v, i, j;
    char s[10];
    player = 1;
	bool Turn=(order==1); // 1 for human's turn ; 0 for computer's turn.
    if (Turn) gensize=9,killdep=0,depsearchdep=9,defencedep=0;
        else  gensize=9,killdep=0,depsearchdep=9,defencedep=0;
    int step=0;
    //order=0?2:1;
    for(playround = 1; /*VictoryJudge(player) == 0*/; playround++,Turn^=1){
        player = 2 - playround % 2;
        if (order - player)
        {
            int t = clock();
			zzAI(playround);
            printf("TOTALTIME: %lf\n",(double)(clock()-t)/CLOCKS_PER_SEC);
            if (value(nboard,ckind) == MAXSCORE)
            {
				addmove(zzAIposition.x,zzAIposition.y,player);
				recordtoDisplayArray();
				displayBoard();
				printf("Sorry~ You are so foolish!zzAI wins!\n");
				break;
			}
            addmove(zzAIposition.x,zzAIposition.y,player);
            printf("x=%d, y=%c \n",15-zzAIposition.x,'A'+zzAIposition.y);
        }
        else{
 loop2:         printf("Playround :%d\n",playround);
                printf("It is your round to set a piece!(number comes first):\n");
            do{
                scanf("%s",s);
                char QUIT[] = "qunsigned long longt";
                if (!strcmp(s,QUIT))
                    exit(-1);
                else
                {
                    if (strlen(s)==3)
                {
                    xin=s[1]-'0'+10;
                    yin=s[2];
                }
                    else
                {
                    xin=s[0]-'0';
                    yin=s[1];
                }
                }
            }while((p = CordinateJudge(xin,yin)) < 0);

            CordinateTrans(xin,yin);
            if(aRecordBoard[x][y] == 0)
            {
                addmove(x,y,player);
				nboard[x+1][y+1]=Turn ? hkind : ckind;
			}
            else{
                printf("This position is illegal!\n");
                goto loop2;
            }
            if (hkind == 1 && (nboard,(rpoint){x,y},1) == FORBIDDEN){printf("FORBIDDEN POINT! You lose the game! \n");break;}
            if (value(nboard,hkind) == MAXSCORE){printf("Congratulations! You win!\n");break;}
        }
        recordtoDisplayArray();
        displayBoard();
		if (step == SIZE*SIZE){printf("What a miracle!You TIE~\n");break;}

    }

}

//�˻���ս
void twoplayers()
{
    int p,v;
    char s[10];
    player = 1;
	for (playround = 1; ifwin(player) == 0; playround++){
        player = 2 - playround % 2;
loop:   printf("It is your round! Choose a place to set a piece, player %d (number comes first):\n", player);
		do{

        scanf("%s",s);
        char QUIT[] = "qunsigned long longt";
        if (!strcmp(s,QUIT))
            exit(-1);
        else
        {
            if (strlen(s)==3)
            {
                xin=s[1]-'0'+10;
                yin=s[2];
            }
            else
            {
                xin=s[0]-'0';
                yin=s[1];
            }

        }
        }while((p = CordinateJudge(xin, yin)) < 0);
        CordinateTrans(xin,yin);
		if(aRecordBoard[x][y] == 0)
            addmove(x,y,player);
        else{
            printf("This position is illegal!\n");
            goto loop;
        }
		recordtoDisplayArray();
		displayBoard();
    }
    switch (v = ifwin(player)){
        case 1 : printf("Player 1 wins!\n");
                 break;
        case 2 : printf("Player 2 wins!\n");
                 break;
    }
}
//˫�˶�ս
int ifwin(int player)
{
    int tempx = current_x, tempy = current_y;
    condition.horizontal = condition.vertical = condition.lean1 = condition.lean2 = 0;

    while(++tempx < SIZE && aRecordBoard[tempx][current_y] == player)
        condition.horizontal++;
    tempx = current_x;
    while(--tempx >= 0 && aRecordBoard[tempx][current_y] == player)
        condition.horizontal++;
    tempx = current_x;
    if (condition.horizontal + 1 >= 5)
        return player;           // Horizontal victory judgement

    while(++tempy < SIZE && aRecordBoard[current_x][tempy] == player)
        condition.vertical++;
    tempy = current_y;
    while(--tempy < SIZE && aRecordBoard[x][tempy] == player)
        condition.vertical++;
    tempy = current_y;
    if (condition.vertical + 1 >= 5)
        return player;          // Vertical victory judgement

    while(++tempx < SIZE && ++tempy < SIZE && aRecordBoard[tempx][tempy] == player)
        condition.lean1++;
    tempx = current_x;
    tempy = current_y;
    while(--tempx >= 0 && --tempy >= 0 && aRecordBoard[tempx][tempy] == player)
        condition.lean1++;
    tempx = current_x;
    tempy = current_y;
    if (condition.lean1 + 1 >= 5)
        return player;          // Bias victory judgement

    while(++tempx < SIZE && --tempy >= 0 && aRecordBoard[tempx][tempy] == player)
        condition.lean2++;
    tempx = current_x;
    tempy = current_y;
    while(--tempx >= 0 && ++tempy < SIZE && aRecordBoard[tempx][tempy] == player)
        condition.lean2++;
    tempx = current_x;
    tempy = current_y;
    if(condition.lean2 + 1 >= 5)
        return player;          // Bias victory judgement'
    return 0;
}

//�ж��Ƿ�ʤ��


void addmove(int x,int y, int player){
	aRecordBoard[x][y]=player+2;
    if (current_x!= -1)
	    aRecordBoard[current_x][current_y] -= 2;
    current_x=x;
	current_y=y;
}
//����

int CordinateJudge(int x, char y){
    if(x <= 15 && x >= 1)
        if((y >= 'a' && y <= 'o') || (y >= 'A' && y <= 'O'))
            return 1;
	printf("Please enter a correct cordinate!\n");
    return -1;
}
//�Ƿ�Խ���ж�
void CordinateTrans(int a, char b){
    xp = &x;
    yp = &y;
    *xp = 15 - a;
    if (b >= 'a' && b <= 'o')
        *yp = b - 'a';
    else
        *yp = b - 'A';
}
//���Դ�СдӰ��

void initRecordBorard(void){
    int i, j;
    for (i = 0; i < SIZE; ++i)
    for (j = 0; j < SIZE; ++j)
            aRecordBoard[i][j] = 0;
//ͨ��˫��ѭ������aRecordBoard��0
    for(int i=0;i<=SIZE+1;++i)
        for (int j=0;j<=SIZE+1;++j)
            nboard[i][j]=-1;
    for(int i=1;i<=SIZE;++i)
        for (int j=1;j<=SIZE;++j)
            nboard[i][j]=0;
}

//��aRecordBoard�м�¼������λ�ã�ת����aDisplayBoardArray��
void recordtoDisplayArray(void){
	int i,j;
    for (i = 0; i < SIZE; ++i)
        for (j = 0; j < SIZE * 2 + 1; ++j)
            aDisplayBoardArray[i][j] = aInitDisplayBoardArray[i][j];
    for (i = 0; i < SIZE; ++i)
        for (j = 0; j < SIZE; ++j)
            switch(aRecordBoard[i][j]){
                case 1 : aDisplayBoardArray[i][2*j] = play1Pic[0];
			 			 aDisplayBoardArray[i][2*j+1] = play1Pic[1];
                         break;
                case 2 : aDisplayBoardArray[i][2*j] = play2Pic[0];
						 aDisplayBoardArray[i][2*j+1] = play2Pic[1];
                         break;
                case 3 : aDisplayBoardArray[i][2*j] = play1CurrentPic[0];
						 aDisplayBoardArray[i][2*j+1] = play1CurrentPic[1];
                         break;
                case 4 : aDisplayBoardArray[i][2*j] = play2CurrentPic[0];
						 aDisplayBoardArray[i][2*j+1] = play2CurrentPic[1];
                         break;
            }
//��һ������aInitDisplayBoardArray�м�¼�Ŀ����̣����Ƶ�aDisplayBoardArray��
//�ڶ�����ɨ��aRecordBoard����������0��Ԫ�أ�������ߡ��Ƶ�aDisplayBoardArray����Ӧλ����
//ע�⣺aDisplayBoardArray����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽڡ�
}


//��ʾ���̸��
void displayBoard(void){
	int i,j;
	//system("cls");
	printf("          ----five from King----     \n\n");
    for (i=0; i<SIZE;++i)
        printf("   %3d %s\n",15-i,aDisplayBoardArray[i]);
	printf("        ");
	for (i=0; i<SIZE;++i)
		printf("%c ",'A'+i);
	printf("\n");


	//��һ��������
	 //����
	//�ڶ�������aDisplayBoardArray�������Ļ��


	//������������������һ����ĸA B ....
}



