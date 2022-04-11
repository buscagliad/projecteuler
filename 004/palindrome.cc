
#include <string.h>
#include <stdio.h>

bool ispalindrome(long n)
{
	char	na[100];
	sprintf(na, "%ld", n);
	int	ln = strlen(na);
	for (int i = 0; i < ln/2; i++)
		if (na[i] != na[ln - i - 1]) return false;
	return true;
}


int main(int argc, char **argv)
{
	long a = 999; 
	long b = 999;
	long ma, mb, mp = 0;
	for (a = 100; a < 1000; a++)
		for (b = a; b < 1000; b++)
		{
			long p = a * b;
			if (ispalindrome(p))
			{
				if (p > mp)
				{
					mp = p; ma = a; mb = b;
				}
				printf("N: %ld  is palindrome: %ld * %ld\n",
					p, a, b);
			}
		}
	printf("Max Palidrome: %ld   a = %ld   b = %ld\n", mp, ma, mb);
	return 0;
}
