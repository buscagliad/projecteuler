#include <cstdio>
#include <cstdlib>
#include <cstring>

long rep[] = {	        1,           11,           111,           1111,        11111, 
				   111111,      1111111,      11111111,      111111111,   1111111111, 
	          11111111111, 111111111111, 1111111111111, 11111111111111};

long getg(long p, int &n)
{
	int i = 0;
	while (rep[i] < p) i++;
	n = i;
	return rep[i];
}

#define MAXAS 500000
int As[MAXAS];
void init()
{
	memset(As, 0, MAXAS * sizeof(int));
}


int A(long p)
{
	if (As[p] > 0) return As[p];
	int n = 0;
	long r = 1;
	long g = getg(p, n);
	//printf("p: %ld   g: %ld\n", p, g); 
	while (r != 0)
	{
		n++;
		long d = g / p;
		r = g % p;
		//printf("n=%d  g=%ld  d=%ld  r=%ld\n", n, g, d, r);
		g = (g - d * p) * 10 + 1;
		//if (n>28)exit(1);
	}
	//printf("n:%d\n", n);
	As[p] = n;
	return n;
}

#include <vector>
#include <iterator>
#include <list>
#include "prime.h"

typedef struct  {
	long	p1;
	long	p2;
	long    p;
	int		Ap1;
	int		Ap2;
	int		Ap;
} comp;

using namespace std;

list<comp> clist;
typedef list<comp>::iterator clist_i;

Prime primes;

size_t  insert(comp &c)
{
	clist_i it = clist.begin();
	if (it == clist.end()) // first entry;
	{
		clist.push_back(c);
		return 1;
	}
	while(it != clist.end() && it->p < c.p) it++;
	clist.insert(it, c);
	return clist.size();
}

bool check(long p1, long p2, comp &c)
{
	c.p1 = p1;
	c.p2 = p2;
	c.p = p1 * p2;
	c.Ap1 = A(p1);
	c.Ap2 = A(p2);
	c.Ap = A(c.p);
	if ( (c.p - 1) % c.Ap == 0) return true;
	return false;
}

bool check(long p)
{
	int ap = A(p);
	if ( ( (p - 1) % ap) == 0 ) return true;
	return false;
}

void	ilist(long maxn)
{
	long p1, p2;
	int n1, n2;
	for (n1 = 1, p1 = prime_list[n1]; p1 < maxn; n1++, p1 = prime_list[n1])
	{
		if (p1 == 5) continue; // no fives
		for (n2 = n1, p2 = prime_list[n2]; p2 < maxn; n2++, p2 = prime_list[n2])
		{
			if (p2 == 5) continue; // no fives
			comp c;
			if (check(p1, p2, c))
			{
				insert(c);
			}
		}
	}
}

void  olist()
{
	clist_i it = clist.begin();
	long sum = 0;
	long count = 0;
	while (it != clist.end())
	{
		count++;
		sum += it->p;
		printf("%2ld:: A(%ld) = %d   A(%ld) = %d   A(%ld) = %d  sum: %ld\n",
			count, it->p1,	it->Ap1, it->p2, it->Ap2, it->p, it->Ap, sum);
		if (count >= 25) return;
		it++;
	}
}


long test(int maxn)
{
	long sum = 0;
	int  count = 0;
	for (int p = 91; p < 60000; p+=2)
	{
		if (isPrime(p)) continue;
		if (p % 5 == 0) continue;
		if (check(p))
		{
			sum += p;
			count++;
			printf("%d  p: %d  sum: %ld\n", count, p, sum);
			if (count == maxn)
			{
				printf("Sum is %ld\n", sum);
				return sum;
			}
		}
	}
	return 0;
}


int main()
{
	init();
	test(5);
	printf("Sum of first 25 composite numbers with repunit property is: %ld\n", test(25));
}
	
