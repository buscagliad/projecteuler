//
//
// Using all of the digits 1 through 9 and concatenating them freely to form decimal integers, 
// different sets can be formed. Interestingly with the set {2,5,47,89,631}, all of the elements 
// belonging to it are prime.
//
// How many distinct sets containing each of the digits one through nine exactly once contain 
// only prime elements?
//

#include <string>
#include <algorithm>

#include "digit.h"
#include "prime.h"
#include "base10.h"

using namespace std;

long  cprimes(string b)
{
	long rv = 0;
	string::iterator	start = b.begin();
	string::iterator    end = b.end();

	do
	{
		if (isPrime(stol(b))){
			//printf("%ld\n", stol(b));
			 rv++;
		}
	} while (next_permutation(start, end));
	return rv;
}	 

int	getplist(vector<long> &list, int n)	// get list of n-digit non-repeating digit primes
{
	long minp = xpower(10, n-1);
	long maxp = 10 * minp;
	printf("n: %d  Min: %ld  Max: %ld\n", n, minp, maxp);
	Prime	p(1l);
	long	np = p.next();
	while(np < minp) np = p.next();
	do {
		if (!repeatDigits(np))
		{
			list.push_back(np);
			//printf("%ld - %ld\n", list.size(), np);
		}
		np = p.next();
	} while (np < maxp);
	printf("Found %lu - %d digit non-repeating primes\n", list.size(), n);
	return list.size();
}

long   eight()
{
	long d = 0;
	string  b2("13456789");
	string  b3("12456789");
	string  b5("12346789");
	string  b7("12345689");
	d += cprimes(b2);
	d += cprimes(b3);
	d += cprimes(b5);
	d += cprimes(b7);
	return d;
}

typedef vector<long> vlt;
typedef vector<long>::iterator vil;

	

long do2(vlt &a, vlt &b, int bmult)
{
	int count = 0;
	for (vil bi = b.begin(); bi != b.end(); bi++)
	{
		for (vil ai = a.begin(); ai != a.end(); ai++)
		{
			if (isPandigital((*ai) + bmult * (*bi)))
			{
				//printf("Set: {%ld,%ld} is good!\n", *ai, *bi);
				count++;
			}
			else
			{
				//printf("Set: {%ld,%ld} is BAD!\n", *ai, *bi);
			}
		}
	}
	return count;
}
		
long do3(vlt &a, vlt &b, long bmult, vlt &c, long cmult)
{
	int count = 0;
	long num;
	for (vil ci = c.begin(); ci != c.end(); ci++)
	{
		for (vil bi = b.begin(); bi != b.end(); bi++)
		{
			if (*bi <= *ci) continue;
			for (vil ai = a.begin(); ai != a.end(); ai++)
			{
				if (*ai <= *bi) continue;
				num = *ai * bmult * cmult + *bi * cmult + *ci;
				if (isPandigital(num))
				{
					//printf("%ld - Set: {%ld,%ld,%ld} is GOOD!\n", num, *ai, *bi, *ci);
					count++;
				}
				else
				{
					//printf("%ld - Set: {%ld,%ld,%ld} is BAD!\n", num, *ai, *bi, *ci);
				}
			}
		}
	}
	return count;	
}

long do4(vlt &a, vlt &b, long bmult, vlt &c, long cmult, vlt &d, long dmult)
{
	int count = 0;
	long num;
	for (vil di = d.begin(); di != d.end(); di++)
	{
		for (vil ci = c.begin(); ci != c.end(); ci++)
		{
			if (*ci <= *di) continue;
			for (vil bi = b.begin(); bi != b.end(); bi++)
			{
				if (*bi <= *ci) continue;
				for (vil ai = a.begin(); ai != a.end(); ai++)
				{
					if (*ai <= *bi) continue;
					num = *ai * bmult * cmult * dmult + *bi * cmult * dmult + *ci * dmult + *di;
					if (isPandigital(num))
					{
						//printf("%ld - Set: {%ld,%ld,%ld,%ld} is GOOD!\n", num, *ai, *bi, *ci, *di);
						count++;
					}
					else
					{
						//printf("%ld - Set: {%ld,%ld,%ld} is BAD!\n", num, *ai, *bi, *ci);
					}
				}
			}
		}
	}
	return count;	
}

