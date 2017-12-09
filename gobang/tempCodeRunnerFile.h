#ifndef BOUNDRY
#define BOUNDRY 15
#endif

srand(SEED);
unsigned long int zobrist_table[BOUNDRY][BOUNDRY][2];
for (int i = 0; i < BOUNDRY * BOUNDRY * 2;i++)
{
    zobrist_table + i = rand();
    printf("%lu ", zobrist_table + i);
}