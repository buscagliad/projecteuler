#include "prime.h"

void verify(long p, int index)
{
	if (index > prime_list_size)
	{
	    printf("%d index exceeds current prime list size of %ld\n", 
			index, prime_list_size);
	    return;
	}
	if (p != prime_list[index-1])
		printf("%d prime is not %ld - it is %ld\n",
			index, p, prime_list[index-1]);
	else
		printf("%d prime is %ld\n",
			index, prime_list[index-1]);
}

int main()
{
	printf("Prime list has %ld members\n", prime_list_size);
	printf("Prime next after table: %ld\n", prime_list_next);
	// index is a 1-up counter, i.e. 2 is the 1st prime
	verify(541, 100);
	verify(2713, 396);
	verify(7793, 987);
	verify(71663, 7094);
	verify(99991, 9592);
	verify(11023, 116747);
}
