//
// 

#include <string>
#include <algorithm>

#include "fract.h"
#include "sequence.h"

string	bag;	// Need to add red each time and compute until bag.size() == 15;

vector<fract> blue;
vector<fract> red;

void init(int n, int bs)
{
	bag = "";
	for (int k = 1; k <= bs; k++)
		bag += 'b';
	for (int k = 2; k <= n+1; k++)
	{
		fract	b(1, k);
		fract   r(k - 1, k);
		blue.push_back(b);
		red.push_back(r);
	}
	printf("Bag: %s\n", bag.c_str());
}

fract	get(string &br)
{
	fract rv(1, 1);
	for (size_t i = 0; i < br.size(); i++)
	{
		if (br[i] == 'b') rv *= blue[i];
		else if (br[i] == 'r') rv*= red[i];
		else {printf ("ERROR - bad char: %c\n", br[i]); exit(1); }
	}
	//printf("g: "); rv.out(); printf("  br: %s\n", br.c_str());

	return rv;
}

fract    addred(string &br, fract &cf)
{
	br += 'r';
	std::sort(br.begin(), br.end());
	do
	{
		fract g = get(br);
		if (br[br.size()-1] == 'r') continue;
		printf("g: "); g.out(); printf("  br: %s  ", br.c_str()); cf.out(); printf("\n");
		cf += g;
	}
	while (std::next_permutation(br.begin(), br.end()));
	return cf;
}

long   getprod(string &br)
{
	long p = 1;
	for (size_t i = 0; i < br.size(); i++)
		if (br[i] == 'r') p *= (i + 1);
	return p;
}

long    summer(string &br)
{
	br += 'r';
	long cf = 0;
	std::sort(br.begin(), br.end());
	do
	{
		if (br[br.size()-1] == 'r') continue;
		long g = getprod(br);
		cf += g;
	}
	while (std::next_permutation(br.begin(), br.end()));
	return cf;
}


void

 playgame(int gameSize)
{
	//const int gameSize = 4;
	//int gs = gameSize;
	const int winReq = gameSize / 2 + 1;
	int wr = winReq;
	init(gameSize, winReq);
	long win = 1;
	get(bag);
	printf("start: %ld  br: %s\n", win, bag.c_str());
	for (int i = 1; i <= gameSize - winReq; i++) 
	{
		long s = summer(bag);
		printf("Bag: %s  S: %ld\n", bag.c_str(), s);
		win += ++wr * win +  s;
	}
	printf("Odds of winning are : %ld / %ld\n", win, fact(gameSize+1));
	printf("Required pot is %ld\n", fact(gameSize+1) / win);
}

int main()
{
	playgame(4);
	playgame(5);
	playgame(6);
	playgame(15);
}
