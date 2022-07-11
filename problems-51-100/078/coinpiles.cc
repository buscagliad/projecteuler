#ifdef PROBLEM_DESCRIPTION



Let p(n) represent the number of different ways in which n coins can be separated into piles. For example, five coins can be separated into piles in exactly seven different ways, so p(5)=7.
OOOOO
OOOO   O
OOO   OO
OOO   O   O
OO   OO   O
OO   O   O   O
O   O   O   O   O

Find the least value of n for which p(n) is divisible by one million.


// coins [i] = { 1 , 2, 3, ..., i }
amount = 200
ways [0.. amount ] = { uninitialized array }
ways [0] = 1;
for i = 1 to 8 do :
	for j = i to total do :
		ways [ j ] = ways [ j ] + ways [j - i]
print ways [ amount ]

#endif

#include <cstdio>
#include <cstring>

typedef unsigned long int ulong;

#ifdef DONT_USE
#define MAXDIM 20000l
ulong    precomp[MAXDIM][MAXDIM];

ulong	ways(long total, long max)
{
	if (max <= 1) return 1;
	// by defintion
	ulong res = 0;
	while (total >= 0)
	{
		ulong w;
		if ( (total < MAXDIM) && (max < MAXDIM) && (precomp[total][max-1] > 0) )
		{
			w = precomp[total][max-1];
		}
		else
		{
			w = ways(total, max-1);
			if ( (total < MAXDIM) && (max < MAXDIM) )
				precomp[total][max-1] = w;
		}
		res = res + w;
		total = total - max;
	}
	return res;
}
#endif

ulong ways(ulong *piles, ulong total)
{
// coins [i] = { 1 , 2, 3, ..., i }
//amount = 200
	//ulong piles [total+1]; // = { uninitialized array }
	memset(piles, 0, (total+1)*sizeof(ulong));
	piles [0] = 1;
	for (ulong i = 1; i <= total; i++)
	{
		if (i%100000 == 0) printf(".\n");
		for (ulong j = i; j <= total; j++)
		{
			piles [ j ] += piles [j - i];
			piles [ j ] %= 1000000;
		}
	}
	//for (int i = 1; i <= total; i++)
	//    printf("Ways[%d] = %lu\n", i, piles[i]);
	return piles[total];
}


int main()
{
	ulong piles [60001]; // = { uninitialized array }
	ulong	total = 60000;	// desired total
	ulong   w = 241;
	ulong   i = 1;
	w = ways(piles, total);
	printf("Piles 55374: %lu\n", piles[55374]);
	//memset(precomp, 0, MAXDIM * MAXDIM * sizeof(ulong));
	while( piles[i] % 1000000 != 0 && i < total) i++;
	{
	//	total++;
		printf("Number of ways to add to %lu is %lu\n", i, 
			piles[i]);
	}
}


