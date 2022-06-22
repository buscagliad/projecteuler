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
#include <cmath>

#include "vlong.h"
#include "factor.h"

#define DEBUG 0


// p = a1 * a2 * a3 * ... * am
// s = sum(a1, am) + k - m
// N = p = s
// N goes from k .. 2*k


#define DUMP(t) if (DEBUG) {pout(t, gc); printf("   Line:%d :: gix:%d  g1:%d\n", __LINE__, gix, g1); }
	

vlong_t	gc;
int     gix;
int     g1;

int numones(vlong_t &c)
{
	int rv = 0;
	for (size_t i = 0; i < c.size(); i++) if (c[i] == 1) rv++;
	return rv;
}

void pout(const char *t, vlong_t &c)
{
	if (!DEBUG) return;
	long s = sum(c);
	long p = product(c);
	int  no = numones(c);
	int  nn = c.size() - no;
	printf("k = %lu  gix = %d  g1 = %d  %s  %ld = %ld", c.size(), gix, g1, t, s, c[0]);
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

bool ginc(long &p, long &s);


bool greset(bool shrink = true)
{
	//printf("greset()\n");
	
	//if ( (gc[1] != 2) || (gc[0] == gc[1]) ) shrink = false;
	//printf("RESET\n");
	gc[1] = 2;
	char str[100];
	//long p, s;
	if (gix == 1 && g1 > 2) shrink = true;
	
	//shrink = false;
	
	//ginc(p, s);
	if (!shrink) {
		for(int i = 1; i < g1 - 1; i++)
		{
			gc[i] = 2;
		}
		gc[0]++;
		gix = 1;
		//sprintf(str, "a RESET shrink: %d", shrink);
		//pout(str, gc);
		return true;
	}
	gix = 1;
	for(int i = 1; i < g1 - 1; i++)
	{
		gc[i] = 2;
	}
	if (shrink)
	{
		//gc[0]++;
		g1--;
		gc[g1] = 1;
		//gc[0]++;
	}
	//sprintf(str, "b RESET shrink: %d", shrink);
	//pout(str, gc);	
	return true;
}

void shrink(long &p, long &s)
{
	//gc[0]++;
	g1--;
	gc[g1] = 1;
	gix = 1;
	p = product(gc);
	s = sum(gc);
	DUMP("shrink");
	if (p > s) shrink(p, s);
	//gc[0]++;
}

bool ggreset(long &p, long &s)
{

	for(int i = 1; i < g1; i++)
	{
		gc[i] = 2;
	}
	//if (gc[0] > 3) gc[0] /= 2;
	gix = 1;
	gc[0]++;
	p = product(gc);
	s = sum(gc);
	pout("ggreset", gc);
	return true;
}

//
// increment will increment the last element in the list for which
// c[n] < c[n-1]
bool ginc(long &p, long &s)
{

	if (p > s)
	{
		//greset(false);
		ggreset(p,s);
		pout("ginc-ggreset", gc);
		if (p > s)
		{
			shrink(p, s);
			pout("ginc-shrink", gc);
		}
	}
	else if (gix >= g1) {
		shrink(p,s);
		pout("ginc-shrink-2", gc);
	}
	else {
		gc[gix]++;
		gix++;
		if (gix == g1) gix = 1;
		p = product(gc);
		s = sum(gc);
		pout("ginc-ginc", gc);
		//if (p > s) shrink(p, s);
	}

	return true;
}



void init(long k, long &p, long &s)
{
	vlong_t  v(k, 1);
	int      i = 0;
	if (k == 2)
	{
		v[0] = 2;
		v[1] = 2;
		gc = v;
		p = product(gc);
		s = sum(gc);
		return;
	}
	while(i < k && product(v) < sum(v))
		v[i++] = 2;
	//v[i-1] = 1;
	g1 = i;
	gix = 0;
	gc = v;
	p = product(gc);
	s = sum(gc);
}


bool gfind(long &p, long &s)
{
	p = product(gc);
	s = sum(gc);
	while(p != s)
	{
		ginc(p, s);
		//if (DEBUG) pout("gfind", gc);
		//if (p > s) ginc(p,s);
	}
	return true;
}
	

bool gwork(long &p, long &s)
{
	size_t i = 0;
	while(i < gc.size() && gc[i] != 1) i++;  // i - 1 points to last non-zero element
	if (i > 0)  i--;
	gc[i] = 1;
	gc[0]++;
	return gfind(p, s);
}

int main()
{
	char str[100];
	vlong sol;
	long maxnum = 120;
	for (long n = 2; n <= maxnum; n++)
	//long n = 29;
	{
		long p;
		long s;
		init(n, p, s);
		if (DEBUG) pout("INIT", gc);
		if (p != s)
		{
			//work(a);
			gfind(p, s);

		    //sprintf(str, "k = %ld (INIT)", n);
			//pout(s, a);
			//findps(a, 0);
			//if (DEBUG) pout("TEST", a);
		}
		if (p == s)
		{
			if (!sol.exists(s)) sol.add(s);
			if (DEBUG) printf("\n");
			sprintf(str, "%ld SOLUTION", sol.sum());
			pout(str, gc);
			if (DEBUG) printf("\n");
		}
		else
		{
			printf("ERROR at k = %ld    p = %ld   s = %ld\n", n, p, s);
			exit(1);
		}
	}
	printf("Sum of unique minimal product-sum numbers from 2 thru %ld is %ld\n",
		maxnum, sol.sum());
		
	return 0;
}
	

