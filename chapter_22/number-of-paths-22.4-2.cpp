#include <iostream>
#include <list>
#include <string>
#include <new>
#include <cstdlib>
#include <cstring>

using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::string;

struct edge;

struct vertex
{
    string name;
    char color;
    struct vertex *p;
    int d, f, num_paths;
    struct edge *e;
};

struct edge
{
    struct vertex *v;
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
                va[i].d = va[i].f = va[i].num_paths = 0;
                va[i].p = NULL;
                va[i].e = NULL;
            }
        }
        
        void resetVertices()
        {
            for(int i=0; i<num_vertices; ++i)
            {
                va[i].color = 'w';
                va[i].d = va[i].f = va[i].num_paths = 0;
                va[i].p = NULL;
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
            int index;
            for(int i=0; i<num_vertices; ++i)
            {
                cout << "Enter all edges from " << va[i].name << " (-1 to stop)" << endl;
                while(1)
                {
                    getline(cin, n);
                    if(!n.compare("-1"))
                        break;
                    index = findVertex(n);
                    if(index == -1)
                    {
                        cout << "Vertex " << n << " does not exist. Try again." << endl;
                        continue;
                    }
                    addEdge(i, index);
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
        
        void addEdge(int origin, int dest)
        {
            edge *e = new edge;
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
        
        void numberOfPaths(string source, string destination)
        {
            resetVertices();
            int sourceIndex = findVertex(source);
            int destinationIndex = findVertex(destination);
            if(sourceIndex == -1 || destinationIndex == -1)
                cout << "Invalid source or destination vertex" << endl;
            else
            {
                int time = 0;
                dfs(&va[sourceIndex], &va[destinationIndex], time);
                cout << "Number of paths: " << va[sourceIndex].num_paths << endl;
            }
        }
        
        void dfs(vertex *u, vertex *d, int &time)
        {
            u->color = 'g';
            u->d = ++time;
            edge *e = u->e;
            while(e != NULL)
            {
                /* Since the graph is a DAG, we will never encounter a grey vertex */
                /*if(e->v->color == 'w')
                {
                    e->v->p = u;
                    dfs(e->v, d, time);
                    if(e->v == d)
                        ++(u->num_paths);
                    else
                        u->num_paths += e->v->num_paths;
                }
                else if(e->v->color == 'b')
                {
                    if(e->v == d)
                        ++(u->num_paths);
                    else
                        u->num_paths += e->v->num_paths;
                }*/
                if(e->v->color == 'w')
                {
                    e->v->p = u;
                    dfs(e->v, d, time);
                }
                if(e->v == d)
                    ++(u->num_paths);
                else
                    u->num_paths += e->v->num_paths;
                    
                    
                e = e->next;
            }
            u->f = ++time;
            u->color = 'b';
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
    
    string a, b;
    while(1)
    {
        cout << "Enter source: ";
        cin >> a;
        cout << "Enter destination: ";
        cin >> b;
        vertices.numberOfPaths(a, b);
    }
    
    return 1;
}
