#include <stdio.h>
#include <stdlib.h>

int main()
{
    int s[] = {0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    int f[] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
    
    int n = sizeof(s)/sizeof(int);
    int i, m, *sol, sol_length;
    
    sol = (int *) malloc(sizeof(int) * n);
    for(i=0; i<n; i++)
        *(sol+i) = -1;
    
    sol_length = 0;
    m = 0;
    for(i=1; i<n; i++)
    {
        if(s[i] >= f[m])
        {
            sol[sol_length++] = i;
            m = i;
        }
    }
    
    for(i=0; i<sol_length; i++)
        printf("%d-%d\n", s[sol[i]], f[sol[i]]);
    
    return 1;
}