long do5(vlt &a, vlt &b, long bmult, vlt &c, long cmult, vlt &d, long dmult, vlt &e, long emult)
{
	int count = 0;
	long num;
	for (vil ei = e.begin(); ei != e.end(); ei++)
	{
		for (vil di = d.begin(); di != d.end(); di++)
		{
			if (*di <= *ei) continue;
			for (vil ci = c.begin(); ci != c.end(); ci++)
			{
				if (*ci <= *di) continue;
				for (vil bi = b.begin(); bi != b.end(); bi++)
				{
					if (*bi <= *ci) continue;
					for (vil ai = a.begin(); ai != a.end(); ai++)
					{
						if (*ai <= *bi) continue;
						//num = *ai * bmult * cmult * dmult + *bi * cmult * dmult + *ci * dmult + *di;
						num = ( ( (*ai * bmult + *bi) * cmult + *ci ) * dmult + *di) * emult + *ei;
						if (isPandigital(num))
						{
							printf("%ld - Set: {%ld,%ld,%ld,%ld,%ld} is GOOD!\n", num, *ai, *bi, *ci, *di, *ei);
							count++;
						}
						else
						{
							//printf("%ld - Set: {%ld,%ld,%ld} is BAD!\n", num, *ai, *bi, *ci);
						}
					}
				}
			}
		}
	}
	return count;	
}


long do6(vlt &a, vlt &b, long bmult, vlt &c, long cmult, vlt &d, long dmult, vlt &e, long emult, vlt &f, long fmult)
{
	int count = 0;
	long num;
	for (vil fi = f.begin(); fi != f.end(); fi++)
	{
		for (vil ei = e.begin(); ei != e.end(); ei++)
		{
			if (*ei <= *fi) continue;
			for (vil di = d.begin(); di != d.end(); di++)
			{
				if (*di <= *ei) continue;
				for (vil ci = c.begin(); ci != c.end(); ci++)
				{
					if (*ci <= *di) continue;
					for (vil bi = b.begin(); bi != b.end(); bi++)
					{
						if (*bi <= *ci) continue;
						for (vil ai = a.begin(); ai != a.end(); ai++)
						{
							if (*ai <= *bi) continue;
							//num = *ai * bmult * cmult * dmult + *bi * cmult * dmult + *ci * dmult + *di;
							num = ( ( ( (*ai * bmult + *bi) * cmult + *ci ) * dmult + *di) * emult + *ei) * fmult + *fi;
							if (isPandigital(num))
							{
								printf("%ld - Set: {%ld,%ld,%ld,%ld,%ld,%ld} is GOOD!\n", num, *ai, *bi, *ci, *di, *ei, *fi);
								count++;
							}
							else
							{
								//printf("%ld - Set: {%ld,%ld,%ld} is BAD!\n", num, *ai, *bi, *ci);
							}
						}
					}
				}
			}
		}
	}
	return count;	
}	


int main()
{
	long e = eight();
	printf("sets of 8 digits + 1 digit prime: %ld\n", e);
	vector<long> p7, p6, p5, p4, p3, p2;
	vector<long> p1 = {2, 3, 5, 7};
	getplist(p2, 2);
	getplist(p3, 3);
	getplist(p4, 4);
	getplist(p5, 5);
	getplist(p6, 6);
	getplist(p7, 7);
	e += do2(p7, p2, 10000000);
	e += do2(p6, p3, 1000000);
	e += do2(p5, p4, 100000);
	
	e += do3(p6, p2, 100, p1, 10);
	e += do3(p7, p1, 10, p1, 10);
	e += do3(p5, p3, 1000, p1, 10);
	e += do3(p5, p2, 100, p2, 100);
	e += do3(p4, p4, 10000, p1, 10);
	e += do3(p4, p3, 1000, p2, 100);
	e += do3(p3, p3, 1000, p3, 1000);
	
	e += do4(p6, p1, 10, p1, 10, p1, 10);
	e += do4(p4, p3, 1000, p1, 10, p1, 10);
	e += do4(p4, p2, 100, p2, 100, p1, 10);
	e += do4(p3, p3, 1000, p2, 100, p1, 10);
	e += do4(p3, p2, 100, p2, 100, p2, 100);
	
	e += do5(p5, p1, 10, p1, 10, p1, 10, p1, 10);
	e += do5(p4, p2, 100, p1, 10, p1, 10, p1, 10);
	e += do5(p3, p3, 1000, p1, 10, p1, 10, p1, 10);
	e += do5(p3, p2, 100, p2, 100, p1, 10, p1, 10);
	e += do5(p2, p2, 100, p2, 100, p2, 100, p1, 10);
	
	e += do6(p3, p2, 100, p1, 10, p1, 10, p1, 10, p1, 10);
	e += do6(p2, p2, 100, p2, 100, p1, 10, p1, 10, p1, 10);
	printf("Total number of prime sets: %ld\n", e);
}
/*
*/
