
#ifdef PROBLEM_DESCRIPTION

https://en.wikipedia.org/wiki/Continued_fraction

#endif

#include <cstdio>
#include <cstring>


#include "bigint.h"


typedef BigInt INT;

//#define SQUARE_ROOT_2

INT an(int n)
{
	#ifdef SQUARE_ROOT_2
	if (n == 0) return 1;
	return 2;
	#else
	if (n == 0l) return INT(2);
	// 1, 2, 3 --> 1, 2, 1
	// 4, 5, 6 --> 1, 4, 1
	// 3k - 2, 3K - 2, 3k --> 1, 2k, 1
	if (n % 3 == 1) return INT(1);
	if (n % 3 == 0) return INT(1);
	return INT(2 * (n+1)/3);
	#endif
}

INT hNext()
{
	static INT hnm2(0l);
	static INT hnm1(1l);
	static int n(-1);
	n++;
	INT hn = an(n) * hnm1 + hnm2;
	hnm2 = hnm1;
	hnm1 = hn;
	return hn;
}

INT kNext()
{
	static INT knm2(1l);
	static INT knm1(0l);
	static int k(-1);
	k++;
	INT kn = an(k) * knm1 + knm2;
	knm2 = knm1;
	knm1 = kn;
	return kn;
}

int main()
{
	BigInt k;
	BigInt h;
	for (int i = 0; i < 100; i++)
	{
		h = hNext();
		k = kNext();
	}
	printf("%s\n%s\n", h.c_str(), k.c_str());
	char digs[h.num_digits()+2];
	strcpy(digs, h.c_str());
	int  sum = 0;
	for (size_t i = 0; i < strlen(digs); i++)
	    if (isdigit(digs[i])) sum += digs[i] - '0';
	printf("Sum of the numeration digits is %d\n", sum);
}
