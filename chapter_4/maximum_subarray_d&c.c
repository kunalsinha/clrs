#include <stdio.h>
#include <string.h>
#include <limits.h>

struct subarray
{
	int sum;
	int left;
	int right;
};

struct subarray find_maximum_subarray(int a[], int left, int right);
struct subarray find_max_crossing_sum(int a[], int left, int mid, int right);

int li, ri;

int main()
{
	char buffer[128];
	char response;
	struct subarray sa;
	int a[] = {2, -12, -6, 3, 10, 8, -2, 14, -26, -3, 5, 7, -23, 12, -8, 17, 2, -3, -1, 0, 19, -11, 2, 4};
	int size = (sizeof(a)/sizeof(int)) - 1;
	do
	{
		printf("Enter a to find the maximum subarray and e to exit\n");
		fgets(buffer, 128, stdin);
		sscanf(buffer, "%c", &response);
		switch(response)
		{
			case 'a':
				sa = find_maximum_subarray(a, 0, size);
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

struct subarray find_maximum_subarray(int a[], int left, int right)
{
	int mid;
	struct subarray sa, left_sa, right_sa, cross_sa;
	
	if(left == right)
	{
		sa.sum = a[left];
		sa.left = sa.right = left;
		return sa;
	}
	else
		mid = (left+right)/2;
		
	left_sa = find_maximum_subarray(a, left, mid);
	right_sa = find_maximum_subarray(a, mid+1, right);
	cross_sa = find_max_crossing_sum(a, left, mid, right);
	
	if(left_sa.sum > right_sa.sum && left_sa.sum > cross_sa.sum)
		return left_sa;
	else if(right_sa.sum > left_sa.sum && right_sa.sum > cross_sa.sum)
		return right_sa;
	else
		return cross_sa;
}

struct subarray find_max_crossing_sum(int a[], int left, int mid, int right)
{
	int i;
	int l_sum, r_sum, sum;
	struct subarray sa;
	l_sum = r_sum = INT_MIN;
	sum = 0;
	
	for(i=mid; i>=left; i--)
	{
		sum += a[i];
		if(sum > l_sum)
		{
			l_sum = sum;
			sa.left = i;
		}
	}
	
	sum = 0;
	for(i=mid+1; i<=right; i++)
	{
		sum += a[i];
		if(sum > r_sum)
		{
			r_sum = sum;
			sa.right = i;
		}
	}
	sa.sum = l_sum + r_sum;
	return sa;
}

