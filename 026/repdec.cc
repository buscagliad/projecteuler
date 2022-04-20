#include <stdio.h>
#include "factor.h"
#include "prime.h"
#include <iostream>
#include "bigint.h"
using namespace std;

void	bigfact(long p)
{
	BigInt k(9);
	long n = 20;
	for (; n > 0; k = k*10 + 9)
	{
		if (k + p == (long) 0)
		{
		    printf("p = %ld   ", p);
		    cout << k;
		    printf("\n");
		    return;
		}
		n--;
	}
}

void test(long la, long lb)
{

	long lc = (la + lb)/2;
	BigInt a(la);
	BigInt b(lb);
	BigInt Q, R;
	BigInt c = avg(a, b);
	cout << a << " and " << b << "  avg -> " << c;
	printf("\n %ld  and  %ld  =  %ld\n", la, lb, lc);
	divide(a, b, Q, R);
	
	R = a % b;
	Q = a / b;
	cout << a << " mod " << b << "  Q = " << Q << "  R = " << R << endl;
}

int main()
{
	BigInt q(590);
	BigInt n(632);
	BigInt mq = -q;
	BigInt mn = n + mq;
	BigInt aab = mq + n;
	BigInt aa = absDiff(mq, n);
	BigInt bb = absDiff(n, mq);
		cout << "         mq = " << mq << endl;
		cout << "     n      = " << n << endl;
		cout << "     n + mq = " << mn << endl;
		cout << "     mq + n = " << aab << endl;
		cout << " absdiff(mq, n) = " << aa << endl;
		cout << " absdiff(n, mq) = " << bb << endl;
	test(632, 10);
	//test(123456789, 100);
	return 1;
	for (int i = 0; i < plist_size; i++)
	    bigfact(prime_list[i]);
}
