#include <stdio.h>
#include <stdlib.h>

#define	FIB1 1
#define FIB2 2
#define NUM 4000000

long a = -1;
long b = -1;

long getfib()
{
	if (a == -1)
	{
		a = FIB1;
		return FIB1;
	}
	if (b == -1)
	{
		b = FIB2;
		return FIB2;
	}
	long f = a + b;
	a = b;
	b = f;
	return f;
}

int main(int argc, char **argv)
{
	long	sum = 0;
	long 	num = NUM;
	if (argc == 2) num = atol(argv[1]);
	long f = getfib();
	while  (f < num)
	{
		if (f % 2 == 0) sum += f;
		f = getfib();
	}
	printf("Sum of all even fibonacci numbers less than %ld  is %ld\n",
		num, sum);
	return 1;
}
