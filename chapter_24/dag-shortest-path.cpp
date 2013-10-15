#include <iostream>
#include <list>
#include <string>
#include <new>
#include <cstdlib>
#include <cstring>
#include <climits>

using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::string;

struct edge;

struct vertex
{
    string name;
    struct vertex *p;
    char color;
    int d;
    struct edge *e;
};

struct edge
{
    struct vertex *v;
    int weight;
    struct edge *next;
};

class Vertices
{
    private:
        vertex *va;
        int num_vertices;
    
    public:
        Vertices(int num_vertices)
        {
            this->num_vertices = num_vertices;
            try
            {
                va = new vertex[num_vertices];
            }
            catch(std::bad_alloc xa)
            {
                cout << "Memory allocation failure" << endl;
                exit(EXIT_FAILURE);
            }
        }
        
        ~Vertices()
        {
            delete[] va;
        }
        
        void acceptVertices()
        {
            string temp;
            for(int i=0; i<num_vertices; ++i)
            {
                cout << "Enter name of vertex " << i+1 << ": ";
                getline(cin, temp);
                va[i].name.assign(temp);
                va[i].color = 'w';
                va[i].d = INT_MAX;
                va[i].p = NULL;
                va[i].e = NULL;
            }
        }
        
        void printVertices()
        {
            edge *e = NULL;
            for(int i=0; i<num_vertices; ++i)
            {
                cout << va[i].name << " --> ";
                e = va[i].e;
                while(e != NULL)
                {
                    cout << "  " << e->v->name << "  ";
                    e = e->next;
                }
                cout << endl;
            }
        }
        
        void acceptEdges()
        {
            string n;
            int index, w;
            for(int i=0; i<num_vertices; ++i)
            {
                cout << "Enter all edges from " << va[i].name << " (-1 to stop)" << endl;
                while(1)
                {
                    cout << "End point? ";
                    getline(cin, n);
                    if(!n.compare("-1"))
                        break;
                    index = findVertex(n);
                    if(index == -1)
                    {
                        cout << "Vertex " << n << " does not exist. Try again." << endl;
                        continue;
                    }
                    cout << "Edge weight? ";
                    cin >> w;
                    cin.ignore();
                    addEdge(i, index, w);
                }
            }
        }
        
        int findVertex(string n)
        {
            for(int i=0; i<num_vertices; ++i)
                if(!va[i].name.compare(n))
                    return i;
            return -1;
        }
        
        void addEdge(int origin, int dest, int weight)
        {
            edge *e = new edge;
            e->weight = weight;
            e->v = &va[dest];
            if(va[origin].e == NULL)
            {
                e->next = NULL;
                va[origin].e = e;
            }
            else
            {
                e->next = va[origin].e;
                va[origin].e = e;
            }
        }
        
        std::list<vertex *> topologicalSort()
        {
            std::list<vertex *> sortedOrder;
            for(int i=0; i<num_vertices; ++i)
            {
                if(va[i].color == 'w')
                    dfs(&va[i], sortedOrder);
            }
            return sortedOrder;
        }
        
        void dfs(vertex *u, std::list<vertex *> &sortedOrder)
        {
            u->color = 'g';
            edge *e = u->e;
            while(e != NULL)
            {
                if(e->v->color == 'w')
                {
                    e->v->p = u;
                    dfs(e->v, sortedOrder);
                }
                e = e->next;
            }
            u->color = 'b';
            sortedOrder.push_front(u);
        }
        
        /* Implement DAG-Shortest_Path algorithm to determine the single source shortest paths */
        void findShortestPaths(std::list<vertex *> vertices, string source)
        {
            vertex *v;
            edge *e;
            initialize(source);
            while(!vertices.empty())
            {
                v = vertices.front();
                vertices.pop_front();
                e = v->e;
                while(e != NULL)
                {
                    relax(v, e);
                    e = e->next;
                }
            }
        }
        
        void initialize(string source)
        {
            for(int i=0; i<num_vertices; ++i)
            {
                va[i].d = INT_MAX;
                va[i].p = NULL;
            }
            int index = findVertex(source);
            if(index != -1)
                va[index].d = 0;
            else
                cout << "Vertex " << source << " does not exist" << endl;
        }
        
        void relax(vertex *u, edge *e)
        {
            if(u->d != INT_MAX && (e->v->d > u->d + e->weight))
            {
                e->v->d = u->d + e->weight;
                e->v->p = u;
            }
        }
        
        void printShortestPaths(string source)
        {
            for(int i=0; i<num_vertices; ++i)
            {
                if(va[i].d == INT_MAX)
                    cout << "No path exists from " << source << " to " << va[i].name << endl;
                else
                {
                    cout << "Shortest path for " << va[i].name << " and path weight: " << va[i].d << endl;
                    printPath(&va[i]);
                    cout << endl;
                }
            }
        }
        
        void printPath(vertex *v)
        {
            if(v != NULL)
            {
                printPath(v->p);
                cout << v->name << " --> ";
            }
        }
};

int main()
{
    int num_v;
    cout << "Enter number of vertices: ";
    cin >> num_v;
    cin.ignore();
    Vertices vertices(num_v);
    vertices.acceptVertices();
    vertices.acceptEdges();
    //vertices.printVertices();
    
    std::list<vertex *> v = vertices.topologicalSort();
    std::list<vertex *>::iterator vp;
    for(vp=v.begin(); vp!=v.end(); ++vp)
        cout << (*vp)->name << " " ;
    cout << endl;
    
    string source;
    while(1)
    {
        cout << "Enter source vertex: ";
        getline(cin, source);
        vertices.findShortestPaths(v, source);
        vertices.printShortestPaths(source);
    }
    
    return 1;
}
