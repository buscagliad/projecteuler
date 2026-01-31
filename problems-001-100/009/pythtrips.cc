#include <stdio.h>

int main()
{
	for (long a = 1; a <= 1000; a++)
	{
		for (long b = a + 1; b <= 1000 - a; b++)
		{
			long c = 1000 - a - b;
			if (a * a + b * b == c * c)
			{
				printf("a = %ld   b = %ld  c = %ld\n", a, b, c);
				printf("  a^2: %ld  +  b^2: %ld = %ld  == c^2: %ld\n", a*a, b*b, a*a + b*b, c*c);
				printf("  a * b * c = %ld\n", a*b*c);
			}
		}
	}
}
