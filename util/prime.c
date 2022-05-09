#include <stdio.h>

#include "prime.h"

int isp(long n)
{
	if (isPrime(n)) printf("%ld is prime.\n", n);
	else printf("%ld is NOT prime\n", n);
}

int	test()
{
	
	long inf24 = 433029629;
	long inf50 = 982450291;
	long lastp = 982451653;
	long oobp  = 982451707;
	long oobnp = 982451713;
	long inf01 = 1657;
	
	isp(inf24);
	isp(inf50);
	isp(lastp);
	isp(oobp);
	isp(oobnp);
	isp(inf01);
	return 1;
}
	

int main()
{
	test();
}
