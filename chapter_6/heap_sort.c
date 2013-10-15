#include <stdio.h>

void build_min_heap(int *a, int length);
void min_heapify(int *a, int i, int heap_size);
void heap_sort(int *a, int length);
int parent(int i);
int left_child(int i);
int right_child(int i);
void swap(int *a, int x, int y);

int main()
{
    int a[] = {43,21,14,76,34,10,38,91,84,26,62,72,24};
    int length = sizeof(a)/sizeof(int);
    int i;
    
    build_min_heap(a, length);
    heap_sort(a, length);
    
    for(i=0; i<length; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 1;
}

void build_min_heap(int *a, int length)
{
    int i, j;
    for(i=parent(length-1); i>=0; i--)
        min_heapify(a, i, length);
}

void min_heapify(int *a, int i, int heap_size)
{
    int smaller, j;
    int left = left_child(i);
    int right = right_child(i);
    
    smaller = i;
    if(left < heap_size && *(a+left) < *(a+i))
        smaller = left;
    if(right < heap_size && *(a+right) < *(a+smaller))
        smaller = right;
        
    if(smaller != i)
    {
        swap(a, i, smaller);
        min_heapify(a, smaller, heap_size);
    }
}

void heap_sort(int *a, int length)
{
    int heap_size = length;
    int i;
    
    for(i=heap_size-1; i>0; i--)
    {
        swap(a, 0, i);
        heap_size--;
        min_heapify(a, 0, heap_size);
    }
}

int parent(int i)
{
    if(i%2 == 0)
        return (i-2)/2;
    else
        return (i-1)/2;
}

int left_child(int i)
{
    return (2*i)+1;
}

int right_child(int i)
{
    return (2*i)+2;
}

void swap(int *a, int x, int y)
{
    int temp;
    temp = *(a+x);
    *(a+x) = *(a+y);
    *(a+y) = temp;
}
