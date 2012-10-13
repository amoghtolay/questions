#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#define NUM_CASES 1
#define MAX_CITIES 80
#define MAX_EDGES (MAX_CITIES*2)
#define NUM_QUES MAX_EDGES

using namespace std;

int main()
{
	ofstream fp;
	fp.open("dataSet.txt");
	if (!fp)
		exit(EXIT_FAILURE);
	fp<<NUM_CASES<<"\n";
			
	for (int k = 0; k < NUM_CASES; k++ )
	{
		
		srand( time(NULL) );
		int numCities = rand() % MAX_CITIES + 20;
		int numEdges = rand() % MAX_EDGES + 20;
		
		int vertex1[numEdges];
		int vertex2[numEdges];
		
		for (int i=0; i<numEdges; i++)
		{
			bool repeated = false;
			int tempVert1 = rand() % numCities;
			int tempVert2 = rand() % numCities;
			
			if (tempVert1 == tempVert2)
			{
				i--;
				continue;
			}
			
			for (int j=0; j<i; j++)
			{
				if ( (tempVert1 == vertex1[j] && tempVert2 == vertex2[j]) || (tempVert1 == vertex2[j] && tempVert2 == vertex1[j]) )
					repeated = true;
			}
			
			if (repeated)
			{
				i--;
				continue;
			}
			
			vertex1[i] = tempVert1;
			vertex2[i] = tempVert2;
		}
		/*
		 * Write the cities and edges to file
		 */
		fp<<numCities<<" "<<numEdges<<"\n";
		for (int i=0; i<numEdges-1; i++)
			fp<<(vertex1[i]+1)<<" "<<(vertex2[i]+1)<<"\n";
		fp<<vertex1[numEdges-1]+1<<" "<<vertex2[numEdges-1]+1<<"\n";
		/*
		 * Now write data of cities,to ask whether the two cities are connected
		 */
		fp<<NUM_QUES<<"\n";
		for (int j = 0; j<NUM_QUES; j++)
		{
			int quesVert1 = rand() % numCities;
			int quesVert2 = rand() % numCities;
			if (quesVert1 == quesVert2)
			{
				j--;
				continue;
			}
			fp<<quesVert1+1<<"?"<<quesVert2+1<<"\n";
		}
	}
	fp.close();
	return EXIT_SUCCESS;
}
