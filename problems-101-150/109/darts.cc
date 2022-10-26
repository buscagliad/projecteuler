#include <cstdio>
#include <cstring>

#define TD_SIZE 172
int	totalOuts[TD_SIZE];

struct dart {
	int	 val;
	char vn[4];
};

#define SINGLE 1
#define DOUBLE 2
#define TRIPLE 3

#define MAX_DARTS 22
dart	sngl[MAX_DARTS];
dart    dbl[MAX_DARTS];
dart    trpl[MAX_DARTS];

int stats()
{
	int	ts = 0;
	int hund = 0;
	for (int i = 0; i < TD_SIZE; i++)
	{
		if (totalOuts[i] == 0) continue;
		if (i < 100) hund += totalOuts[i];
		ts += totalOuts[i];
		printf("Out Value: %d    Number: %d\n", i, totalOuts[i]);
	}
	printf("Total number of outs: %d\n", ts);
	printf("Total number of outs < 100: %d\n", hund);
	return 0;
}
		

void init()
{
	for (int i = 0; i < TD_SIZE; i++) totalOuts[i] = 0;
	for (int i = 0; i <= 20; i++)
	{
		sngl[i].val = i;
		sprintf(sngl[i].vn, "S%d", i);
		dbl[i].val = 2*i;
		sprintf(dbl[i].vn, "D%d", 2*i);
		trpl[i].val = 3*i;
		sprintf(trpl[i].vn, "T%d", 3*i);
	}

	sngl[21].val = 25;
	strcpy(sngl[21].vn, "B25");
	dbl[21].val = 50;
	strcpy(dbl[21].vn, "B50");
	trpl[21].val = 0;
}

void	oneDart()
{
	for (int i = 1; i <= 21; i++)
	{
		int dart1 = dbl[i].val;
		if (dart1 == 0) continue;
		totalOuts[dart1]++;
		if (dart1 == 6) printf("D1: %d    Total: %d\n", dart1, totalOuts[dart1]);
	}
}

void    twoDarts(int firstDart)
{
	int dart1 = 0;
	for (int i = 1; i <= 21; i++)
	{
		if (firstDart == SINGLE) dart1 = sngl[i].val;
		else if (firstDart == DOUBLE) dart1 = dbl[i].val;
		else if (firstDart == TRIPLE) dart1 = trpl[i].val;
		if (dart1 == 0) continue;
		for (int j = 1; j <= 21; j++)
		{
			int dart2 = dbl[j].val;
			int ix = dart1 + dart2;
			if (dart2 == 0) continue;
			totalOuts[ix]++;
			if (ix == 6) printf("D1: %d  D2: %d Out value: %d   Total: %d\n", dart1, dart2, ix, totalOuts[ix]);
		}
	}
}
			
	
void    threeDarts(int firstDart, int secondDart)
{
	int dart1 = 0;
	int dart2 = 0;
	for (int i = 1; i <= 21; i++)
	{
		if (firstDart == SINGLE) dart1 = sngl[i].val;
		else if (firstDart == DOUBLE) dart1 = dbl[i].val;
		else if (firstDart == TRIPLE) dart1 = trpl[i].val;
		if (dart1 == 0) continue;
		for (int k = 1; k <= 21; k++)
		{
			if (secondDart == SINGLE) dart2 = sngl[k].val;
			else if (secondDart == DOUBLE) dart2 = dbl[k].val;
			else if (secondDart == TRIPLE) { if (k == 21) continue; dart2 = trpl[k].val; }
			if (dart2 == 0) continue;
			if ( (firstDart == secondDart) && (k > i) ) continue;
			for (int j = 1; j <= 21; j++)
			{
				int dart3 = dbl[j].val;
				int ix = dart1 + dart2 + dart3;
				if (dart3 == 0) continue;
				totalOuts[ix]++;
				if (ix == 6) printf("D1: %d  D2: %d  D3: %d Out value: %d   Total: %d\n", dart1, dart2, dart3, ix, totalOuts[ix]);
			}
		}
	}
}

int	main()
{
	init();
	if (1) {
	oneDart();
	twoDarts(SINGLE);
	twoDarts(DOUBLE);
	twoDarts(TRIPLE);
	threeDarts(SINGLE, SINGLE);
	threeDarts(SINGLE, DOUBLE);
	threeDarts(SINGLE, TRIPLE);
	threeDarts(DOUBLE, DOUBLE);
	threeDarts(DOUBLE, TRIPLE);
	threeDarts(TRIPLE, TRIPLE);
	}
	
	stats();
}
