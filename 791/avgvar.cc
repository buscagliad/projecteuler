

#include <cinttypes>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int64_t	get_sum(int64_t d, bool output = false)
{
	int64_t a, b, c;
	int64_t sa, sb, sc;
	int64_t sa2, sb2, sc2;
	int64_t s, s2;
	int64_t	d2 = d * d;
	int64_t ts = 0;
	bool first = true;
	double dd = d;
	int cnt = 0;
	int64_t startd = (int64_t)(dd - 2 * sqrt(dd));
	if (startd < 1) startd = 1;
	
	for (a = startd; a <= d; a++)
	{
		sa = d + a;
		sa2 = d2 + a*a;
		for (b = a; b <= d; b++)
		{
			sb = sa + b;
			sb2 = sa2 + b * b;
			for (c = b; c <= d; c++)
			{
				s = sb + c;
				s2 = sb2 + c * c;
				if (2 * s == (4 * s2 - s * s) )
				{
					ts += s; cnt++;
					if (output) printf("(%ld, %ld, %ld, %ld)   s = %ld  total = %ld\n", a, b, c, d, s, ts);
					if (output) { first = false;
						double sqd = 2 * sqrt((double)(d));
						printf("a = %ld, d = %ld, d-a = %ld, 2*sqrt(d)= %.1f  %s\n", a, d, d-a, sqd, 
							((d-a)<sqd)?"GOOD":"ERROR");
					}
				}
			}
		}
	}
	printf("Count: %d   ts/cnt: %.3f\n", cnt, (double)ts / (double)cnt);
	return ts;
}

void run_sum(int64_t N)
{
	int64_t ts = 0, ots = 0, dts = 0;
	for (int64_t d = 1; d <= N; d++)
	{
		ts += get_sum(d);
		if (1)
		{
			dts = ts - ots;
			printf("d = %ld, total = %ld   delta=%ld\n", d, ts, dts);
			ots = ts;
		}
	}
}

void run_last(int64_t d)
{
	int64_t ts = 0;
	ts = get_sum(d, true);
	printf("Run single d value = %ld, total = %ld \n", d, ts);
}

int	main(int argc, char **argv)
{
	int64_t  N = atoll(argv[1]);
	run_last(N);
	// run_sum(N);
	return 0;
}
				
