#ifdef PROBLEM_DESCRIPTION



#endif

#include <iostream>
#include <string>
#include <cstdio>
#include "vlong.h"

using namespace std;

int	ring[5];
int exnode[5];
int lines[5];
char res[200];

void outThreeRing()
{
	int en = 0;
	for (int i = 1; i < 3; i++) if (exnode[i] < exnode[en]) en = i;
	printf("Total: %d-%d-%d    %d,%d,%d;%d,%d,%d;%d,%d,%d;\n",
		lines[(en + 0) % 3], lines[(en + 1) % 3],lines[(en + 2) % 3],
		exnode[(en + 0) % 3], ring[(en + 0) % 3], ring[(en + 1) % 3],
		exnode[(en + 1) % 3], ring[(en + 1) % 3], ring[(en + 2) % 3],
		exnode[(en + 2) % 3], ring[(en + 2) % 3], ring[(en + 0) % 3]);
	sprintf(res, "%d%d%d%d%d%d%d%d%d", 
		exnode[(en + 0) % 3], ring[(en + 0) % 3], ring[(en + 1) % 3],
		exnode[(en + 1) % 3], ring[(en + 1) % 3], ring[(en + 2) % 3],
		exnode[(en + 2) % 3], ring[(en + 2) % 3], ring[(en + 0) % 3]);
	printf("%s\n", res);
}

bool check()
{
	lines[0] = exnode[0] + ring[0] + ring[1];
	lines[1] = exnode[1] + ring[1] + ring[2];
	lines[2] = exnode[2] + ring[2] + ring[0];
	if (lines[0] != lines[1]) return false;
	if (lines[1] != lines[2]) return false;
	return true;
}

void	setRing(int a, int b, int c)
{
	ring[0] = a;
	ring[1] = b;
	ring[2] = c;
}

void    setExNode(int a, int b, int c)
{
	exnode[0] = a;
	exnode[1] = b;
	exnode[2] = c;
}


  
std::string	run(int r0, int r1, int r2,
			int v0, int v1, int v2)
{
	setRing(r0, r1, r2);
	vlong_t r{r0, r1, r2};
	vlong_t v{v0, v1, v2};
	std::sort(r.begin(), r.end());
	do
	{
		setRing(r[0], r[1], r[2]);

		std::sort(v.begin(), v.end());
		do
		{
			setExNode(v[0], v[1], v[2]);
			if (check()) outThreeRing();
		}
		while( std::next_permutation(v.begin(), v.end()) );
	}
	while( std::next_permutation(r.begin(), r.end()) );
	return res;
}



int main()
{
	string s = run(1, 2, 3, 4, 5, 6);
	string b = run(1, 3, 5, 2, 4, 6);
	if (b > s) s == b;
	b = run(2, 4, 6, 1, 3, 5);
	if (b > s) s == b;
	b = run(4, 5, 6, 1, 2, 3);
	if (b > s) s == b;
	cout << "Ring string: " << s << endl;
}
