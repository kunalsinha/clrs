#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct node
{
    int id;
    char *name;
    long d;
    char c;
    struct node *p;
};

struct item
{
    int vertex;
    struct item *next;
};

struct entry
{
    struct node *v;
    struct entry *next;
};

void add_edge(struct item **node, int vertex);
void display_edges(struct item *vertex, struct node *nodes, int num_nodes);
void push(struct entry **queue, struct node *v);
struct node *pop(struct entry **queue);
int empty(struct entry *queue);
void display_queue(struct entry *queue);
void print_path(struct node *source, struct node *dest);
int find_vertex(struct node *nodes, int num_nodes, char *vertex);

int main()
{
    char buffer[128], z[128];
    int num_nodes;
    struct node *nodes;
    int i, edge;
    char name[128];
    struct item **adj, *ptr;
    struct node *u;
    int source;
    struct entry *queue = NULL;
    
    printf("Enter nuber of nodes: ");
    fgets(buffer, 127, stdin);
    sscanf(buffer, "%d", &num_nodes);
    nodes = (struct node *) malloc(num_nodes * sizeof(struct node));
    
    /*Initialize the vertices*/
    for(i=0; i<num_nodes; ++i)
    {
        nodes[i].id = i+1;
        printf("Enter name of node %d: ", i+1);
        fgets(buffer, 127, stdin);
        sscanf(buffer, "%[^\n]s", name);
        nodes[i].name = (char *) (malloc((strlen(name)+1) * sizeof(char)));
        strcpy(nodes[i].name, name);
        nodes[i].d = LONG_MAX;
        nodes[i].c = 'w';
        nodes[i].p = NULL;
    }
    
    adj = (struct item **)malloc(num_nodes * sizeof(struct item *));
    /*Initialize adjacency list to NULL*/
    for(i=0; i<num_nodes; ++i)
        adj[i] = NULL;
        
    /*Add all the edges to adjacency list. No mechanism implemented to prevent multi-edges or self-loop*/
    for(i=0; i<num_nodes; ++i)
    {
        printf("Enter all edges from %s: (-1 to end)\n", nodes[i].name);
        while(1)
        {
            fgets(buffer, 127, stdin);
            sscanf(buffer, "%s", z);
            if(strcmp(z, "exit") == 0)
                break;
            edge = find_vertex(nodes, num_nodes, z);
            if(edge == -1)
            {
                printf("Vertex %s does not exist\n", z);
                break;
            }
            add_edge(&adj[i], edge);
        }
    }
    
    #ifdef DEBUG
    /*Display all the edges*/
    for(i=0; i<num_nodes; ++i)
        display_edges(adj[i], nodes, i);
    #endif
    
    /*Choose a source vertex*/
    printf("Enter the source vertex: ");
    fgets(buffer, 127, stdin);
    sscanf(buffer, "%s", z);
    source = find_vertex(nodes, num_nodes, z);
    if(source == -1)
    {
        printf("Invalid vertex\n");
        exit(-1);
    }
    #ifdef DEBUG
    printf("***DEBUG MODE ON***\n");
    #endif
    /*Perform a BFS*/
    nodes[source-1].d = 0;
    nodes[source-1].p = NULL;
    nodes[source-1].c = 'g';
    push(&queue, &nodes[source-1]);
    #ifdef DEBUG
    printf("Pushed %s\n", nodes[source-1].name);
    display_queue(queue);
    #endif
    while(!empty(queue))
    {
        u = pop(&queue);
        #ifdef DEBUG
        printf("Popped %s\n", u->name);
        display_queue(queue);
        #endif
        i = u->id;
        ptr = adj[i-1];
        while(ptr != NULL)
        {
            if(nodes[ptr->vertex-1].c == 'w')
            {
                nodes[ptr->vertex-1].c = 'g';
                nodes[ptr->vertex-1].d = u->d + 1;
                nodes[ptr->vertex-1].p = u;
                push(&queue, &nodes[ptr->vertex-1]);
                #ifdef DEBUG
                printf("Pushed %s\n", nodes[ptr->vertex-1].name);
                display_queue(queue);
                #endif
            }
            ptr = ptr->next;
        }
        u->c = 'b';
    }
    
    #ifdef DEBUG
    printf("***Printing paths***\n");
    #endif
    for(i=0; i<num_nodes; ++i)
    {
        if(i != source-1)
        {
            print_path(&nodes[source-1], &nodes[i]);
            printf("\n");
        }
    }
    
    return 1;
}

int find_vertex(struct node *nodes, int num_nodes, char *vertex)
{
    int i;
    for(i=0; i<num_nodes; ++i)
    {
        if(strcmp(vertex, nodes[i].name) == 0)
            return i+1;
    }
    return -1;
}

void print_path(struct node *source, struct node *dest)
{
    if(dest == source)
        printf("%s", source->name);
    else if(dest->p == NULL)
        printf("No path from %s to %s exists", source->name, dest->name);
    else
    {
        print_path(source, dest->p);
        printf(" --> %s", dest->name);
    }
}

void push(struct entry **queue, struct node *v)
{
    struct entry *temp;
    temp = (struct entry *) malloc(sizeof(struct entry));
    temp->v = v;
    if(*queue == NULL)
    {
        #ifdef DEBUG
        printf("Queue is empty\n");
        #endif
        temp->next = NULL;
        *queue = temp;
    }
    else
    {
        #ifdef DEBUG
        printf("Queue is NOT empty\n");
        #endif
        temp->next = *queue;
        *queue = temp;
    }
}

struct node *pop(struct entry **queue)
{
    struct entry *t = *queue, *p;
    struct node *v;
    if(*queue == NULL)
        return NULL;
    else if((*queue)->next == NULL)
    {
        v = (*queue)->v;
        *queue = NULL;
        return v;
    }
    else
    {
        p = *queue;
        t = (*queue)->next;
        while(t->next != NULL)
        {
            p = t;
            t = t->next;
        }
        p->next = NULL;
        return t->v;
    }
}

int empty(struct entry *queue)
{
    if(queue == NULL)
        return 1;
    else
        return 0;
}

void display_queue(struct entry *queue)
{
    printf("***QUEUE START***\n");
    while(queue != NULL)
    {
        printf("%s\t", queue->v->name);
        queue = queue->next;
    }
    printf("\n***QUEUE END***\n");
}

void add_edge(struct item **n, int vertex)
{
    struct item *temp = (struct item *) malloc(sizeof(struct item));
    temp->vertex = vertex;
    
    if(*n == NULL)
    {
        temp->next = NULL;
        *n = temp;
    }
    else
    {
        temp->next = *n;
        *n = temp;
    }
}

void display_edges(struct item *vertex, struct node *nodes, int n)
{
    char temp[128];
    strcpy(temp, nodes[n].name);
    strcat(temp, ":");
    printf("%-20s", temp);
    while(vertex != NULL)
    {
        printf("%20s\t", nodes[(*vertex).vertex-1].name);
        vertex = vertex->next;
    }
    printf("\n");
}