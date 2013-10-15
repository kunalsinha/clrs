#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

enum operation
{
    copy,
    replace,
    del,
    insert,
    twiddle,
    kill
};

void find_minimum_edit_distance(char *x, char *y);
void print_optimal_operation_sequence(char *x, char *y, int **tracker, int i, int j);
void print_array(int **et, int i, int j);
int get_minimum(int x[], int size);

int main()
{
    char x[1024], y[1024];
    
    printf("Enter source string: ");
    fgets(x, 1023, stdin);
    printf("Enter target string: ");
    fgets(y, 1023, stdin);
    
    find_minimum_edit_distance(x, y);
    
    return 1;
}

void find_minimum_edit_distance(char *x, char *y)
{
    int m, n, i, j, k;
    int cost[] = {2, 2, 2, 2, 5, 10};
    int t_cost[5];
    int **et, **tracker;
    int kill_cost, index;
    
    m = strlen(x) - 1;
    *(x+m) = '\0';
    n = strlen(y) - 1;
    *(y+n) = '\0';
    
    et = (int **) malloc(sizeof(int *) * (m+1));
    for(i=0; i<=m; i++)
        et[i] = (int *) malloc(sizeof(int) * (n+1));
    
    tracker = (int **) malloc(sizeof(int *) * (m+1));
    for(i=0; i<=m; i++)
        tracker[i] = (int *) malloc(sizeof(int) * (n+1));
        
    for(i=0; i<=m; i++)
    {
        for(j=0; j<=n; j++)
        {
            et[i][j] = 0;
            tracker[i][j] = -1;
        }
    }
    for(i=1; i<=m; i++)
        et[i][0] = cost[del] * i;
    for(j=1; j<=n; j++)
        et[0][j] = cost[insert] * j;
    
    for(i=1; i<=m; i++)
    {
        for(j=1; j<=n; j++)
        {
            printf("i=%d j=%d\n", i, j);
            for(k=0; k<5; k++)
                t_cost[k] = INT_MAX;
                
            if(x[i-1] == y[j-1])
                t_cost[copy] = et[i-1][j-1] + cost[copy];
                
            if(x[i-1] != y[j-1]) //add condition that z is not equal to y
                t_cost[replace] = et[i-1][j-1] + cost[replace];
                
            t_cost[del] = et[i-1][j] + cost[del];
            
            t_cost[insert] = et[i][j-1] + cost[insert];
            
            if((i>=2 && j>=2) && (y[j-1] == x[i-2] && y[j-2] == x[i-1]))
                t_cost[twiddle] = et[i-2][j-2] + cost[twiddle];
                
            printf("copy cost = %d\n", t_cost[0]);
            printf("replace cost = %d\n", t_cost[1]);
            printf("delete cost = %d\n", t_cost[2]);
            printf("insert cost = %d\n", t_cost[3]);
            printf("twiddle cost = %d\n", t_cost[4]);
            
            index = get_minimum(t_cost, 5);
            printf("Index = %d\n", index);
            switch(index)
            {
                case 0:
                    et[i][j] = t_cost[0];
                    tracker[i][j] = 0;
                    break;
                case 1:
                    et[i][j] = t_cost[1];
                    tracker[i][j] = 1;
                    break;
                case 2:
                    et[i][j] = t_cost[2];
                    tracker[i][j] = 2;
                    break;
                case 3:
                    et[i][j] = t_cost[3];
                    tracker[i][j] = 3;
                    break;
                case 4:
                    et[i][j] = t_cost[4];
                    tracker[i][j] = 4;
                    break;
                default:
                    break;
            }
            print_array(et, m, n);
            getchar();
        }
    }
    //for(i=0; i<m; i++)
    //{
    //    kill_cost = et[i][n] + cost[kill];
    //    if(kill_cost < et[m][n])
    //        et[m][n] = kill_cost;
    //}
    printf("Edit distance minimum cost = %d\n", et[m][n]);
    //print_array(tracker, m, n);
    //print_optimal_operation_sequence(x, y, tracker, m, n);
    
}

void print_optimal_operation_sequence(char *x, char *y, int **tracker, int i, int j)
{
    printf("i=%d j=%d\n", i, j);
    if(i >= 1 && j >= 1)
    {
        printf("tracker[i][j] = %d\n", tracker[i][j]);
        switch(tracker[i][j])
        {
            case 0:
                print_optimal_operation_sequence(x, y, tracker, i-1, j-1);
                printf("Copy\n");
                break;
            case 1:
                print_optimal_operation_sequence(x, y, tracker, i-1, j-1);
                printf("Replace\n");
                break;
            case 2:
                print_optimal_operation_sequence(x, y, tracker, i-1, j);
                printf("Delete\n");
                break;
            case 3:
                print_optimal_operation_sequence(x, y, tracker, i, j-1);
                printf("Insert\n");
                break;
            case 4:
                print_optimal_operation_sequence(x, y, tracker, i-2, j-2);
                printf("Twiddle\n");
                break;
            default:
                printf("Invalid data\n");
                break;
        }
    }
}

int get_minimum(int x[], int size)
{
    int min = INT_MAX;
    int i, min_index;
    
    for(i=0; i<size; i++)
    {
        if(x[i] < min)
        {
            min = x[i];
            min_index = i;
        }
    }
    return min_index;
}

void print_array(int **x, int i, int j)
{
    int a, b;
    for(a=0; a<=i; a++)
    {
        for(b=0; b<=j; b++)
            printf("%3d ", x[a][b]);
        printf("\n");
    }
    printf("\n");
}
