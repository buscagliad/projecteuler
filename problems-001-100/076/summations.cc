#ifdef PROBLEM_DESCRIPTION

Counting summations


Problem 76

It is possible to write five as a sum in exactly six different ways:

4 + 1
3 + 2
3 + 1 + 1
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1

How many different ways can one hundred be written as a sum of at least two positive integers?
#endif

#include <cstdio>
#include <cstring>

#define TOTAL 100

int	sum[TOTAL+1];
int listSize = 0;
int lastIndex = 0;

bool next()
{
	// find largest index from left that can be 'fractured'
	// 
	if (sum[0] == 1) return false;
	int from = 0;
	int to = 0;
	// find the first adjacent pair that differ by two or more
	// if none - find the first two from the right
	for (; from <= lastIndex; from++)
	{
		if (sum[from] - sum[from+1] > 1) 
		{
			to = from + 1;
			break;
		}
	}
	if (to == 0) // no adjacent differences
	{
		while(sum[from] < 2) from--;
		to = lastIndex+1;
	}
	// find the smallest index to right of from that is at least a difference of 2
	//if (sum[from] - sum[to] < 2)
	//{
	//	for (int k = to; k < lastIndex; k++) 
	//		if (sum[k] < sum[from] - 1) to = k;
	//}
		
	sum[from]--;
	if (to > lastIndex+1) printf("ERROR\n");
	if (sum[to] == 0) { lastIndex++; listSize++; }
	sum[to]++;
	printf("from = %d  to = %d    listSize = %d  lastIndex = %d\n", 
		from, to, listSize, lastIndex);
	return true;
}


int main()
{
	int count = 0;
	memset(sum, 0, sizeof(int) * (TOTAL+1));
	sum[0] = TOTAL;
	listSize = 1;
	lastIndex = 0;
	while(next())
	{
		count++;
		printf("%3d  %d", count, sum[0]);
		for (int k = 1; sum[k]>0; k++) printf(",%d", sum[k]);
		printf("\n");
	}
	printf("Number of sums is %d\n", count);
}
