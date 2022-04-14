#include <stdio.h>

#define GRIDX 20
#define GRIDY 20

long grid[GRIDX][GRIDY];
bool readgrid(const char *name)
{
	FILE *f = fopen(name, "r");
	if (!f) return false;
	for (int j = 0; j < GRIDY; j++)
	{
		for (int i = 0; i < GRIDX; i++)
		{
			fscanf(f, "%ld", &(grid[i][j]));
		}
	}
	return true;
}

void printgrid()
{
	for (int j = 0; j < GRIDY; j++)
	{
		for (int i = 0; i < GRIDX; i++)
		{
			printf("%2ld ", grid[i][j]);
		}
		printf("\n");
	}
}

long getgrid(int i, int j)
{
	if (i < 0) return 0;
	if (j < 0) return 0;
	if (i >= GRIDX) return 0;
	if (j >= GRIDY) return 0;
	return grid[i][j];
}

long maxprod(int xdelta, int ydelta, int len)
{
	long max = 0;
	long mi, mj;
		
	for (int j = 0; j < GRIDY; j++)
	{
		for (int i = 0; i < GRIDX; i++)
		{
			long pr = 1;
			for (int k = 0; k < len; k++)
			{
				pr *= getgrid(j + k * ydelta, i + k * xdelta);
			}
			if (pr > max) {
				max = pr;
				mi = i;
				mj = j;
			}
		}
	}
	printf("MAX:: xd: %d  yd: %d  mi: %ld mj: %ld  max: %ld\n", xdelta, ydelta, mi, mj, max);
	return max;
}

int main()
{
	readgrid("grid.txt");
	printgrid();
	printf("Horizontal: %ld\n", maxprod(1,0,4));
	printf("  Vertical: %ld\n", maxprod(0,1,4));
	printf("R Diagonal: %ld\n", maxprod(1,1,4));
	printf("L Diagonal: %ld\n", maxprod(-1,1,4));
}
