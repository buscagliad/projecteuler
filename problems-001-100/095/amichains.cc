#ifdef PROBLEM_DESCRIPTION

Amicable chains


  [Show HTML problem content]  
Problem 95

The proper divisors of a number are all the divisors excluding the number itself. For example, the proper divisors of 28 are 1, 2, 4, 7, and 14. As the sum of these divisors is equal to 28, we call it a perfect number.

Interestingly the sum of the proper divisors of 220 is 284 and the sum of the proper divisors of 284 is 220, forming a chain of two numbers. For this reason, 220 and 284 are called an amicable pair.

Perhaps less well known are longer chains. For example, starting with 12496, we form a chain of five numbers:

12496 → 14288 → 15472 → 14536 → 14264 (→ 12496 → ...)

Since this chain returns to its starting point, it is called an amicable chain.

Find the smallest member of the longest amicable chain with no element exceeding one million.

#endif


#include "base10.h"
#include "vlong.h"
#include "factor.h"

#define MAX_AMICABLE_CHAIN_VALUE 1000000


void out(vlong &v, int &repIndex)
{
	vlong_it vi = v.begin();
	int rep = v.size();
	printf("[%2d] %ld ", rep, *vi);
	for (vi++; vi != v.end(); vi++)
	{	
		printf(" → %ld", *vi);
	}
	if (repIndex>=0)
	    printf(" (→ %ld)", v[repIndex]);
	else
		printf(" → %ld", v[0]);
	printf("\n");
	fflush(stdout);
}

bool testa(long n, vlong &v, int &repIndex)
{
	factor f(n);
	vlong_t t;
	t = f.divisors();
	if (t.size() == 1) {
		//printf("%ld is prime\n", n);
		return false;
	}
	//printf("N: %ld  \n", n);
	//vl_out(t);
	long   sd = sum(t);
	if (sd > MAX_AMICABLE_CHAIN_VALUE) return false;
	repIndex = v.find(sd);
	//printf("    rep: %d   n: %ld   sd: %ld\n", repIndex, n, sd);
	if (repIndex >= 0) return true;
	v.add(sd);
	return testa(sd, v, repIndex);
}

int test(long n)
{
	if (isPrime(n)) return 0;
	vlong  v(false);  // unordered set
	int    repIndex;
	v.clear();
	repIndex = -1;
	v.add(n);
	testa(n, v, repIndex);
	if (repIndex == 0) out(v, repIndex);
	else return 0;
	//printf("repIndex = %d\n", repIndex);
	return v.size();
}


int main()
{
	//test(12496); return 1;
	//test(362562);
	//return 0;
	int nn = 0;
	int mn = 0;
	for(long n = 28; n < MAX_AMICABLE_CHAIN_VALUE; n++)
	{
		int	tn = test(n);
		if (tn > mn)
		{
			mn = tn;
			nn = n;
		}
	}

	printf("Longest amicable chain with numbers less than %d is %d at N = %d\n\n", MAX_AMICABLE_CHAIN_VALUE,
			mn, nn);
	//test(nn);
}
	
