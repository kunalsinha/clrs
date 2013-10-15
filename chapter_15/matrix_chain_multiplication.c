#include <stdio.h>
#include <limits.h>
#define SIZE 5
void print_optimal_chaining(int s[][SIZE+1], int i, int j);
int main()
{
    int l, i, j, k, q;
    int m[SIZE+1][SIZE+1], s[SIZE+1][SIZE+1];
    int p[SIZE+1] = {8,2,9,20,6,5};
    for(i=0; i<=SIZE; i++)
    {
        m[i][i] = 0;
        s[i][i] = 0;
    }
    for(l=1; l<SIZE; l++)
    {
        for(i=1; i<SIZE-l+1; i++)
        {
            j = i + l;
            m[i][j] = INT_MAX;
            printf("%d %d\n", i, j);
            for(k=i; k<j; k++)
            {
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if(q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                    printf("m[%d][%d] = %d split at %d\n", i, j, m[i][j], k);
                }
            }
        }
        printf("\n");
    }
    print_optimal_chaining(s, 1, SIZE);
    printf("\n");
    return 0;
}

void print_optimal_chaining(int s[][SIZE+1], int i, int j)
{
    if(i==j)
        printf("%d", i);
    else
    {
        printf("(");
        print_optimal_chaining(s, i, s[i][j]);
        print_optimal_chaining(s, s[i][j]+1, j);
        printf(")");
    }
}