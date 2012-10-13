#include<iostream>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

// Constructs a palindrome from the half number. If oddlength is true,
// it uses last digit as common, otherwise repeats last digit.
// 3 digit n gives 6 digit palindrome if even length, 5 digit palindrome if odd length
int makePalindromeBase10(int n, bool isOddLength) {
	int result = n;
	if (isOddLength) {
		n = n / 10;
	}
	while (n > 0) {
		result = (result * 10) + (n % 10);
		n = n / 10;
	}
	return result;
}

int getPalindromeFast(int k, int numDigits) {
	int part = 1;
	int count = (numDigits % 2 == 0) ? numDigits/2 : numDigits/2 + 1;
	bool isOdd = !(numDigits % 2 == 0);
	for (int i = 1; i < count; i++) {
		part = part * 10;	//Basically doing the work of pow function, but avoiding it to increase compatibility
	}
	part = part + k - 1;
	return makePalindromeBase10(part, isOdd);
}


int main(int argc, char *argv[])
{
	int T = 0;
	cin>>T;
	for (int i=0; i<T; i++)
	{
		int n=0, k=0;
		cin>>n>>k;
		int answer = getPalindromeFast(k,n);
		cout<<answer<<"\n";
	}
	return EXIT_SUCCESS;
}
