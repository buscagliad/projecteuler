#ifdef PROBLEM_DESCRIPTION

Digit factorial chains


Problem 74

The number 145 is well known for the property that the sum of the factorial of its digits is equal to 145:

1! + 4! + 5! = 1 + 24 + 120 = 145

Perhaps less well known is 169, in that it produces the longest chain of numbers that link back to 169; it turns out that there are only three such loops that exist:

169 → 363601 → 1454 → 169
871 → 45361 → 871
872 → 45362 → 872

It is not difficult to prove that EVERY starting number will eventually get stuck in a loop. For example,

69 → 363600 → 1454 → 169 → 363601 (→ 1454)
78 → 45360 → 871 → 45361 (→ 871)
540 → 145 (→ 145)

Starting with 69 produces a chain of five non-repeating terms, but the longest non-repeating chain with a starting number below one million is sixty terms.

How many chains, with a starting number below one million, contain exactly sixty non-repeating terms?
#endif

#include "base10.h"
#include "vlong.h"


void testa(long n, vlong &v, int &repIndex)
{
	base10 b(n);
	base10 c = b.digfac();
	long   cl = c.value();
	repIndex = v.find(cl);
	if (repIndex >= 0) return;
	//printf("    rep: %d   n: %ld   cl: %ld\n", repIndex, n, cl);
	v.add(cl);
	testa(cl, v, repIndex);
}

void out(vlong &v, int &repIndex)
{
	vlong_it vi = v.begin();
	int rep = v.size();
	printf("[%2d] %ld ", rep, *vi);
	for (vi++; vi != v.end(); vi++)
	{	
		printf(" → %ld", *vi);
	}
	if (repIndex)
	    printf(" (→ %ld)", v[repIndex]);
	else
		printf(" → %ld", v[0]);
	printf("\n");
}

int test(long n)
{
	vlong  v(false);  // unordered set
	int    repIndex;
	v.clear();
	repIndex = -1;
	v.add(n);
	testa(n, v, repIndex);
	if (v.size() > 59) out(v, repIndex);
	return v.size();
}


int main()
{
	int count = 0;
	for(long n = 2; n < 1000000; n++)
	    if (test(n) > 59) count++;
	printf("There are %d starting numbers less than 1000000 with factorial chains of 60\n", count);
}
	
