// what is the largest prime divisor 
// of the given number??

#ifndef __PRIME_H__
#define __PRIME_H__

// function check whether a number
// is prime or not
#include <vector>
#include <stdio.h>
#include <stdlib.h>

//
// three key functions in this header file (no library, all inline)
//
// number is ANY number for which prime factorization is required
// pfactors is a vector list of factors
void prime_factor( long number,  std::vector<long> &pfactors);

// prodf will return the product of the long vector
//
long prodf(std::vector<long> &v);

//
// isPrime will test 'n', true if it is a prime, false if not a prime
bool isPrime(long n);

//
// print_factors prints the list of factors and the composite number
void print_factors(std::vector<long> &pv);

//
//
//


static
long prime_list[] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 
	71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 
	151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 
	233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 
	317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 
	419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 
	503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 
	607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 
	701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 
	811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 
	911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997
	};
static
long	plist_size = sizeof(prime_list)/sizeof(long);
static
long plist_next = 1009; // first prime after prime_list

// for numbers greater than 1000
inline
bool isPrime(long n)
{
	//printf("Is %ld prime? ", n);
	// Corner cases
	if (n <= 1)
		return false;
	if (n <= 3)
		return true;

	// This is checked so that we can skip
	// middle five numbers in below loop
	if (n % 2 == 0 || n % 3 == 0)
		return false;

	for (long i = 5; i * i <= n; i = i + 6)
	{
		if (n % i == 0 || n % (i + 2) == 0)
		{
			//printf("NO\n");
			return false;
		}
	}
	//printf("YES\n");
	return true;
}

inline
long next_prime(long n)
{
	if (n % 2 == 0) n++;
	if (n % 5 == 0) n+=2;
	if (isPrime(n)) return n;
	return next_prime(n + 2);
}

inline
long div_prime_list(std::vector<long> &pfactors, long n, int start_index = 0)
{
	long np = -1;
	int i;
	bool found = false;
	if (start_index >= plist_size) return n;
	// checks with first set of primes
	for (i = start_index; prime_list[i] > 0 && !found; i++)
	{
		if ( (n % prime_list[i]) == 0)
		{
			pfactors.push_back(prime_list[i]);
			np = n / prime_list[i];
			found = true;
			//printf("== %ld has %ld as a factor - leaving %ld\n", 
			//	n, prime_list[i], np);
			np = div_prime_list(pfactors, np, i);
			return np;
		}
	}
	return n;
}



inline
void print_factors(std::vector<long> &pv)
{
	printf("The prime factors of %ld are: \n", prodf(pv));
	for (size_t i = 0; i < pv.size(); i++)
	{
		printf("  %ld\n", pv[i]);
	}
}

inline
long prodf(std::vector<long> &v)
{
	long p = 1;
	for (size_t i = 0; i < v.size(); i++) p *= v[i];
	return p;
}

// Prime factor
inline
void prime_factor( long number,  std::vector<long> &pf)
{
	long n = div_prime_list(pf, number);
	long k = plist_next;
	long prod = prodf(pf);

	//printf("++ k = %ld  n = %ld\n", k, n);
	while(prod != number)
	{
		while ((n % k) == 0)
		{
			prod *= k;
			pf.push_back(k);
			//long nn = n / k;
			//printf("++ %ld has %ld as a factor - leaving %ld\n", 
			//	n, k, nn);
			n = n / k;
		}
		k = next_prime(k + 2);
	}
	//printf("Next prime after %ld is: %ld\n", plist_next, next_prime(plist_next+2));
}

#endif
