#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int max(int a, int b);

int main()
{
    //char *input = "dhfkjshkyeyugdhjsasffgjanljdasrf";
    char *input = "ALGORITHMSISAGREATCLASS";
    int len, i, j;
    int **lps;
    
    len = strlen(input);
    lps = (int **) malloc(sizeof(int *) * (len));
    for(i=0; i<len; i++)
        lps[i] = (int *) malloc(sizeof(int) * (len));
    for(i=0; i < len; i++)
        lps[i][i] = 1;

    for(i=len-2; i>=0; i--)
        for(j=i; j<len; j++)
            if(i != j)
                if(input[i] == input[j])
                    lps[i][j] = lps[i+1][j-1] + 2;
                else
                    lps[i][j] = max(lps[i][j-1], lps[i+1][j]);
    
    printf("Length of longest palindrome subsequence: %d\n", lps[0][len-1]);
    for(i=0; i<len; i++)
    {
        for(j=0; j<len; j++)
            printf("%3d ", lps[i][j]);
        printf("\n");
    }
    return 1;
}

int max(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}
