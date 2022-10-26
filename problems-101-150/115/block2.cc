//
// This problem will be solve by recursion
//
// The function F(m,n) returns the number of ways a pallet of the given
// size n, can be covered by red blocks (of size m or more) which have at least one
// black block between them.
//
// This function is called it will add blocks for length m to the pallet size n and will
// then recursively call itself to add blocks of variying size and starting positions
//
// 

#include <cstdio>

#define MAX_PALLET 100

long	M[MAX_PALLET+1];

void  init()
{

	for (int i = 0; i <= MAX_PALLET; i++) M[i] = 0;
}

long   F(int m, int n)
{
	long sum = 1;  // always have 1 if m > n
	// no more solutions possible
	if (m > n) return sum;
	if (M[n] > 0) return M[n];
	for (int brick = m; brick <= n; brick++) // brick size starts at m and goes
													// until n (the largest brick possible
	{
		for (int r = 0; r <= n - brick; r++) // start position (n - brick) is last position to
										 // put a block of length brick
		{
			sum += F(m, n - r - brick - 1);   // we have a split the pallette by this brick, 
												// call F eith the remaining pallette size of 
												// n - r - brick - 1
//                   r+brick-1	
//					 |					
//         |-----RRRRR---------------------------|   <--  pallette of size n
//          0    r   |-                              <--  need to add a blank in from of RRRRR before recursing
//                     --------------------------|
//                     \    n - r - brick - 1   /
		}
	}
	M[n] = sum;

	//printf("n: %d  sum: %ld \n", n, sum);
	return sum;
}

// F(m, n)

long   Fold(int m, int n)
{
	long sum = 1;  // always have 1 if m > n
	// no more solutions possible
	if (m > n) return sum;
	if (M[n] > 0) return M[n];
	for (int r = 0; r <= n - m; r++) // start position (n - m is last position to
									 // put a block of length m
	{
		for (int brick = m; brick <= n - r; brick++) // brick size starts at m and goes
														// until
		{
			sum += F(m, n - r - brick - 1);
		}
	}
	M[n] = sum;

	//printf("n: %d  sum: %ld \n", n, sum);
	return sum;
}



int minn(int bsize, long numcombos)
{
	for (int psize = bsize; psize < 10000; psize++)
	{
		init();
		long cnt = F(bsize, psize);
			printf("F(%d.%d) =   %ld\n", bsize, psize, cnt);

		if (cnt > numcombos) {
			printf("*** F(%d.%d) =   %ld\n", bsize, psize, cnt);
			return psize;
		}
	}
	return -1;
}


int main()
{
	init();
	minn(3, 1000000);
	minn(10, 1000000);
	minn(50, 1000000);
}
