#include <stdio.h>

long num_do_path_calls = 0;

#define XGRID 20
#define YGRID 20

// this function starts at x,y on its way to 0,0
//
// same problem in terms of number of steps
//
long do_path_rec(int x, int y)
{
	num_do_path_calls++;
	if (num_do_path_calls % 100000 == 0)
	{
		printf("x: %d   y: %d    NC: %ld\n", x, y, num_do_path_calls);
	}
	if ( (x == 0) || (y == 0) ) return 1;  // once you are at the edge - only 1 way to home
	return do_path_rec(x, y-1) + do_path_rec(x-1, y);
}

// combinatorial solution (NOTE: I only learned of this AFTER solving the
//                          recursive function - which took hours)
//
// D represents a down movement
// R represents a right movement
// stringing them together:  DDRRDRDDRRD...RDDRD
// we would need exactly N R's and N D's to get from (0,0) to (N,N)
// that means we need to figure out how many ways we can arrange N D's and N R's
// this is a combinatorics problem of 2N choose N, recalling that n choose k is:
//               n!
//   n C k = ----------
//           k!(n - k)!
//  
//            (2N)!       2N * (2N - 1) * ... * (N + 2) * (N + 1)      N   N + i
// 2N C N =  --------  = ----------------------------------------  =  P   -------
//           (N!)(N!)          N * (N - 1) * ... * 2 * 1             i = 1   i

long do_paths(long N)	// only for square grids
{
	long prod = 1;
	for (long i = 1; i <= N; i++)
	{
	    prod *= (N + i);
	    prod /= i;	// need to do divide AFTER multiply to avoid floating point numbers
	}
	return prod;
}

void test(long n)
{
	long num_paths_r = do_path_rec(n, n);
	long num_paths = do_paths(n);
	printf("    Number of paths recursive: %ld\n", num_paths_r);
	printf("Number of paths combinotorics: %ld\n", num_paths);
}

int main()
{
	test(2);
	test(3);
	long num_paths = do_paths(20);
	printf("N = 20 - paths = %ld\n", num_paths);
}
