#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	
	int t;
	cin>>t;
	for (int i=0; i<t; i++)
	{
		int n;
		cin>>n;
		bool* primes = new bool[n];
		primes[0] = false;
		primes[1] = false;
		bool toggle = true;
		
		long long ans = 0;
		for (int i = 2; i < n; i++)
			primes[i] = true;
		
		for (int i = 2; i < n; i++)
		{
			if (primes[i])
			{
				if (toggle)
				{
					ans = ans + i;
					toggle = false;
				}
				else toggle = true;
				
				for (int k = i + i; k < n; k += i)
					primes[k] = false;
			}
		}

		delete[] primes;
		cout << ans << "\n";
	}
	return EXIT_SUCCESS;
}
