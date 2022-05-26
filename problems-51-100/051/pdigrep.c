#ifdef PROBLEM_DESCRIPTION
Prime digit replacements

Problem 51

By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the first example having seven primes among the ten generated numbers, yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of this family, is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) with the same digit, is part of an eight prime value family.


NOTE:  I misread this problem - i thought you had to replace any two digits with the same number...
bottom line it made me code base10 to deal with choosing m things from a set of n items.  What a waste 
of time - however - i am hoping that it will be usefull in the future.

#endif
#include "utils.h"

#include "base10.h"

int
primeMake(long a, vlong_t &retPrimes)
{
	// take the number a and replace digits d1 and d2 with digits 0 thru 9,
	// return number of primes found
	int d;  // d is the digit that is repeated
	int pcount = 0;
	int maxPcount = 0;
	vlong_t primes;	// local primes - maxPcount is set by this
	vlong_t rprimes;	// local primes - maxPcount is set by this
	base10 v(a);
	if (v.unique() ) return 0;
	base10::base10i	digRep;
	if (!isPrime(a)) return 0;
	// some cases we are not handling (multiple two-digit cases
	// if 3 digits d and 1st digit is d, we have an issue
	// since we are looking for eight digit replacements - only need to look
	// for repeating 0 or repeating 1 or repeating 2 (2,3,4,5,6,7,8,9)

	for (d = 0; d <= 2; d++)
	{
		int nz = v.cdigits(d, digRep);
		if (nz < 2) continue;
		//v.setChoose(digRep, 2);	// select only two digits
		base10::base10i	digi = digRep;
		//digi = v.getNext();				// gets next choice of digit places
		//vl_out(digRep);

		primes.clear();
		
		while (digi.size())
		{
			primes.push_back(a);
			for (int k = d+1; k <= 9; k++)
			{
				v.reset();
				long p = v.sdigits(k, digi);
				//printf("k = %d    p = %ld  Prime: ", k, p);
				if (isPrime(p)) { 
					primes.push_back(p); 
					//printf("YES\n"); 
				} 
				else
				{
						//printf ("NO\n");
				}
			}
			pcount = primes.size();
			//vl_out(digi);
			//vl_out(primes);
			if (pcount >= maxPcount)
			{
				rprimes = primes;
				maxPcount = pcount;
			}
			digi = v.getNext();				// gets next choice of digit places
		}
	}
	retPrimes = rprimes;
	//if (retPrimes.size() != maxPcount) printf("ERROR--- size: %ul  max: %ld", retPrimes.size(), maxPcount);
	return maxPcount;
}


int main()
{
	Prime p(false);
	vlong_t	primes;
	int pcount = 0;
	int pindex = 25;
	int mpcount = 1;
	//primeMake(56003, primes);
	//vl_out(primes);
	//mpcount = 0;
	//primeMake(121313, primes);
	//vl_out(primes);
	//return 1;
	long last_p = 0;
	while (pcount < 8)
	{
		long p = next_prime();
		if (p < last_p)
		{
			printf("EXITTING!!  p = %ld   last_p = %ld\n", p, last_p);
			exit(1);
		}
		pcount = primeMake(p, primes);
		//if (mpcount < pcount)
		if (pcount >= 7)
		{
			mpcount = pcount;
			printf("FOUND: pcount = %d\n", mpcount);
			vl_out(primes);
		}
		pindex++;
		if (0) printf("pindex = %d   p = %ld   last_p = %ld\n", pindex, p, last_p);
		last_p = p;
	}
	
	
}
