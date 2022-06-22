#ifdef PROBLEM_DESCRIPTION

Product-sum numbers


  [Show HTML problem content]  
Problem 88

A natural number, N, that can be written as the sum and product of a given set of at least two natural numbers, {a1, a2, ... , ak} is called a product-s


um number: N = a1 + a2 + ... + ak = a1 × a2 × ... × ak.

For example, 6 = 1 + 2 + 3 = 1 × 2 × 3.

For a given set of size, k, we shall call the smallest N with this property a minimal product-sum number. The minimal product-sum numbers for sets of size, k = 2, 3, 4, 5, and 6 are as follows.

k=2: 4 = 2 × 2 = 2 + 2
k=3: 6 = 1 × 2 × 3 = 1 + 2 + 3
k=4: 8 = 1 × 1 × 2 × 4 = 1 + 1 + 2 + 4
k=5: 8 = 1 × 1 × 2 × 2 × 2 = 1 + 1 + 2 + 2 + 2
k=6: 12 = 1 × 1 × 1 × 1 × 2 × 6 = 1 + 1 + 1 + 1 + 2 + 6

Hence for 2≤k≤6, the sum of all the minimal product-sum numbers is 4+6+8+12 = 30; note that 8 is only counted once in the sum.

In fact, as the complete set of minimal product-sum numbers for 2≤k≤12 is {4, 6, 8, 12, 15, 16}, the sum is 61.

What is the sum of all the minimal product-sum numbers for 2≤k≤12000?

#endif

#include <cstdio>
#include "vlong.h"
#include "factor.h"

#define DEBUG 0

int numones(vlong_t &c)
{
	int rv = 0;
	for (size_t i = 0; i < c.size(); i++) if (c[i] == 1) rv++;
	return rv;
}

void pout(const char *t, vlong_t &c)
{
	long s = sum(c);
	long p = product(c);
	int  no = numones(c);
	int  nn = c.size() - no;
	printf("k = %lu  %s  %ld = %ld", c.size(), t, s, c[0]);
	for (int i = 1; i < nn; i++)
	{
		printf(" + %ld", c[i]); 
	}
	if (no) printf(" + (%d) 1 ", no);
	
	if (s == p) printf(" = ");
	else printf(" || %ld = ", p);

	printf("%ld", c[0]);
	for (int i = 1; i < nn; i++)
	{
		printf(" * %ld", c[i]); 
	}
	if (no) printf(" * (%d) 1", no);
	printf("\n");
}


bool reset(vlong_t &v, bool shrink)
{
	//printf("RESET\n");
	if ( (v.size() - numones(v) == 2) || (v[0] == v[1]) ) shrink = false;
	v[0]++;
	v[1] = 2;
	for(size_t i = 2; i < v.size(); i++)
	{
		if ( (shrink) && ( i > 2 ) && ( (v[i] == 1) || (i + 1 == v.size()) ) )
		{
			v[0] = 2;
			v[i-1] = 1;
			break;
		}
		else if (v[i] > 1) v[i] = 2;
	}
	return true;
}



bool increment(vlong_t &c)
{
	for (size_t j = 0; j < c.size() - 1; j++)
	{
		if ( (c[j] > c[j+1]) && c[j+1] > 1) 
		{
			c[j+1]++;
			return true;
		}
	}
	return reset(c, false);
}



vlong_t init(long k)
{
	vlong_t  v(k, 1);
	int      i = 0;
	while(product(v) < sum(v))
		v[i++] = 2;
	return v;
}
	
bool findps(vlong_t &v, int index)
{
	long p = product(v);
	long s = sum(v);
	if (v[index] == 1)
	   return false;
	if (DEBUG) pout("findps", v);
	if (p == s) return true;
	else if (p > s)
	{
		//increment(v);
		reset(v, true);
		return findps(v, 0);
	}
	if (!increment(v)) { reset(v, true); index = 0; }
	return findps(v, index);
}
	
bool work(vlong_t &v)
{
	size_t i = 0;
	while(i < v.size() && v[i] != 1) i++;  // i - 1 points to last non-zero element
	if (i > 0)  i--;
	v[i] = 1;
	v[0]++;
	return findps(v, 0);
}

int main()
{
	char str[100];
	vlong sol;
	long maxnum = 12000;
	for (long n = 2; n <= maxnum; n++)
	//long n = 10;
	{
		vlong_t a = init(n);
		if (DEBUG) pout("INIT", a);
		if (product(a) == sum(a))
		{
		    sprintf(str, "k = %ld", n);
		    pout(str, a);
		}
		else
		{
		    //sprintf(str, "k = %ld (INIT)", n);
			//pout(s, a);
			work(a);
			sprintf(str, "k = %ld", n);
			pout(str, a);
			//findps(a, 0);
			//if (DEBUG) pout("TEST", a);
		}
		long p = product(a);
		long s = sum(a);
		if (p == s)
		{
			if (!sol.exists(s)) sol.add(s);
		}
		else
		{
			printf("ERROR at k = %ld\n", n);
			exit(1);
		}
	}
	printf("Sum of unique minimal product-sum numbers from 2 thru %ld is %ld\n",
		maxnum, sol.sum());
		
	return 0;
}
	
