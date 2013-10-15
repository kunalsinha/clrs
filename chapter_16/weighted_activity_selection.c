#include <stdio.h>
#include <stdlib.h>

int binary_search(int *f, int left, int right, int key);

int main()
{
    int s[] = {0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
    int f[] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};
    int w[] = {0, 4, 6, 2, 5, 1, 6, 0, 3, 2, 4, 2};
    
    
    //int s[] = {0,2,3,2};
    //int f[] = {0,4,7,11};
    
    int n = sizeof(s)/sizeof(int);
    int *sol, *p, *tracker;
    int i, sol1, sol2;
    
    sol = (int *) malloc(sizeof(int) * (n+1));
    p = (int *) malloc(sizeof(int) * (n+1));
    tracker = (int *) malloc(sizeof(int) * (n+1));
    
    *(sol+0) = 0; //better written as *sol = 0
    for(i=1; i<=n; i++)
        *(tracker+i) = -1;
    
    
    //Fill the array p
    for(i=1; i<=n; i++)
        p[i] = binary_search(f, 0, i, s[i]);
    
    for(i=1; i<=n; i++)
    {
        sol1 = w[i] + sol[p[i]];
        sol2 = sol[i-1];
        if(sol1 >= sol2)
        {
            sol[i] = sol1;
            tracker[i] = p[i];
        }
        else
            sol[i] = sol2;
    }
    
    printf("Maximum weight of activities that can be scheduled = %d\n", sol[n]);
    i = n;
    while(1)
    {
        if(tracker[i] == -1)
        {
            i--;
            continue;
        }
        else if(tracker[i] == 0)
        {
            printf("%d-%d\n", s[i], f[i]);
            break;
        }
        else
        {
            printf("%d-%d\n", s[i], f[i]);
            i = p[i];
        }
    }
    
    return 1;
}

int binary_search(int *f, int left, int right, int key)
{
    int mid;
    static int index = 0;
    
    if(left > right)
        return index;
    
    mid = (left+right)/2;
    if(*(f+mid) <= key)
    {
        index = mid;
        return binary_search(f, mid+1, right, key);
    }
    else
        return binary_search(f, left, mid-1, key);
}
