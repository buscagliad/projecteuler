#include <algorithm>
#include <string>
#include <stdio.h>

 using namespace std;

void brute(string s, int nx)
{
	int n = nx;
	sort(s.begin(), s.end());	// ensure order
	while (n > 1)
	{
		next_permutation(s.begin(), s.end());
		n--;
	}
	printf("%d permuation is %s\n", nx, s.c_str());
}

int main()
{
	brute("0123456789", 0);
	brute("0123456789", 1);
	brute("0123456789", 2);
	brute("0123456789", 100000);
	brute("0123456789", 362880);
	brute("0123456789", 999999);
	brute("0123456789", 1000000);
}
