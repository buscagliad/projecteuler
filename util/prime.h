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


#include "prime_list.h"

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
	if (n <= 2) return 3;
	if (n <= 4) return 5;
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
	if (start_index >= prime_list_size) return n;
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
	long k = prime_list_next;
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
	//printf("Next prime after %ld is: %ld\n", prime_list_next, next_prime(prime_list_next+2));
}

#endif
