#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void min_heapify(int *a, int i, int heap_size);
int parent(int i);
int left_child(int i);
int right_child(int i);
void swap(int *a, int x, int y);
int minimum(int *a, int heap_size);
int extract_minimum(int *a, int *heap_size);
void decrease_key(int *a, int i, int key, int heap_size);
void insert(int *a, int key, int *heap_size);
void print_priority_queue(int *a, int heap_size);
int delete(int *a, int i, int *heap_size);

int main()
{
    int *a;
    int heap_size = 0;
    char ch, buffer[512];
    int key, index, min, size;
    
    printf("Enter size of the priority queue: ");
    fgets(buffer, 511, stdin);
    sscanf(buffer, "%d", &size);
    
    a = (int *) malloc(sizeof(int) * size);
    
    do
    {
        printf("1> Enter i to insert a number in priority queue\n");
        printf("2> Enter c to delete a number from priority queue\n");
        printf("3> Enter d to decrease key\n");
        printf("4> Enter g to see minimum value in priority queue\n");
        printf("5> Enter m to retrieve maximum value in priority queue\n");
        printf("6> Enter p to print the priority queue\n");
        printf("7> Enter e to exit\n");
        fgets(buffer, 511, stdin);
        sscanf(buffer, "%c", &ch);
        switch(ch)
        {
            case 'i':
                if(heap_size < size)
                {
                    printf("Enter the key to insert: ");
                    fgets(buffer, 511, stdin);
                    sscanf(buffer, "%d", &key);
                    insert(a, key, &heap_size);
                    printf("Key inserted successfully\n");
                }
                else
                    printf("Priority queue overflow\n");
                break;
            case 'c':
                printf("Enter index to delete: ");
                fgets(buffer, 511, stdin);
                sscanf(buffer, "%d", &index);
                if(delete(a, index, &heap_size) != -1)
                    printf("Key deleted successfully\n");
                break;
            case 'd':
                printf("Enter index to be decrease: ");
                fgets(buffer, 511, stdin);
                sscanf(buffer, "%d", &index);
                printf("Enter new key less than the previous: ");
                fgets(buffer, 511, stdin);
                sscanf(buffer, "%d", &key);
                decrease_key(a, index, key, heap_size);
                printf("Key decreased successfully\n");
                break;
            case 'g':
                min = minimum(a, heap_size);
                if(min != -1)
                    printf("Minimum value in priority queue = %d\n", min);
                break;
            case 'm':
                min = extract_minimum(a, &heap_size);
                if(min != -1)
                    printf("Minimum value in priority queue = %d\n", min);
                break;
            case 'p':
                print_priority_queue(a, heap_size);
                break;
            case 'e':
                printf("Exiting\n");
                break;
            default:
                printf("Try again\n");
                break;
        }
    }
    while(ch != 'e');
    
    return 1;
}

int delete(int *a, int i, int *heap_size)
{
    int key;
    if(i >= *heap_size)
        printf("Invalid index: larger than heap size\n");
    else
    {
        key = *(a+(*heap_size)-1);
        *heap_size -= 1;
        if(key < *(a+i))
            decrease_key(a, i, key, *heap_size);
        else
        {
            *(a+i) = key;
            print_priority_queue(a, *heap_size);
            min_heapify(a, i, *heap_size);
        }
        return 0;
    }
}

void print_priority_queue(int *a, int heap_size)
{
    int i;
    for(i=0; i<heap_size; i++)
        printf("%d ", *(a+i));
    printf("\n");
}

int minimum(int *a, int heap_size)
{
    if(heap_size < 1)
    {
        printf("No items in the priority queue\n");
        return -1;
    }
    return *(a+0);
}

int extract_minimum(int *a, int *heap_size)
{
    int min;
    if(*heap_size < 1)
    {
        printf("No items in the priority queue\n");
        return -1;
    }
    min = *(a+0);
    swap(a, 0, *heap_size-1);
    *heap_size -= 1;
    min_heapify(a, 0, *heap_size);
    return min;
}

void decrease_key(int *a, int i, int key, int heap_size)
{
    if(i >= heap_size)
        printf("Invalid index: larger than heap size\n");
    else if(key > *(a+i))
        printf("Entered key %d is greater than value at index %d: %d\n", key, i, *(a+i));
    else
    {
        *(a+i) = key;
        while(i>0 && *(a+parent(i)) > *(a+i))
        {
            swap(a, parent(i), i);
            i = parent(i);
        }
    }
}

void insert(int *a, int key, int *heap_size)
{
    *(a+(*heap_size)) = INT_MAX;
    *heap_size += 1;
    decrease_key(a, *heap_size-1, key, *heap_size);
}

void min_heapify(int *a, int i, int heap_size)
{
    int smaller, j;
    int left;
    int right;
    
    if(i >= heap_size)
        printf("Invalid index: larger than heap size\n");
    else
    {
        left = left_child(i);
        right = right_child(i);
        
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