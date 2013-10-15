#include <iostream>
#include <cmath>
#include <new>
#include <cfloat>
#include <iomanip>

using namespace std;

class Point
{
    public:
        int x, y;
        
        Point(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
};

double get_distance(Point p1, Point p2)
{
    double a, b;
    a = p2.y - p1.y;
    b = p2.x - p1.x;
    return sqrt(pow(a, 2.0) + pow(b, 2.0));
}

int main()
{
    Point points[] = {Point(2,7), Point(3,3), Point(4,4), Point(5,5), Point(6,1), Point(7,6), Point(8,2)};
    int size, i, j, k;
    double **bitonic_dist;
    double dist;
    int **tracker;
    
    size = sizeof(points)/sizeof(Point);
    bitonic_dist = new double *[size];
    for(i=0; i<size; i++)
        bitonic_dist[i] = new double[size];
    tracker = new int *[size];
    for(i=0; i<size; i++)
        tracker[i] = new int[size];
    for(i=0; i<size; i++)
        for(j=0; j<size; j++)
            tracker[i][j] = -1;
    
    for(i=0; i<size-1; i++)
    {
        for(j=i+1; j<size; j++)
        {
            if(i == 0 && j == 1)
            {
                bitonic_dist[i][j] = get_distance(points[0], points[1]);
                tracker[i][j] = i;
            }
            else if(i < j-1)
            {
                bitonic_dist[i][j] = bitonic_dist[i][j-1] + get_distance(points[j-1], points[j]);
                tracker[i][j] = j-1;
            }
            else
            {
                bitonic_dist[i][j] = DBL_MAX;
                for(k=0; k<i; k++)
                {
                    dist = bitonic_dist[k][i] + get_distance(points[k], points[i]);
                    if(dist < bitonic_dist[i][j])
                    {
                        bitonic_dist[i][j] = dist;
                        tracker[i][j] = k;
                    }
                }
            }
        }
    }

    //printf("Bitonic distance is %f\n", bitonic_dist[size-2][size-1] + get_distance(points[size-2], points[size-1]));
    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
            cout << setw(3) << tracker[i][j] << " ";
        cout << endl;
    }
}