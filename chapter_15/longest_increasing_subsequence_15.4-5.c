#include <stdio.h>
#include <stdlib.h>

int print_lis(int seq[], int ser[], int x);

int main()
{

int seq[] = {24, 5, 12, 29, 11, 10, 26, 32, 2, 5, 7, 29, 37, 83};
int i, j, max;
int size, last_element;
int *lis, *ser;

size = sizeof(seq)/sizeof(int);
lis = (int *)malloc(size * sizeof(int));
ser = (int *)malloc(size * sizeof(int));
lis[0] = 1;
ser[0] = 0;
for(i=1; i<size; i++)
{
    lis[i] = 1;
    ser[i] = i;
    for(j=i-1; j>=0; j--)
    {
        if((seq[j] < seq[i]) && ((lis[j]+1) > lis[i]))
        {
            lis[i] = lis[j] + 1;
            ser[i] = j;
        }
    }
}

max = 1;
for(i=0; i<size; i++)
{
    if(lis[i] > max)
    {
        max = lis[i];
        last_element = i;
    }
}
printf("Length of longest increasing subsequence: %d\n", max);

print_lis(seq, ser, last_element);
printf("\n");

return 1;
}

int print_lis(int seq[], int ser[], int x)
{
    if(ser[x] == x)
    {
        printf("%d ", seq[x]);
        return 1;
    }
    else
    {
        print_lis(seq, ser, ser[x]);
        printf("%d ", seq[x]);
    }
    return 1;
}