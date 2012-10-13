#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

struct _Questions
{
	int left;
	int right;
}*grid;

int main()
{
	int T = 0;
	scanf("%d\n", &T);
	
	for (int j=1; j<=T; j++)
	{
		int n=0;
		scanf("%d\n", &n);
		grid = (_Questions*) malloc(sizeof(_Questions) * n);
		int a, b;
		
		int i;
		for (i=0; i<n-1; i++)
		{
			scanf("%d %d\n", &a, &b);
			grid[i].left = a;
			grid[i].right = b;
		}
		scanf("%d %d", &a, &b);
		grid[i].left = a;
		grid[i].right = b;
		
		/*
		 * Grid has been created and parsed
		 * Now, just sort and find number of inversions for each
		 */
		 
		 int countInversions = 0;
		 
		 for (int i=0; i<n; i++)
			for(int j= 0; j<n; j++)
			{
				if((grid[i].left - grid[j].left) * (grid[i].right - grid[j].right) < 0)
					countInversions++;
			}
		
		countInversions = countInversions/2;		 
		 
		 /*
		  * Number of inversions found
		  */
		
		printf("%d\n",countInversions); 
	
	}
return EXIT_SUCCESS;
}
