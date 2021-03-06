#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct edge;

struct vertex
{
    char *name;
    char color;
    struct vertex *p;
    int d, f;
    struct edge *e;
};

struct edge
{
    struct vertex *vptr;
    struct edge *next;
};

void dfs(struct vertex *vptr, int *time);
void add_edge(struct vertex *vptr, struct vertex *v);
int find_vertex(const char *name, struct vertex *adj_list, const int num_vertices);
void display_adj_list(struct vertex *adj_list, const int num_vertices);

int main()
{
    char buffer[128], name[128];
    struct vertex *adj_list = NULL;
    int i, num_vertices, index, time;
    
    printf("Enter the number of vertices: ");
    fgets(buffer, 127, stdin);
    sscanf(buffer, "%d", &num_vertices);
    adj_list = malloc(sizeof(struct vertex) * num_vertices);
    if(adj_list == NULL)
    {
        printf("Memory allocation failure...\n");
        exit(-1);
    }
    for(i=0; i<num_vertices; ++i)
    {
        printf("Enter the name of vertex: ");
        fgets(buffer, 127, stdin);
        sscanf(buffer, "%[^\n]s", name);
        adj_list[i].name = malloc(strlen(name)+1);
        strcpy(adj_list[i].name, name);
        adj_list[i].e = NULL;
        adj_list[i].p = NULL;
        adj_list[i].color = 'w';
        adj_list[i].d = adj_list[i].f = 0;
    }
    
    /*Add the edges to the vertices*/
    for(i=0; i<num_vertices; ++i)
    {
        printf("Enter all edges for %s (-1 to stop)\n", adj_list[i].name);
        while(1)
        {
            fgets(buffer, 127, stdin);
            sscanf(buffer, "%s", name);
            if(!strcmp(name, "-1"))
                break;
            index = find_vertex(name, adj_list, num_vertices);
            if(index == -1)
            {
                printf("Vertex with name %s does not exist. Try again.\n", name);
                continue;
            }
            add_edge(&adj_list[i], &adj_list[index]);
        }
    }
    
    /* Perform a depth-first-search on the graph */
    time = 0;
    for(i=0; i<num_vertices; ++i)
    {
        if(adj_list[i].color == 'w')
            dfs(&adj_list[i], &time);
    }
    
    /* Display the adjacency list */
    display_adj_list(adj_list, num_vertices);
    
    return 1;
}

void dfs(struct vertex *vptr, int *time)
{
    struct edge *e = vptr->e;
    vptr->color = 'g';
    vptr->d = ++*time;
    while(e != NULL)
    {
        if(e->vptr->color == 'w')
        {
            e->vptr->p = vptr;
            dfs(e->vptr, time);
        }
        e = e->next;
    }
    vptr->color = 'b';
    vptr->f = ++*time;
}

void add_edge(struct vertex *vptr, struct vertex *v)
{
    struct edge *ep = malloc(sizeof(struct edge));
    ep->vptr = v;
    if(vptr->e == NULL)
    {
        vptr->e = ep;
        ep->next = NULL;
    }
    else
    {
        ep->next = vptr->e;
        vptr->e = ep;
    }
}

int find_vertex(const char *name, struct vertex *adj_list, const int num_vertices)
{
    int i;
    for(i=0; i<num_vertices; ++i)
        if(!strcmp(adj_list[i].name, name))
            return i;
    return -1;
}

void display_adj_list(struct vertex *adj_list, const int num_vertices)
{
    int i;
    struct edge *e = NULL;
    for(i=0; i<num_vertices; ++i)
    {
        printf("%s d_time:%d f_time:%d -->", adj_list[i].name, adj_list[i].d, adj_list[i].f);
        e = adj_list[i].e;
        while(e != NULL)
        {
            printf("  %s  ", e->vptr->name);
            e = e->next;
        }
        printf("\n");
    }
}
