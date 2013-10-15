#include <stdio.h>
#include <limits.h>

int CUT_ROD(int prices[], int length);
int max(int a, int b);

int main()
{
	int prices[10] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	int length, res;
	char buffer[32];
		
	printf("Enter the length of the rod: ");
	fgets(buffer, 32, stdin);
	sscanf(buffer, "%d", &length);
	
	res = CUT_ROD(prices, length);
	
	printf("Maximum price to cut a rod of length %d is %d\n", length, res);
	
	return 1;
}

int CUT_ROD(int prices[], int length)
{
	int q, i;
	
	if(length == 0)
		return 0;
	
	q = INT_MIN;
	for(i=1; i<=length; i++)
		q = max(q, prices[i-1] + CUT_ROD(prices, length-i));
	return q;
}

int max(int a, int b)
{
	if(a > b)
		return a;
	else
		return b;
}

