//
// This problem will be solve by recursion
//
// The function count(pallet_size) returns the number of ways a pallet of the given
// size can be covered by red blocks (of size 3 or more) which have at least one
// black block between them.
//
// This function is called it will add blocks for length 3 to the pallet size and will
// then recursively call itself to add blocks on either side of the block added - with
// the pallet size remaining after adding the block
//
// The function returns 0 if the palletsize is < 3, 1 if == 3
// when a pallet size is computed, the value is stored in M so that
// subsequent calls to this function can just return that value
// instead of computing all over again.

#include <cstdio>

#define MAX_PALLET 50

long	M[MAX_PALLET+1];

void  init()
{

	for (int i = 0; i <= MAX_PALLET; i++) M[i] = 0;
}



// count(psize, minbsize)
//   psize is the size of the pallet, minbsize is the size of the block 
//   if bsize > psize done - return solutions
//   otherwise, you can place a brick and call count again with the reduced psize

long   count(int psize, int mbsize)
{
	long sum = 1;  // always have 1 if psize >= 3
	// no more solutions possible
	if (mbsize > psize) return sum;
	if (M[psize] > 0) return M[psize];
	for (int r = 0; r <= psize - mbsize; r++) // start position
	{
		for (int brick = mbsize; brick <= psize - r; brick++) // brick size
		{
			sum += count(psize - r - brick - 1, mbsize);
		}
	}
	M[psize] = sum;

	//printf("psize: %d  sum: %ld \n", psize, sum);
	return sum;
}

int main()
{
	init();
	int p = 50;
	long c = count(p, 3);
	printf("Pallet: %d   num: %ld\n", p, c);
}
