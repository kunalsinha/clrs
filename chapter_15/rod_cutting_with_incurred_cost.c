#include <stdio.h>
#include <limits.h>

int main()
{
	int prices[10] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	int result[11];
	int s[10];
	int i, j, q, length, rem;
	char buffer[32];
	int no_of_cuts;
	int cuts[11];
	int cost = 2;
	
	result[0] = 0;
	for(i=1; i<=10; i++)
		result[i] = INT_MIN;
	
	for(i=0; i<11; i++)
		cuts[i] = 0;
	
	printf("Enter the length of the rod: ");
	fgets(buffer, 32, stdin);
	sscanf(buffer, "%d", &length);
	
	for(i=1; i<=length; i++)
	{
		q = INT_MIN;
		for(j=1; j<=i; j++)
		{
			rem = i-j;
			if(rem == 0)
				no_of_cuts = 0;
			else
				no_of_cuts = cuts[rem] + 1;
				
			if(q < prices[j-1] + result[rem] - cost * no_of_cuts)
			{
				q = prices[j-1] + result[rem] - cost * no_of_cuts;
				s[i] = j;
				cuts[i] = no_of_cuts;
			}
		}
		result[i] = q;
	}
	
	printf("Optimal price = %d\n", result[length]);
	printf("The length of pieces of rod to be cut: ");
	j = length;
	while(j>0)
	{
		printf("%d ", s[j]);
		j = j-s[j];
	}
	printf("\n");
	return 1;
}

