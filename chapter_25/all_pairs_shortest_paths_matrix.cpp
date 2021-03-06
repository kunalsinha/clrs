#include <iostream>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include "all_pairs_shortest_paths_matrix.hpp"

void Graph::initializeGraph()
{
    // enter the names of all the vertices in the graph
    std::cout << "Enter the name of vertices ('done' to stop)" << std::endl;
    while(true)
    {
        std::getline(std::cin, vertex);
        if(vertex == "done")
            break;
        vertices.push_back(vertex);
    }
    
    //enter all the edges in the graph
    //extend the size of edge_weights as needed
    edge_weights.resize(boost::extents[vertices.size()][vertices.size()]);

    for(index i=0; i<vertices.size(); ++i)
        for(index j=0; j<vertices.size(); ++j)
            if(i == j)
                edge_weights[i][j] = 0;
            else
                edge_weights[i][j] = std::numeric_limits<int>::max();

    for(int i=0; i<vertices.size(); ++i)
    {
        std::cout << "Enter the names of vertices to which " << vertices[i] << " has outgoing edges ('done' to stop)" << std::endl;
        while(true)
        {
            std::getline(std::cin, vertex);
            if(vertex == "done")
                break;
            auto pos = vertices.begin();
            if((pos = std::find(vertices.begin(), vertices.end(), vertex)) == vertices.end())
            {
                std::cout << "No vertex " << vertex << " in the graph" << std::endl;
                continue;
            }
            std::cout << "Weight of edge " << vertices[i] << " -> " << vertex << ": ";
            int weight;
            std::cin >> weight;
            edge_weights[i][std::distance(vertices.begin(), pos)] = weight;
            std::cin.ignore();
        }
    } 
}
    
void Graph::printVertices()
{
    for(auto& v: vertices)
        std::cout << v << std::endl;
}

void Graph::printEdgeWeights()
{
    for(index i=0; i<vertices.size(); ++i)
    {
        for(index j=0; j<vertices.size(); ++j)
            std::cout << edge_weights[i][j] << " "; 
        std::cout << std::endl;
    }
}

void Graph::findAllPairsShortestPaths()
{
    fastFindAllPairsShortestPaths();
}

// Takes O(V^4) time and O(V^3) space. 
void Graph::slowFindAllPairsShortestPaths()
{
    std::vector<int_2d_array> shortest_path;
    shortest_path.push_back(edge_weights);
    for(int i=2; i<vertices.size(); ++i)
        shortest_path.push_back(extend_shortest_path(shortest_path.back(), edge_weights));

    shortest_paths.resize(boost::extents[vertices.size()][vertices.size()]);
    shortest_paths = shortest_path.back();
    printShortestPaths();
}

/* Takes O(V^3 lg V) time by using repeated squaring method to find matrix product
 * and O(V^2) space
 */
void Graph::fastFindAllPairsShortestPaths()
{
    shortest_paths.resize(boost::extents[vertices.size()][vertices.size()]);
    shortest_paths = edge_weights;
    int i=1;
    while(i < vertices.size())
    {
        shortest_paths = extend_shortest_path(shortest_paths, shortest_paths);
        i *= 2;
    }
    printShortestPaths();
}


int_2d_array Graph::extend_shortest_path(int_2d_array path, int_2d_array weights)
{
    int_2d_array new_path(boost::extents[vertices.size()][vertices.size()]);
    //std::generate(new_path.begin(), new_path.end(), std::numeric_limits<int>::max);
    for(index i=0; i<vertices.size(); ++i)
        for(index j=0; j<vertices.size(); ++j)
            new_path[i][j] = std::numeric_limits<int>::max();
    
    for(index i=0; i<vertices.size(); ++i)
        for(index j=0; j<vertices.size(); ++j)
            for(index k=0; k<vertices.size(); ++k)
                if(path[i][k] != std::numeric_limits<int>::max() && edge_weights[k][j] != std::numeric_limits<int>::max())
                    new_path[i][j] = std::min(new_path[i][j], path[i][k] + edge_weights[k][j]);
    
    return new_path;
}

/* Floyd-Warshall algorithm to find all pairs shortest paths in a graph
 * in O(V^3) time. Implementation takes O(V^2) space
 */
void Graph::floydWarshall()
{
    int size = vertices.size();
    int_2d_array kth_matrix(boost::extents[vertices.size()][vertices.size()]);
    kth_matrix = edge_weights;
    int_2d_array kand1th_matrix(boost::extents[vertices.size()][vertices.size()]);

    for(int k=0; k<size; ++k)
    {
        //reset kth_matrix
        resetMatrix(kand1th_matrix);
        for(int i=0; i<size; ++i)
        {
            for(int j=0; j<size; j++)
            {
                if(kth_matrix[i][k] == std::numeric_limits<int>::max() ||
                        kth_matrix[k][j] == std::numeric_limits<int>::max())
                {
                    int temp = std::numeric_limits<int>::max();
                    kand1th_matrix[i][j] = kth_matrix[i][j];
                }
                else
                    kand1th_matrix[i][j] = std::min(kth_matrix[i][j], kth_matrix[i][k] + kth_matrix[k][j]);
            }
        }
        kth_matrix = kand1th_matrix;
    }
    shortest_paths.resize(boost::extents[vertices.size()][vertices.size()]);
    shortest_paths = kth_matrix;
    printShortestPaths();
}

void Graph::resetMatrix(int_2d_array& matrix)
{
    for(int i=0; i<vertices.size(); ++i)
        for(int j=0; j<vertices.size(); ++j)
            matrix[i][j] = std::numeric_limits<int>::max();
}

void Graph::printShortestPaths()
{
    for(index i=0; i<vertices.size(); ++i)
    {
        
        std::cout << "Shortest path weights for " << vertices[i] << std::endl;
        for(index j=0; j<vertices.size(); ++j)
        {
            std::cout << vertices[j] << ": "; 
            if(shortest_paths[i][j] == std::numeric_limits<int>::max())
                std::cout << "No path";
            else
                std::cout << shortest_paths[i][j];
            std::cout << "\t";
        }
        std::cout << std::endl;
    }
}

