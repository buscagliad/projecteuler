#include "factor.h"

long pvec[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
long pwr[]  = {1, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1};
long ks[]   = {1, 1, 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1};


// for a given vector k of powers of primes, and number 'N" is computed
// based on summing pvec[i] ^ k[i]
// and the number of pairs for the reciprical diophantine equation
// np is computed by computing the product:  product(2 * k[i] + 1) then adding 1
void computeNP(long *k, int ksize, long &N, long &np)
{
	int		prod = 1;
	N = 1;
	
	for (int i = 0; i < ksize; i++)
	{
		prod *= 2 * k[i] + 1;
		N *= xpower(pvec[i], k[i]);
	}
	
	np = (prod + 1) / 2;
}

// find the first 'digit' that is less than
// the one that precedes it
void    resetA(long *v, int &N)
{
	printf("reset\n");
	int	s = 0;
	for (int i = 0; i < N - 1; i++)
	{
	    if (v[i] > v[i+1]) 
	    {
			s=i+1;
			v[s]++;
			s++;
		}
	}
	for (int i = s; i < N; i++)
		v[i] = 1;
}

// find the first 'digit' that is less than
// the one that precedes it
void    reset(long *v, int &N)
{
	printf("reset ");
	// find the 
	
	int	s = -1;
	for (int i = 0; i < N - 1; i++)
	{
	    if (v[i] > v[i+1]) 
	    {
			if (v[i+1] == 1)
			{
				s = 0;
				printf("  setting s to 0 ");
			}
			else
			{
				s=i+1;
				printf("  setting s to %d ", s);
			}
			v[s]++;
			s++;
			break;
		}
	}
	if (s == -1)
	{
		v[0]++;
		s = 1;
	}
		
	printf("  setting to 1 from %d on\n", s);
	for (int i = s; i < N; i++)
		v[i] = 1;
}


//
//

void    resize(long *v, int &N)
{
	printf("resize\n");
	N--;
	for (int i = 0; i < N; i++)
		v[i] = 1;
}

bool	adjust(long *v, int &N)
{
	printf("adjust\n");
	for (int i = N-1; i > 0; i--)
	{
		if (v[i] < v[i-1]) { 
			v[i]++; 
			for (int j = i+1; j < N; j++) v[j] = 1;
			return true; 
		}
	}
	v[0]++;
	//
	// if we get here - all v's are the same
	return false;
}
	

#define PRINT	printf("N: %20ld  Pairs: %10ld   GN: %20ld  GPairs: %10ld   PrimePowers: ", N, pairs, goodN, goodPairs); \
				for (int i = 0; i < psize; i++) printf(" %2ld ", p[i]); printf("\n");


int main3()
{
	bool    done = false;
	long	p[] = {1,1,1,1,1,1,1,1,1,1,1,1};
	int		psize = 12;
	long    N = 0, pairs = 0;
	long    goodN, goodPairs;
	computeNP(p, psize, goodN, goodPairs);
	printf("N = %ld   pairs = %ld\n", goodN, goodPairs);
	for (int k = 1; !done && k < 100; k++) // while (!done)
	{
		
		adjust(p, psize);
		computeNP(p, psize, N, pairs);
			PRINT;
		if ( (pairs > 4000000) && N < goodN)
		{
			goodN = N;
			goodPairs = pairs;
			PRINT;
		}
		if (N > goodN)
		{
			psize--;
			p[0]++;
			for (int i = 1; i < psize; i++)
			    p[i] = p[0];
		}
		resize(p, psize);
		// if (np > goodN)
		// {
		// 	adjust(p, psize);
		// }
		// else
		// {
		// 	increment(p, psize);
		// }
		if(psize < 4) done = true;
	}
	return 1;
}

int main()
{
	bool    done = false;
	long	p[] = {1,1,1,1,1,1,1,1,1,1,1,1};
	long    g[] = {5,2,2,2,1,1,1,1,1,1,1,1};
	int		psize = 12;
	long    N = 0, pairs = 0;
	long    goodN = 0, goodPairs = 0;
	computeNP(g, psize, goodN, goodPairs);
	printf("N = %ld   pairs = %ld\n", goodN, goodPairs);
	while (psize > 5) // for (int k = 1; !done && k < 1000; k++) // while (!done)
	{
		
		computeNP(p, psize, N, pairs);
		PRINT;
		if (N < 0)
		{
			resize(p, psize);
		}
		else if ((pairs > 4000000))
		{
			if (N < goodN)
			{
				goodN = N;
				goodPairs = pairs;
			}
			reset(p, psize);
			computeNP(p, psize, N, pairs);
			if (N > goodN)
				resize(p, psize);
		}
		else
		    adjust(p, psize);
	}
	
}
