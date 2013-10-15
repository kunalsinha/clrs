#include <stdio.h>
#include <limits.h>
#include <time.h>

int CUT_ROD(int prices[], int length);
int max(int a, int b);

int main()
{
	int prices[10] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	int res;
	time_t begin, end;
	
	time(&begin);
		
	res = CUT_ROD(prices, 10);
	
	printf("Maximum price to cut a rod of length 10 is %d\n", res);
	
	time(&end);
	printf("%f\n", difftime(end, begin)*1000);
	
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

