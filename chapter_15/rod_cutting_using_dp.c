#include <stdio.h>
#include <limits.h>

int CUT_ROD_BOTTOM_UP(int prices[], int length, int *s);

int main()
{
	int prices[10] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	int s[11];
	int length, result;
	char buffer[32];
	
	s[0] = 0;
	
	printf("Enter the length of the rod: ");
	fgets(buffer, 32, stdin);
	sscanf(buffer, "%d", &length);
	
	result = CUT_ROD_BOTTOM_UP(prices, length, s);
	
	printf("Optimal price = %d\n", result);
	printf("Pieces cut: ");
	while(length > 0)
	{
		printf("%d ", s[length]);
		length -= s[length];
	}
	printf("\n");
	return 1;
}

int CUT_ROD_BOTTOM_UP(int prices[], int length, int *s)
{
	int result[11];
	int q, i, j, rem;
	result[0] = 0;
	for(i=1; i<=10; i++)
		result[i] = INT_MIN;
	
	for(i=1; i<=length; i++)
	{
		q = INT_MIN;
		for(j=1; j<=i; j++)
		{
			rem = i-j;
			if(q < prices[j-1] + result[rem])
			{
				q = prices[j-1] + result[rem];
				*(s+i) = j;
			}
		}
		result[i] = q;
	}
	return result[length];
}

