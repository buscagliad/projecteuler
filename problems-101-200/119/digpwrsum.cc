//
//

#include <algorithm>
#include <vector>

#include <math.h>
#include "factor.h"
#include "base10.h"
//						   111111111122222222223
//                123456789012345678901234567890
#define	MAX_POWER 1000000000000000

typedef struct {
	int			n;
	int			pwr;
	long		n2pwr;
} pwr_t;

std::vector<pwr_t>	pt;

bool cmp(pwr_t &p1, pwr_t &p2)
{
	return (p1.n2pwr < p2.n2pwr);
}

void   check(pwr_t &p)
{
	base10 b(p.n2pwr);
	if (b.digsum() == p.n) pt.push_back(p);
}

long	comp(int n, int p)
{
	pwr_t px = {n, p, 0};
	px.n2pwr = xpower(n, p);
	check(px);
	return px.n2pwr;
}

size_t	add(int p)
{
	int	n = 2;
	while (comp(n, p) < MAX_POWER) n++;
	return pt.size();
}

int	main()
{
	int	max_power = round(log(MAX_POWER)/log(2));
	
	for (int p = 2; p < max_power; p++)
	    add(p);
	std::sort(pt.begin(), pt.end(), cmp);
	printf("Total number of elements: %ld\n", pt.size());
	for (vector<pwr_t>::iterator it = pt.begin(); it != pt.end(); it++ )
	    printf("n: %d    p: %d    P: %20ld\n", it->n, it->pwr, it->n2pwr);
}
