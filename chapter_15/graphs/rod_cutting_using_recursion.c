#include <stdio.h>
#include <limits.h>

int rod_cut(int prices[], int length);
int max(int a, int b);

int no_of_calls;

int main()
{
	int prices[10] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	int i;
	char buffer[32];
	
	FILE *gp = popen("gnuplot", "w");
	fprintf(gp, "set terminal png\n");
	fprintf(gp, "set title ''\n");
	fprintf(gp, "set xlabel 'Length of rod'\n");
	fprintf(gp, "set ylabel 'No. of calls to CUT_ROD'\n");
	fprintf(gp, "set xrange [0:11]\n");
	fprintf(gp, "set yrange [0:1100]\n");
	fprintf(gp, "p '-' u 1:2 w lines ti 'Recursive method'\n");
		
	
	for(i=1; i<=10; i++)
	{
		no_of_calls = 0;
		rod_cut(prices, i);
		//plot no_of_calls agains i
		fprintf(gp, "%d %d\n", i, no_of_calls);
	}
	
	pclose(gp);
	return 1;
}

int rod_cut(int prices[], int length)
{
	int q, i;
	
	no_of_calls++;
	if(length == 0)
		return 0;
	
	q = INT_MIN;
	for(i=1; i<=length; i++)
		q = max(q, prices[i-1] + rod_cut(prices, length-i));
	return q;
}

int max(int a, int b)
{
	if(a > b)
		return a;
	else
		return b;
}

