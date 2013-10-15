#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int binary_search(int *list, int left, int right, int key);
int print_lis(int *seq, int *ser, int index);

int main()
{

    //int seq[] = {24, 5, 12, 29, 11, 10, 26, 29, 24, 21, 50, 7, 6, 8};
    int seq[] = {24, 5, 12, 29, 11, 10, 26, 32, 2, 5, 7, 29, 37, 83};
    int *lis, *ser, *lis_index;
    int size, i, key, pos, right;
    
    size = sizeof(seq)/sizeof(int);
    lis = (int *)malloc(sizeof(int) * (size+1));
    lis_index = (int *)malloc(sizeof(int) * (size+1));
    ser = (int *)malloc(sizeof(int) * (size+1));
    right = 0;
    lis[0] = INT_MIN;
    lis_index[0] = 0;
    ser[0] = 0;
    
    for(i=0; i<size; i++)
    {
        key = seq[i];
        if(key >= lis[right])
        {
            ser[i] = lis_index[right];
            lis[++right] = key;
            lis_index[right] = i;
        }
        else
        {
            pos = binary_search(lis, 1, right, key);
            lis[pos] = key;
            lis_index[pos] = i;
            ser[i] = lis_index[pos-1];
        }
    }
    print_lis(seq, ser, lis_index[right]);
    printf("\nLength of longest increasing subsequence: %d\n", right);
    return 1;
}

int binary_search(int *list, int left, int right, int key)
{
    int mid;
    if(left > right)
        return -1;
    mid = (left + right) / 2;
    if(*(list + mid) > key)
    {
        if(*(list+mid-1) < key)
            return mid;
        else
            binary_search(list, left, mid-1, key);
    }
    else
        binary_search(list, mid+1, right, key);
    
}

int print_lis(int *seq, int *ser, int index)
{
    if(index == 0)
        return -1;
    print_lis(seq, ser, ser[index]);
    printf("%d ", seq[index]);
}