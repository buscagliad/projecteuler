//
// This problem will be solve by recursion
//
// The function ccount(m,n) returns the number of ways a pallet of the given
// size n, can be covered by red blocks (size 2) green(3) and blue(4) - the blocks do not need space
//
// 

#include <cstdio>

#define MAX_PALLET 	100
#define MAX_COLOR 	6
#define RED 		2
#define GREEN 		3
#define BLUE 		4

long	M[MAX_COLOR][MAX_PALLET+1];

void  init()
{

	for (int i = 0; i <= MAX_PALLET; i++) 
		for (int j = 0; j <= MAX_COLOR; j++) M[j][i] = 0;
}


long   ccount(int m, int n)	// multi-color count
{
	long sum = 1;  // always have 1 if m > n
	// no more solutions possible
	if (m > n) return sum;
	if (M[m][n] > 0) return M[m][n];
	for (int brick = m; brick <= BLUE; brick++) // brick size starts at m and goes
													// until BLUE (the largest brick possible
	{
		for (int r = 0; r <= n - brick; r++) // start position (n - brick) is last position to
										 // put a block of length brick
		{
			sum += ccount(m, n - r - brick);   // we have a split the pallette by this brick, 
												// call F eith the remaining pallette size of 
												// n - r - brick - 1
//                   r+brick+1	
//					 |					
//         |-----RRRRR---------------------------|   <--  pallette of size n
//          0    r   |---------------------------|   <--  pass this pallet into ccount
//                    \    n - r - brick        /
		}
	}
	M[m][n] = sum;

	//printf("n: %d  sum: %ld \n", n, sum);
	return sum;
}



void do117(int n)
{
	init();
	printf("%d Pallett::  Total: %ld\n", 
	    n, ccount(RED, n));
}

int main()
{
	init();

	do117(5);
	do117(50);
}
