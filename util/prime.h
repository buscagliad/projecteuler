// what is the largest prime divisor 
// of the given number??

#ifndef __PRIME_H__
#define __PRIME_H__

// function check whether a number
// is prime or not
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "vlong.h"

//
// three key functions in this header file (no library, all inline)
//
// number is ANY number for which prime factorization is required
// pfactors is a vector list of factors
void prime_factor( long number,  vlong_t &pfactors);

//
// isPrime will test 'n', true if it is a prime, false if not a prime
bool isPrime(long n);

//
// coPrime will return true if M and N do not have any prime factors in common
bool coPrime(long m, long n);

//
// print_factors prints the list of factors and the composite number
void print_factors(vlong_t &pv);


#define PRIME_FILE_DIRECTORY "/home/dave/projecteuler/primes/"
#define PRIME_TITLE_SIZE 100
#define PRIME_FILE_SIZE 1000000
#define PRIME_FILE_MAX  50  // currently only first 50 million primes
#define PRIME_MAX_NUMBERS 50000000 // product of FILE_SIZE * FILE_MAX
static	long prime_list[PRIME_MAX_NUMBERS];
static	char prime_file_title[PRIME_TITLE_SIZE];
static	char prime_file_name[PRIME_TITLE_SIZE];
static	int  prime_file_index = 0;  // file 1 thru 50
static	int  prime_list_size;
//static	int  prime_list_index;
static	long  prime_min_value;
static  long  prime_max_value;
static	long  prime_max_index;

class Prime {
	public:
		Prime(bool load_all = false);			// reads in first million primes, sets index to 0
		long operator[] (int n) { return get(n); };
		bool isPrime(long p){ return ::isPrime(p); };  // returns true if 'p' is prime
		long next();		  // returns next prime
		void reset();		  // loads 1st million primes and sets index to 0
								// returns true if n and m have no common factors
		bool coPrime(long n, long m) {return ::coPrime(n, m); };
		vlong_t	factor(long n);	// returns factors 
		long get(int n);		// if n < 0 or n >= 
	private:
};

#define INIT_FILE	if (prime_file_index == 0) readFile(1);

inline
bool	readFile(int n)
{
	#define MAX_LINE 1000
	if (n < 1 || n > PRIME_FILE_MAX) 
	{
		printf("ERROR - requested file exceeds allowed number (cur file:%d -  des file: %d)\n",
			prime_file_index, n);
		return false;
	}
	if (n == 1) prime_list_size = 0;
	if (n <= prime_file_index) return true;
	if (n - prime_file_index > 1)
	{
		printf("ERROR - cannot read into the middle of prime array (cur file:%d -  des file: %d)\n",
			prime_file_index, n);
		return false;
	}
	prime_file_index = n;
	sprintf(prime_file_name, "%sprimes%2.2d.txt", PRIME_FILE_DIRECTORY, prime_file_index);
	char	line[MAX_LINE];
	FILE *f = fopen(prime_file_name, "r");
	if (!f) return false;
	fgets(prime_file_title, PRIME_TITLE_SIZE, f);
	fgets(line, MAX_LINE, f); // skip line
	while (!feof(f) && prime_list_size < n * PRIME_FILE_SIZE)
	{
		fscanf(f, "%ld", prime_list + prime_list_size);
		prime_list_size++;
	}
	prime_min_value = prime_list[0];
	prime_max_value = prime_list[prime_list_size-1];
	prime_max_index = n * PRIME_FILE_SIZE;
	printf("ReadFile: %s    Min: %ld   Max: %ld - %d elements\n",
		prime_file_name, prime_min_value, prime_max_value, prime_list_size);
	fclose(f);
	return true;
}	

inline
Prime::Prime(bool load_all)
{
	readFile(1);
	if (load_all)
	{
		for(int k = 2; k <= PRIME_FILE_MAX; k++)
		    readFile(k);
		#ifdef DEBUG_PRIME_FILE
		FILE *f = fopen("/tmp/allprimes.txt", "w");
		for (int i = 0; i < prime_max_index; i++)
		    fprintf(f, "%9d   %20ld\n", i, prime_list[i]);
		    
		fclose(f);
		#endif
	}
}	

int binarySearch(long array[], int x, int low, int high) 
{

	// Repeat until the pointers low and high meet each other
	while (low <= high) 
	{
		int mid = low + (high - low) / 2;

		if (array[mid] == x)
			return mid;

		if (array[mid] < x)
			low = mid + 1;

		else
			high = mid - 1;
	}

	return -1;
}

