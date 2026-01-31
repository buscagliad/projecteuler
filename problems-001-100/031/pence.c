
#include <stdio.h>
#define GOAL 200
#define COIN1 	1
#define COIN2 	2
#define COIN3 	5
#define COIN4	10
#define COIN5	20
#define COIN6	50
#define COIN7	100
#define COIN8	200

#define LOOP(n, v)	for (long n = 0; n <= GOAL/v; n ++)

#define PCOIN(c, cn)	printf("%3ld(%dp) ", c, cn)

#define DEBUG 0
int main()
{
	long count = 0;
	LOOP(c1, COIN1)
	LOOP(c2, COIN2)
	LOOP(c3, COIN3)
	LOOP(c4, COIN4)
	LOOP(c5, COIN5)
	LOOP(c6, COIN6)
	LOOP(c7, COIN7)
	LOOP(c8, COIN8)
	{
		long v = c1 * COIN1 + c2 * COIN2 + c3 * COIN3 + c4 * COIN4 + 
		         c5 * COIN5 + c6 * COIN6 + c7 * COIN7 + c8 * COIN8;
		if (v == GOAL)
		{
			count ++;
			if (DEBUG)
			{
				PCOIN(c1, COIN1);
				PCOIN(c2, COIN2);
				PCOIN(c3, COIN3);
				PCOIN(c4, COIN4);
				PCOIN(c5, COIN5);
				PCOIN(c6, COIN6);
				PCOIN(c7, COIN7);
				PCOIN(c8, COIN8);
				printf("  Total is %ld\n", v);
			}
		}
		
	}
	printf("Total number of ways to make %dp is %ld\n", GOAL, count);
}
