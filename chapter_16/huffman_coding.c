#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node *huffman_coding(char *characters, int *freq, int num_chars);
void print_pq(struct node **priority_queue, int size);
void print_character_codes(struct node *root);

void min_heapify(struct node **priority_queue, int i, int heap_size);
int parent(int i);
int left_child(int i);
int right_child(int i);
void swap(struct node **priority_queue, int x, int y);
struct node *minimum(struct node **priority_queue, int heap_size);
struct node *extract_minimum(struct node **priority_queue, int *heap_size);
void decrease_key(struct node **priority_queue, int i, struct node *key, int heap_size);
void insert(struct node **priority_queue, struct node *key, int *heap_size);
//int delete(int *a, int i, int *heap_size);

struct node
{
    char ch;
    int frequency;
    struct node *left, *right;
};

int main()
{
    char characters[] = {'a','b','c','d','e','f'};
    int frequency[] = {45,13,12,16,9,5};
    int num_chars;
    struct node *root = NULL;
    
    num_chars = sizeof(frequency)/sizeof(int);
    root = huffman_coding(characters, frequency, num_chars);
    //if(root != NULL)
    //    printf("%d\n", root->frequency);
    
    print_character_codes(root);
    return 1;
}

struct node *huffman_coding(char *characters, int *frequency, int num_chars)
{
    struct node **priority_queue, *n, *left, *right;
    int heap_size = 0;
    int i;
    
    priority_queue = (struct node **) malloc(sizeof(struct node *) * num_chars);
    
    //initialize the priority queue
    for(i=0; i<num_chars; i++)
    {
        if(heap_size < num_chars)
        {
            n = (struct node *) malloc(sizeof(struct node));
            n->ch = *(characters+i);
            n->frequency = *(frequency+i);
            n->left = n->right = NULL;
            insert(priority_queue, n, &heap_size);
        }
        else
            printf("Priority Queue overflow\n");
    }
    
    for(i=0; i<num_chars-1; i++)
    {
        left = extract_minimum(priority_queue, &heap_size);
        right = extract_minimum(priority_queue, &heap_size);
        n = (struct node *) malloc(sizeof(struct node));
        n->left = left;
        n->right = right;
        n->frequency = left->frequency + right->frequency;
        insert(priority_queue, n, &heap_size);
    }
    
    return minimum(priority_queue, heap_size);
}

void insert(struct node **priority_queue, struct node *key, int *heap_size)
{
    struct node *temp;
    temp = (struct node *) malloc(sizeof(struct node));
    temp->frequency = INT_MAX;
    temp->left = temp->right = NULL;
    *(priority_queue + *heap_size) = temp;
    *heap_size += 1;
    decrease_key(priority_queue, *heap_size-1, key, *heap_size);
    free(temp);
}

struct node *extract_minimum(struct node **priority_queue, int *heap_size)
{
    struct node *min;
    if(*heap_size < 1)
    {
        printf("No items in the priority queue\n");
        return NULL;
    }
    min = *(priority_queue+0);
    swap(priority_queue, 0, *heap_size-1);
    *heap_size -= 1;
    min_heapify(priority_queue, 0, *heap_size);
    return min;
}

struct node *minimum(struct node **priority_queue, int heap_size)
{
    if(heap_size < 1)
    {
        printf("No items in the priority queue\n");
        return NULL;
    }
    return *(priority_queue+0);
}

void min_heapify(struct node **priority_queue, int i, int heap_size)
{
    int smaller;
    int left;
    int right;
    
    if(i < heap_size)
    {
        left = left_child(i);
        right = right_child(i);
        
        smaller = i;
        if(left < heap_size && (*(priority_queue+left))->frequency < (*(priority_queue+i))->frequency)
            smaller = left;
        if(right < heap_size && (*(priority_queue+right))->frequency < (*(priority_queue+smaller))->frequency)
            smaller = right;
        
        if(smaller != i)
        {
            swap(priority_queue, i, smaller);
            min_heapify(priority_queue, smaller, heap_size);
        }
    }
}

void decrease_key(struct node **priority_queue, int i, struct node *key, int heap_size)
{
    if(i >= heap_size)
        printf("Invalid index: larger than heap size\n");
    else if(key->frequency > (*(priority_queue+i))->frequency)
        printf("Entered key frequency %d is greater than frequency at index %d: %d\n", key->frequency, i, (*(priority_queue+i))->frequency);
    else
    {
        *(priority_queue+i) = key;
        while(i>0 && (*(priority_queue+parent(i)))->frequency > (*(priority_queue+i))->frequency)
        {
            swap(priority_queue, parent(i), i);
            i = parent(i);
        }
    }
}

void swap(struct node **priority_queue, int x, int y)
{
    struct node *temp;
    temp = *(priority_queue+x);
    *(priority_queue+x) = *(priority_queue+y);
    *(priority_queue+y) = temp;
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

void print_pq(struct node **priority_queue, int size)
{
    int i;
    for(i=0; i<size; i++)
        printf("%c ", (*(priority_queue+i))->ch);
    printf("\n");
}

/*int delete(int *a, int i, int *heap_size)
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
}*/

void print_character_codes(struct node *root)
{
    static int code[7];
    static int code_size = 0;
    int i;
    
    if(root != NULL)
    {
        if(root->left != NULL)
        {
            code[code_size++] = 0;
            print_character_codes(root->left);
        }
        if(root->right != NULL)
        {
            code[code_size++] = 1;
            print_character_codes(root->right);
        }
        if(root->left == NULL && root->right == NULL)
        {
            printf("%c - ", root->ch);
            for(i=0; i<code_size; i++)
                printf("%d", code[i]);
            printf("\n");
        }
        code_size--;
    }
}
