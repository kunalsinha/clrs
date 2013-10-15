#include <stdio.h>
#include <stdlib.h>


int main()
{
    int capacity = 200;
    int v[] ={120, 60, 100, 45, 80, 20, 120};
    int w[] = {80, 20, 30, 60, 70, 20, 100};
    
    int **sol, **tracker;
    int n = sizeof(v)/sizeof(int);
    int i, j, sol1, sol2;
    
    sol = (int **)malloc(sizeof(int *) * (n+1));
    for(i=0; i<=n; i++)
        sol[i] = (int *) malloc(sizeof(int) * (capacity+1));
    for(i=0; i<=n; i++)
        for(j=0; j<=capacity; j++)
            sol[i][j] = 0;
            
    tracker  = (int **) malloc(sizeof(int *) * (n+1));
    for(i=0; i<=n; i++)
        tracker[i] = (int *) malloc(sizeof(int) * (capacity+1));
    for(i=0; i<=n; i++)
        for(j=0; j<=capacity; j++)
            tracker[i][j] = -1;
        
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=capacity; j++)
        {
            if(w[i-1] > j)
            {
                sol[i][j] = sol[i-1][j];
            }
            else
            {
                sol1 = v[i-1] + sol[i-1][j-w[i-1]];
                sol2 = sol[i-1][j];
                if(sol1 >= sol2)
                {
                    sol[i][j] = sol1;
                    tracker[i][j] = 0;
                }
                else
                    sol[i][j] = sol2;
            }
        }
    }
    
    printf("Max value that can be carried = %d\n", sol[n][capacity]);
    
    printf("value weight\n");
    i = n;
    j = capacity;
    while(i >= 0)
    {
        if(tracker[i][j] == -1)
            i--;
        else
        {
            printf("%5d %5d\n", v[i-1], w[i-1]);
            j -= w[i-1];
            i--;
        }
    }
    printf("\n");
    
    return 1;
}
