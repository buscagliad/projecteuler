#ifdef PROBLEM_DESCRIPTION



#endif

#include <stdio.h>
#include "vlong.h"

int	ring[5];
int exnode[5];
int lines[5];
char res[200];

void outFiveRing()
{
	int en = 0;
	for (int i = 1; i < 5; i++) if (exnode[i] < exnode[en]) en = i;
	printf("Total: %d-%d-%d-%d-%d    %d,%d,%d;%d,%d,%d;%d,%d,%d;"
						 "%d,%d,%d;%d,%d,%d\n", 
		lines[(en + 0) % 5], lines[(en + 1) % 5],lines[(en + 2) % 5],lines[(en + 3) % 5],lines[(en + 4) % 5],
		exnode[(en + 0) % 5], ring[(en + 0) % 5], ring[(en + 1) % 5],
		exnode[(en + 1) % 5], ring[(en + 1) % 5], ring[(en + 2) % 5],
		exnode[(en + 2) % 5], ring[(en + 2) % 5], ring[(en + 3) % 5],
		exnode[(en + 3) % 5], ring[(en + 3) % 5], ring[(en + 4) % 5],
		exnode[(en + 4) % 5], ring[(en + 4) % 5], ring[(en + 0) % 5]);
	sprintf(res, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", 
		exnode[(en + 0) % 5], ring[(en + 0) % 5], ring[(en + 1) % 5],
		exnode[(en + 1) % 5], ring[(en + 1) % 5], ring[(en + 2) % 5],
		exnode[(en + 2) % 5], ring[(en + 2) % 5], ring[(en + 3) % 5],
		exnode[(en + 3) % 5], ring[(en + 3) % 5], ring[(en + 4) % 5],
		exnode[(en + 4) % 5], ring[(en + 4) % 5], ring[(en + 0) % 5]);
	printf("%s\n", res);
}

bool check()
{
	lines[0] = exnode[0] + ring[0] + ring[1];
	lines[1] = exnode[1] + ring[1] + ring[2];
	lines[2] = exnode[2] + ring[2] + ring[3];
	lines[3] = exnode[3] + ring[3] + ring[4];
	lines[4] = exnode[4] + ring[4] + ring[0];
	if (lines[0] != lines[1]) return false;
	if (lines[1] != lines[2]) return false;
	if (lines[2] != lines[3]) return false;
	if (lines[3] != lines[4]) return false;
	return true;
}

void	setRing(int a, int b, int c, int d, int e)
{
	ring[0] = a;
	ring[1] = b;
	ring[2] = c;
	ring[3] = d;
	ring[4] = e;
}

void    setExNode(int a, int b, int c, int d, int e)
{
	exnode[0] = a;
	exnode[1] = b;
	exnode[2] = c;
	exnode[3] = d;
	exnode[4] = e;
}


  
void	run()
{
	setRing(1,2,3,4,5);
	vlong_t r{1, 2, 3, 4, 5};
	vlong_t v{6, 7, 8, 9, 10};
	std::sort(r.begin(), r.end());
	do
	{
		setRing(r[0], r[1], r[2], r[3], r[4]);

		std::sort(v.begin(), v.end());
		do
		{
			setExNode(v[0], v[1], v[2], v[3], v[4]);
			if (check()) outFiveRing();
		}
		while( std::next_permutation(v.begin(), v.end()) );
	}
	while( std::next_permutation(r.begin(), r.end()) );
}

void	run2()
{
	setRing(1,3,5,7,9);
	vlong_t r{1,3,5,7,9};
	vlong_t v{2,4,6,8,10};
	std::sort(r.begin(), r.end());
	do
	{
		setRing(r[0], r[1], r[2], r[3], r[4]);

		std::sort(v.begin(), v.end());
		do
		{
			setExNode(v[0], v[1], v[2], v[3], v[4]);
			if (check()) outFiveRing();
		}
		while( std::next_permutation(v.begin(), v.end()) );
	}
	while( std::next_permutation(r.begin(), r.end()) );
}


int main()
{
	run();
	//run2();
}
