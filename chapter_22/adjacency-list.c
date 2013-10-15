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

void add_edge(struct item **node, int vertex);
void display_edges(struct item *vertex, struct node *nodes, int num_nodes);

int main()
{
    char buffer[128];
    int num_nodes;
    struct node *nodes;
    int i, edge;
    char name[128];
    struct item **adj;
    
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
    for(i=0; i<num_nodes; i++)
        adj[i] = NULL;
        
    /*Add all the edges to adjacency list. No mechanism implemented to prevent multi-edges or self-loop*/
    for(i=0;i <num_nodes; i++)
    {
        printf("Enter all edges from %s: (-1 to end)\n", nodes[i].name);
        while(1)
        {
            fgets(buffer, 127, stdin);
            sscanf(buffer, "%d", &edge);
            if(edge == -1)
                break;
            add_edge(&adj[i], edge);
        }
    }
    
    /*Display all the edges*/
    for(i=0; i<num_nodes; i++)
        display_edges(adj[i], nodes, i);
        
    return 1;
}

void add_edge(struct item **node, int vertex)
{
    struct item *temp = (struct item *) malloc(sizeof(struct item));
    temp->vertex = vertex;
    
    if(*node == NULL)
    {
        temp->next = NULL;
        *node = temp;
    }
    else
    {
        temp->next = *node;
        *node = temp;
    }
}

void display_edges(struct item *vertex, struct node *nodes, int node)
{
    char temp[128];
    strcpy(temp, nodes[node].name);
    strcat(temp, ":");
    printf("%-20s", temp);
    while(vertex != NULL)
    {
        printf("%20s\t", nodes[(*vertex).vertex-1].name);
        vertex = vertex->next;
    }
    printf("\n");
}