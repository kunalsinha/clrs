#include <stdio.h>
#include <malloc.h>

int max(int a, int b);

int main()
{
    int i, j;
    int *cur;
    char *sstring, *lstring;
    //char x[M] = {'D', 'B', 'C', 'A', '\0'};
    //char y[N] = {'C', 'D', 'B', 'C', 'A', 'D', '\0'};
    //char *x = "ABCBDAB";
    //char *y = "BDCABA";
    char *x = "10010101";
    char *y = "010110110";
    int x_size, y_size;
    int small, big;
    int dia, temp;
    
    i = 0;
    while(x[i] != '\0')
        i++;
    x_size = i;
    i = 0;
    while(y[i] != '\0')
        i++;
    y_size = i;
    
    if(x_size < y_size)
    {
        small = x_size;
        sstring = x;
        big = y_size;
        lstring = y;
    }
    else
    {
        small = y_size;
        sstring = y;
        big = x_size;
        lstring = x;
    }
    
    cur = (int *)malloc(sizeof(int)*(small+1));
    
    for(i=0; i<=small; i++)
        cur[i] = 0;
    
    for(i=0; i<big; i++)
    {
        dia = 0;
        for(j=0; j<small; j++)
        {
            if(lstring[i] == sstring[j])
            {
                temp = cur[j+1];
                cur[j+1] = 1 + dia;
                dia = temp;
            }
            else
            {
                dia = cur[j+1];
                cur[j+1] = max(cur[j], cur[j+1]);
            }
        }
    }
    printf("Length of longest common subsequence = %d\n", cur[small]);
    return 1;
}

int max(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}
