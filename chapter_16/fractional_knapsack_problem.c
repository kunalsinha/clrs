#include <stdio.h>
#include <stdlib.h>

void relative_insertion_sort(double *p, double *v, double *w, int n);
void swap(double *x, int index1, int index2);

int main()
{
    //const double capacity = 180;
    //double v[] = {20, 120, 60, 45, 120, 120};
    //double w[] = {20, 80, 20, 60, 30, 100};
    const double capacity = 15;
    double v[] = {4, 2, 2, 1, 10};
    double w[] = {12, 1, 2, 1, 4};
    int n = sizeof(v)/sizeof(double);
    double *p;
    double weight, value;
    int i;
    
    p = (double *) malloc(sizeof(double) * n);
    for(i=0; i<n; i++)
        p[i] = v[i]/w[i];
        
    relative_insertion_sort(p, v, w, n);
    
    weight = value = 0;
    i = 0;
    while(weight < capacity && i<n)
    {
        if(w[i] <=  capacity-weight)
        {
            weight += w[i];
            value += v[i];
            printf("%7.2f unit weights of stuff with value: %2.2f and weight: %2.2f\n\n", w[i], v[i], w[i]);
        }
        else
        {
            value += p[i] * (capacity-weight);
            printf("%7.2f unit weights of stuff with value: %2.2f and weight: %2.2f\n\n", capacity-weight, v[i], w[i]);
            weight = capacity;
        }
        i++;
    }
    
    printf("***Maximum value of stuff that can be carried = %3.2f unit value***\n\n", value);
    return 1;
}

void relative_insertion_sort(double *p, double *v, double *w, int n)
{
    int i, j, key_index;
    double key;
    for(i=0; i<n-1; i++)
    {
        key = *(p+i);
        key_index = i;
        for(j=i+1; j<n; j++)
        {
            if(*(p+j) > key)
            {
                key = *(p+j);
                key_index = j;
            }
        }
        if(key_index != i)
        {
            swap(p, i, key_index);
            swap(v, i, key_index);
            swap(w, i, key_index);
        }
    }
}

void swap(double *x, int index1, int index2)
{
    double temp;
    temp = *(x+index1);
    *(x+index1) = *(x+index2);
    *(x+index2) = temp;
}
