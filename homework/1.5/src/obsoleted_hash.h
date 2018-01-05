//obsoleted_hash implemention in gobang project;
//Used chaintable;

int _ndefZobchain = 1;

struct _ZobChain
{
    int (*boardrecord)[BOUNDRY];
    double weight;
    struct _ZobChain *next;
};
int (*BoardRec())[BOUNDRY]
//malloc memory to save the board now, meanwhile, return the point foe saved board.
{
    int(*result)[BOUNDRY] = (int(*)[BOUNDRY])malloc(sizeof(int) * BOUNDRY * BOUNDRY);
    // memcpy(result, board, BOUNDRY * BOUNDRY * sizeof(int));
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            result[a][b] = board[a][b];
        }
    }
    return result;
}

int BoardCmp(int (*boarda)[BOUNDRY], int (*boardb)[BOUNDRY])
{
    for (int a = 0; a < BOUNDRY; a++)
    {
        for (int b = 0; b < BOUNDRY; b++)
        {
            if (boarda[a][b] < boardb[a][b])
                return -1;
            if (boarda[a][b] > boardb[a][b])
                return 1;
        }
    }
    return 0;
}

double FindinZobChain(unsigned long int zob, double **_socket)
//Remark: the status of this function is defined at double *_zobnewweight = 0;
// _weight= FindinZobChain();
// if (_zobnewweight == 0) {_weight = newweight();*_zobnewweight=_weight;}
// else goon;
{

    struct _ZobChain *_lastpoint = hashtable[zob];
    struct _ZobChain *current;

    //emptylist

    if (hashtable[zob] == 0)
    {
        hashtable[zob] = (struct _ZobChain *)malloc(sizeof(struct _ZobChain));
        current = hashtable[zob];
        // current->boardrecord = 0;
        // puts("new line!");
        current->next = 0;
        current->boardrecord = BoardRec();
        *_socket = &(current->weight);
        return 0;
    }
    else
    {
        current = hashtable[zob];
    }
    //nonemptylist
    do
    {
        if (BoardCmp(current->boardrecord, board) == 1)
        {
            _lastpoint = current;
            if (current->next == 0)
            {
                //add here
                // puts("new end!");

                current->next = (struct _ZobChain *)malloc(sizeof(struct _ZobChain));
                current->next->next = 0;
                current->next->boardrecord = BoardRec();
                *_socket = &(current->next->weight);
                return 0;
            }
            current = current->next;
            // printf("%p\n", current);
            continue;
        }
        if (BoardCmp(current->boardrecord, board) == 0)
        {
            // puts("read!");
            *_socket = 0;
            return current->weight;
        }
        if (BoardCmp(current->boardrecord, board) == -1)
        {
            //add here;
            // puts("new in!");
            _lastpoint = (struct _ZobChain *)malloc(sizeof(struct _ZobChain));
            _lastpoint->next = current;
            _lastpoint->boardrecord = BoardRec();
            *_socket = &(_lastpoint->weight);
            return 0;
        }

        BOOM("Undefed sit!");
    } while (1);
}

double FindInHashTable(double **_socket)
{
    unsigned long int zob = Getzob();
    return FindinZobChain(zob, _socket);
}