#include<iostream>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) 
{
	int T = 100;
	
	if (argc == 2)
	{
		T = atoi(argv[1]);
	}
	else
	{
		printf("Argument is TestCases (T)\n");
		exit(EXIT_FAILURE);
	}

	FILE *fp = fopen("input.txt", "w");
	fprintf(fp, "%d\n", T);
	
	
	for (int i = 0; i<T; i++)
	{
		int n,k;
		int kMax;
		n = rand() % 8 + 2;
		switch ( n )
		{
			case 2:	kMax = 9;
					break;
			case 3:	kMax = 90;
					break;
			case 4:	kMax = 90;
					break;
			case 5:	kMax = 900;
					break;
			case 6:	kMax = 900;
					break;
			case 7:	kMax = 9000;
					break;
			case 8:	kMax = 9000;
					break;
			case 9:	kMax = 90000;
					break;
			
			default:printf("n is %d: Error in n value \n", n);
					exit(EXIT_FAILURE);
					break;
		}
		
		k = rand() % kMax + 1;
		fprintf(fp, "%d %d\n", n, k);
		
	}
	fclose(fp);
	return EXIT_SUCCESS;
}
