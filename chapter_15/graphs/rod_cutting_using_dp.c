#include <stdio.h>
#include <limits.h>
#include <time.h>

int CUT_ROD_BOTTOM_UP(int prices[], int length);

int main()
{
	int prices[10] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	int result, i;
	char buffer[32];
	time_t begin, end;
	
	/*FILE *gp = popen("gnuplot", "w");
	
	fprintf(gp, "set terminal png\n");
	fprintf(gp, "set title ''\n");
	fprintf(gp, "set xlabel 'Length of rod'\n");
	fprintf(gp, "set ylabel 'Running time of CUT_ROD_BOTTOM_UP (in ms)'\n");
	fprintf(gp, "set xrange [0:11]\n");
	fprintf(gp, "set yrange [0:1]\n");
	fprintf(gp, "p '-' u 1:2 w lines ti 'Dynamic programming'\n");*/
	
	for(i=1; i<=10;i++)
	{
		time(&begin);
		result = CUT_ROD_BOTTOM_UP(prices, i);
		time(&end);
		//fprintf(gp, "%d %f\n", i, difftime(end, begin)*1000000000);
		printf("%d %f\n", i, difftime(end, begin)*100000000000000000000000000000000000000000000000000000000000000000000.0);
	}
	
	printf("Optimal price = %d\n", result);
	//pclose(gp);
	return 1;
}

int CUT_ROD_BOTTOM_UP(int prices[], int length)
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
				q = prices[j-1] + result[rem];
		}
		result[i] = q;
	}
	return result[length];
}

