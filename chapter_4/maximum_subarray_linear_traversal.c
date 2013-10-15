#include <stdio.h>
#include <string.h>
#include <limits.h>

struct subarray
{
	int sum;
	int left;
	int right;
};

struct subarray find_maximum_subarray(int a[], int size);

int main()
{
	char buffer[128];
	char response;
	int size;
	struct subarray sa;
	int a[] = {2, -12, -6, 3, 10, 8, -2, 14, -26, -3, 5, 7, -23, 12, -8, 17, 2, -3, -1, 0, 19, -11, 2, 4};
	size = sizeof(a)/sizeof(int);
	do
	{
		printf("Enter a to find the maximum subarray and e to exit\n");
		fgets(buffer, 128, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				sa = find_maximum_subarray(a, size);
				printf("Sum of maximum subarray from index %d to %d = %d\n", sa.left, sa.right, sa.sum);
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

struct subarray find_maximum_subarray(int a[], int size)
{
	int i, sum, left;
	struct subarray sa;
	sum = left = 0;
	sa.sum = INT_MIN;
	
	for(i=0; i<size; i++)
	{
		sum += a[i];
		if(sum > sa.sum)
		{
			sa.sum = sum;
			sa.left = left;
			sa.right = i;
		}
		if(sum < 0)
		{
			sum = 0;
			left = i+1;
		}
	}
	return sa;	
}

