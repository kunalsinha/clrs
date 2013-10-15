#include <stdio.h>
#include <string.h>

#define LIST_SIZE 5

int find_kth_minimum_order(int list[], int left, int right, int k);
int partition(int *list, int left, int right);

int main()
{
	int list[LIST_SIZE];
	char buffer[128];
	char response;
	int i, order, result;
	
	printf("Enter the list of %d numbers\n", LIST_SIZE);
	for(i=0; i<LIST_SIZE; i++)
	{
		fgets(buffer, 128, stdin);
		sscanf(buffer, "%d", &list[i]);
	}
	for(i=0; i<LIST_SIZE; i++)
		printf("%d\t", list[i]);
	printf("\n");
	
	do
	{
		printf("Enter a to find minimum order statistic and e to exit\n");
		fgets(buffer, 128, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				printf("Which order minimum in the list do you want: ");
				fgets(buffer, 128, stdin);
				sscanf(buffer, "%d", &order);
				result = find_kth_minimum_order(list, 0, LIST_SIZE, order);
				printf("Minimum number of order %d in list is %d\n",  order, result);
				break;
			case 'e':
				break;
			default:
				printf("Wrong option\n");
				break;
		}
	}
	while(response != 'e');
	return 1;
}

int find_kth_minimum_order(int list[], int left, int right, int k)
{
	int pivot_index, distance;
	
	pivot_index = partition(list, left, right);
	//getchar();
	distance = pivot_index - left + 1;
	//printf("Distance = %d\n", distance);
	
	if(k == distance)
		return list[pivot_index];
	else if(k < distance)
	{
		//printf("Looking in left array for a distance at %d\n", k);
		return find_kth_minimum_order(list, left, pivot_index, k);
	}
	else
	{
		//printf("Looking in right array for a distance at %d\n", k-pivot_index-1);
		return find_kth_minimum_order(list, pivot_index+1, right, k-pivot_index-1);
	}
}

//Choosing pivot indexing as the rightmost element in the list
int partition(int *list, int left, int right)
{
	int key, i, j, temp;
	//printf("Left=%d\tRight=%d\n", left, right);
	key = *(list+right-1);
	j = left;
	for(i=left; i<right-1; i++)
	{
		if(*(list+i) <= key)
		{
			temp = *(list+i);
			*(list+i) = *(list+j);
			*(list+j) = temp;
			j++;
		}
	}
	/*printf("*******Array just before final switch******\n");
	for(i=left; i<right; i++)
		printf("%d\t", *(list+i));
	printf("\n");*/
	temp = *(list+j);
	*(list+j) = *(list+right-1);
	*(list+right-1) = temp;
	/*printf("*******Array after partition******\n");
	for(i=left; i<right; i++)
		printf("%d\t", *(list+i));
	printf("\n");
	printf("Index for %d is %d\n", key, j);*/
	return j;
}

