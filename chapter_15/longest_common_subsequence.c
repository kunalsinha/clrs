#include <stdio.h>
#define M 8
#define N 9

void print_lcs(char dir[M+1][N+1], char x[M], int i, int j);

int main()
{
    int i, j;
    int lcs[M+1][N+1];
    char dir[M+1][N+1];
    //char x[M] = {'D', 'B', 'C', 'A', '\0'};
    //char y[N] = {'C', 'D', 'B', 'C', 'A', 'D', '\0'};
    //char *x = "ABCBDAB";
    //char *y = "BDCABA";
    char *x = "10010101";
    char *y = "010110110";
    
    for(j=0;j<=N;j++)
    {
        lcs[0][j] = 0;
        dir[0][j] = '0';
    }
        
    for(i=0;i<=M;i++)
    {
        lcs[i][0] = 0;
        dir[i][0] = '0';
    }
        
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            if(x[i] == y[j])
            {
                lcs[i+1][j+1] = 1 + lcs[i][j];
                dir[i+1][j+1] = 'd';
            }
            else if(lcs[i+1][j] > lcs[i][j+1])
            {
                lcs[i+1][j+1] = lcs[i+1][j];
                dir[i+1][j+1] = 'l';
            }
            else
            {
                lcs[i+1][j+1] = lcs[i][j+1];
                dir[i+1][j+1] = 'u';
            }
        }
    }
    for(i=0;i<=M;i++)
    {
        for(j=0;j<=N;j++)
            printf("%c ", dir[i][j]);
        printf("\n");
    }
    printf("Length of longest common subsequence of %s and %s is %d\n", x, y, lcs[M][N]);
    print_lcs(dir, x, M, N);
    printf("\n");
    return 1;
}

void print_lcs(char dir[M+1][N+1], char x[M], int i, int j)
{
    if(i<0 || j<0)
        return;
    if(dir[i][j] == 'd')
    {
        print_lcs(dir, x, i-1, j-1);
        printf("%c", x[i-1]);
    }
    else if(dir[i][j] == 'u')
        print_lcs(dir, x, i-1, j);
    else
        print_lcs(dir, x, i, j-1);
}