// isPrime uses the 50000000 primes defined in the file set
// if those cannot find that it's a prime, the sieve method is 
// finally used for numbers greater than the 50000000th prime
inline
bool isPrime(long n)
{
	INIT_FILE;
	if ( n <= 1) return false;
	// This is checked so that we can skip
	// middle five numbers in below loop
	if (n % 2 == 0 || n % 3 == 0)
		return false;
	
	if ( (n < prime_min_value) && (prime_file_index > 1) )
	{
		readFile(prime_file_index - 1);
		return isPrime(n);
	}
	if ( (n > prime_max_value) && (prime_file_index < 50) )
	{
		readFile(prime_file_index + 1);
		return isPrime(n);
	}
	int  k = 0;
	//while (k < PRIME_FILE_SIZE  &&  n > prime_list[k]) k++;
	k = binarySearch(prime_list, n, 0, prime_max_index);
	//printf("n = %ld  k = %d  P(k) = %ld \n", n, k, prime_list[k]);
	if (k > -1)
	{
		//printf("isPrime:: %ld is prime from file: %d at index %d\n",
		//	n, prime_file_index, k);
		return true;
	}
		
	return false;
}

// next_prime with a long argument, sets the
// index of the prime point to point to the first
// prime number after n 

static int	prime_next_index = -1;
inline
long next_prime(long n)
{
	INIT_FILE;
	if (n < 2) n = 2;
	else n++;
	
	if ( (n < prime_min_value) && (prime_file_index > 1) )
	{
		readFile(prime_file_index - 1);
		return next_prime(n);
	}
	if ( (n > prime_max_value) && (prime_file_index < 50) )
	{
		readFile(prime_file_index + 1);
		return next_prime(n);
	}
	int  k = 0;
	while (k < PRIME_FILE_SIZE  &&  n >= prime_list[k]) k++;
	printf("n = %ld  k = %d  P(k) = %ld \n", n, k, prime_list[k]);
	return prime_list[k];
}

long next_prime()
{
	if (prime_next_index < 0) next_prime(1);
	prime_next_index++;
	if (prime_next_index >= prime_max_index) 
	{
		readFile(prime_file_index + 1);
		prime_next_index = 0;
	}
	return prime_list[prime_next_index];
}

//
// find all factors from the prime_list (see prime_list.h)
//
inline
long div_prime_list(vlong_t &pfactors, long n, int start_index = 0)
{
	long np = -1;
	int i;
	bool found = false;
	if (start_index >= prime_list_size) 
	{
		if ( (prime_file_index + 1) <= PRIME_FILE_MAX)
		{
		    readFile(prime_file_index+1);
		    start_index = 0;
		}
		else
		    return n;
	}
	// checks with first set of primes
	for (i = start_index; i < PRIME_FILE_SIZE && !found; i++)
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
void print_factors(vlong_t &pv)
{
	printf("The prime factors of %ld are: \n", product(pv));
	for (size_t i = 0; i < pv.size(); i++)
	{
		printf("  %ld\n", pv[i]);
	}
}


// Prime factor
//  returns list(vector) of prime factors of 'number'
//  with multiplicities; i.e. 12 = 2 * 2 * 3 --- two '2's will be in pf
inline
void prime_factor( long number,  vlong_t &pf)
{
	INIT_FILE;
	long n = div_prime_list(pf, number);
	long prod = product(pf);
	if (prod == number) return;
	long k = next_prime(prime_max_value+2);

	//printf("++ k = %ld  n = %ld\n", k, n);
	// if div_prime_list got ALL of the prime factors, then prod is number
	// if not, need to find next primes after larges prime in the prime_list,
	// which k is set to the 'next' number after prime_list
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

// coPrime 
inline
bool coPrime( long n,  long m)
{
	INIT_FILE;
	vlong_t	nf;
	vlong_t mf;
	prime_factor( n,  nf);
	vlong ncf(nf);
	prime_factor( m, mf);
	
	// search through all factors of m and see if they match
	// return false on any match - at the end, if none mathc
	// return true, indicating m and n are coPrime

	//printf("++ k = %ld  n = %ld\n", k, n);
	for (vlong_it mfi = mf.begin(); mfi != mf.end(); mfi++)
		if (ncf.exists(*mfi)) return false;
	return true;
}

#endif
