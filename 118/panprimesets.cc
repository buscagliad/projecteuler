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
			printf("%ld\n", stol(b));
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
	Prime	p(minp);
	long	np = p.next();
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


		
			

int main()
{
	
	//printf("sets of 8 digits + 1 digit prime: %ld\n", eight());
	vector<long> p7, p6, p5, p4, p3, p2;
	getplist(p2, 2);
	getplist(p3, 3);
	getplist(p4, 4);
	getplist(p5, 5);
	getplist(p6, 6);
	getplist(p7, 7);
}

