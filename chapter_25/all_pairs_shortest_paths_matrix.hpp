#include <boost/multi_array.hpp>
#include <string>

typedef boost::multi_array<int, 2> int_2d_array;
typedef int_2d_array::index index;

class Graph
{
    private:
        
        std::string vertex;
        std::vector<std::string> vertices;
        int_2d_array edge_weights;
        int_2d_array shortest_paths;

    public:
        Graph(): edge_weights(int_2d_array(boost::extents[0][0])), shortest_paths(int_2d_array(boost::extents[0][0]))
        {
            initializeGraph();
        }
        void initializeGraph();
        void printVertices();
        void printEdgeWeights();
        int_2d_array extend_shortest_path(int_2d_array path, int_2d_array weights);
        void findAllPairsShortestPaths();
        void slowFindAllPairsShortestPaths();
        void fastFindAllPairsShortestPaths();
        void printShortestPaths();
};
