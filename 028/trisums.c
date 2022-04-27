
#include <stdio.h>

int	triangle(int n)
{
	if (n == 1) return 1;
	int delta = 2 * (n - 1);
	int corner = (2 * n - 1) * (2 * n - 1);
	return 4 * corner - 6 * delta;
}

#define TRI_SUM 501
int main()
{
	long k = 1;
	for (long n = 2; n <= TRI_SUM; n++)
	    k += triangle(n);
	    
	printf("Triangle sum at %d is %ld\n", TRI_SUM, k);
	return 1;
}
