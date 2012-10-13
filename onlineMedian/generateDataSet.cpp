#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#define MAX_INPUT 1000000
#define MAX_NUM 10000
#define PROB 60

using namespace std;

int main()
{
	srand( time(NULL) );
	int t = rand() % MAX_INPUT + 2000;
	ofstream fp;
	fp.open("dataSet.txt");
	int countNumMedian = 0;

	fp<<(rand() % MAX_NUM + 1)<<"\n";
	bool turn = 0;
	for (int i=0; i<t; i++)
	{
		int prob = rand() % 100;
		if (prob < PROB)
		{
			fp<<(rand() % MAX_NUM + 1)<<"\n"<<(rand() % MAX_NUM + 1)<<"\n";
			turn = 1;
		}
		else
			if ( turn )
			{
				fp<<"m\n";
				turn = 0;
				countNumMedian++;
			}
	}
	fp<<"e";
	fp.close();
	cout<<countNumMedian<<"\n";
	return EXIT_SUCCESS;
}
