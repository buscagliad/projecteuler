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


// tcount(n, m)   n - number of tiles, m width of cube
// single color only
long   tcount(int n, int m)
{
	long sum = 1;  // always have 1 if m > n
	// no more solutions possible
	if (m > n) return 1;
	if (M[m][n] > 0) return M[m][n];
	for (int r = 0; r <= n - m; r++) // start position (n - m is last position to
									 // put a block of length m
	{
		sum += tcount(n - r - m, m);
												// n - r - brick - 1
//         m R's     r+m+1	
//				\	 |					
//         |-----RRRRR---------------------------|   <--  pallette of size n
//          0    r   |---------------------------|   <--  need to add a blank in from of RRRRR before recursing
//                    \     n - r - m           /
	}
	M[m][n] = sum;

	//printf("n: %d  sum: %ld \n", n, sum);
	return sum;
}




void do116(int m)
{
	init();
	long red = tcount(m, RED)-1;
	long green = tcount(m, GREEN)-1;
	long blue = tcount(m, BLUE)-1;
	long total = red + green + blue;
	printf("%d Pallett::  Red tiles: %ld  Green tiles: %ld  Blue tiles: %ld  Total: %ld\n", 
	    m, red, green, blue, total);
}

int main()
{
	init();

	do116(5);
	do116(50);
}
