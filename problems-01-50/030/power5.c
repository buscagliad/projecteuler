#include <stdio.h>

#define P5(n) n*n*n*n*n

int main()
{
	long sump5 = -1;	// this allows ignoring trivial case of 1
	long ones, tens, hunds, thous, tenth, ht;
	for (ht = 0; ht < 10; ht++)
	{
		for (tenth = 0; tenth < 10; tenth++)
		{
			for (thous = 0; thous < 10; thous++)
			{
				for (hunds = 0; hunds < 10; hunds++)
				{
					for (tens = 0; tens < 10; tens++)
					{
						for (ones = 0; ones < 10; ones++)
						{
							long num = 100000 * ht + 10000 * tenth + 1000 * thous + 100 * hunds + 10 * tens + ones;
							long p5 = P5(ht) + P5(tenth) + P5(thous) + P5(hunds) + P5(tens) + P5(ones);
							if (num == p5)
							{
								sump5 += num;
								printf("num: %ld   %ld %ld %ld %ld %ld %ld\n", num, ht, tenth, thous, hunds, tens, ones);
							}
						}
					}
				}
			}
		}
	}
	printf("Sum of all numbers: %ld\n", sump5);
}
