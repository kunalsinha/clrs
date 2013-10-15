#include <iostream>
#include <string>
#include <new>
#include <cstdlib>
#include <climits>
#include <queue>
#include <set>

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
    int d;
    struct edge *e;
};

struct edge
{
    struct vertex *v;
    int weight;
    struct edge *next;
};

class VertexComparator
{
    public:
        bool operator()(vertex *u, vertex *v)
        {
            if(u->d > v->d)
                return true;
            else
                return false;
        }
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
        
        void acceptVertices()
        {
            string temp;
            for(int i=0; i<num_vertices; ++i)
            {
                cout << "Enter name of vertex " << i+1 << ": ";
                getline(cin, temp);
                va[i].name.assign(temp);
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
                    cout << "  " << e->v->name << "-" << e->weight << "  ";
                    e = e->next;
                }
                cout << endl;
            }
        }
        
        void acceptEdges()
        {
            string n;
            int w;
            int index;
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
        
        /* Dijkstra's algorithm to find single source shortest path */
        void findShortestPaths(string source)
        {
            initialize(source);
            std::set<vertex *> determined;
            std::priority_queue<vertex *, std::vector<vertex *>, VertexComparator> undetermined;
            for(int i=0; i<num_vertices; ++i)
                undetermined.push(&va[i]);
            vertex *u;
            edge *e;
            while(!undetermined.empty())
            {
                u = undetermined.top();
                undetermined.pop();
                determined.insert(u);
                e = u->e;
                while(e != NULL)
                {
                    relax(findIndex(u), e);
                    e = e->next;
                }
            }
            printShortestPaths(source);
        }
        //*/
        
        int findIndex(vertex *u)
        {
            for(int i=0; i<num_vertices; ++i)
                if(u == &va[i])
                    return i;
            return -1;  
        }
        
        void relax(int s_index, edge *e)
        {
            if((va[s_index].d != INT_MAX) && (e->v->d > va[s_index].d + e->weight))
            {
                e->v->d = va[s_index].d + e->weight;
                e->v->p = &va[s_index];
            }
        }
        
        void initialize(string source)
        {
            int index = findVertex(source);
            if(index == -1)
                cout << "Vertex " << source << " does not exist" << endl;
            else
            {
                for(int i=0; i<num_vertices; ++i)
                {
                    va[i].d = INT_MAX;
                    va[i].p = NULL;
                }
                va[index].d = 0;
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
    vertices.findShortestPaths("a");
    return 1;
}
