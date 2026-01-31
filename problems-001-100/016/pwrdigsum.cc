
#include "bigint.h"

int main()
{
	BigInt t = BigInt(2) ^ 1000;
	printf ("Number of digits is: %d\n", t.num_digits());
	long sum = 0;
	for (int i = 0; i < t.num_digits(); i++)
	    sum += t.get_digit(i);
	printf("Sum of digits is: %ld\n", sum);
}
