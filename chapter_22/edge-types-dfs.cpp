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
    int d, f;
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
                va[i].d = va[i].f = 0;
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
        
        void dfs()
        {
            int time = 0;
            for(int i=0; i<num_vertices; ++i)
                if(va[i].color == 'w')
                    dfs_visit(&va[i], time);
        }
        
        void dfs_visit(vertex *u, int &time)
        {
            u->color = 'g';
            u->d = ++time;
            edge *e = u->e;
            while(e != NULL)
            {
                if(e->v->color == 'w')
                {
                    cout << "Tree Edge: " << u->name << " --> " << e->v->name << endl;
                    e->v->p = u;
                    dfs_visit(e->v, time);
                }
                else if(e->v->color == 'g')
                    cout << "Back Edge: " << u->name << " --> " << e->v->name << endl;
                else
                {
                    if(u->d < e->v->f)
                        cout << "Forward Edge: " << u->name << " --> " << e->v->name << endl;
                    else
                        cout << "Cross Edge: " << u->name << " --> " << e->v->name << endl;
                }
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
    vertices.dfs();
    
    
    
    return 1;
}
