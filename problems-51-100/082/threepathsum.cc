#ifdef PROBLEM_DESCRIPTION


The minimal path sum in the 5 by 5 matrix below, by starting in any cell in the left column and finishing in any cell in the right column, and only moving up, down, and right, is indicated in red and bold; the sum is equal to 994.
Find the minimal path sum from the left column to the right column in matrix.txt (right click and "Save Link/Target As..."), a 31K text file containing an 80 by 80 matrix.
#endif

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <ctype.h>
#include <cstring>
#include <string>

using namespace std;
#define MAXX 1000
#define MAXY 1000
#define MAX_RV 88888

int	s_grid[MAXX][MAXY];
int	g_grid[MAXX][MAXY];

int  g_nx = 0;
int  g_ny = 0;

int xpts = 0;
int ypts = 0;
#define NOT_SET -1

#define MAXLINE 1000
///////////////////////////////////////////////////////////////////
// DEBUG outgrid outputs the grid to stdout
///////////////////////////////////////////////////////////////////
void outgrid(int g[MAXX][MAXY], int nx, int ny)
{
	printf("GRID  X: %d  Y: %d\n", nx, ny);
	for (int y = 0; y < ny; y++)
	{
		for (int x = 0; x < nx; x++)
		{
			printf("%6d", g[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}



bool mindval(int g[MAXX][MAXY], int s[MAXX][MAXY], int nx, int ny, int x, int y)
{
	bool	rv = false;
	int	sumv = 0;
	if (s[x][y] != NOT_SET)
	{
		#ifdef ALLOW_LEFT
        if (x - 1 >= 0) // LEFT
        {
            sumv = s[x][y] + g[x-1][y];
            if ( (sumv < s[x-1][y]) || (s[x-1][y] == NOT_SET) )
            {
                s[x-1][y] = sumv;
                rv = true;
            }
        }
        #endif
        if (x + 1 < nx) // RIGHT
        {
            sumv = s[x][y] + g[x+1][y];
            if ( (sumv < s[x+1][y]) || (s[x+1][y] == NOT_SET) )
            {
                s[x+1][y] = sumv;
                rv = true;
            }
        }
        if (y - 1 >= 0) // ABOVE
        {
            sumv = s[x][y] + g[x][y-1];
            if ( (sumv < s[x][y-1]) || (s[x][y-1] == NOT_SET) )
            {
                s[x][y-1] = sumv;
                rv = true;
            }
        }
        if (y + 1 < ny) // BELOW
        {
            sumv = s[x][y] + g[x][y+1];
            if ( (sumv < s[x][y+1]) || (s[x][y+1] == NOT_SET) )
            {
                s[x][y+1] = sumv;
                rv = true;
            }
        }
	}
	return rv;
}

int route(int g[MAXX][MAXY], int s[MAXX][MAXY], int nx, int ny, int ystart)
{
	s[0][ystart] = g[0][ystart];
	bool done = false;
	while (!done)
	{
		done = true;
		for (int x = 0; x < nx; x++)
		{
			for (int y = 0; y < ny; y++)
			{
				if (mindval(g, s, nx, ny, x, y))
				    done = false;
			}
			//outgrid(g, nx, ny);
		}
	}
	int minv = s[nx-1][0];
	for (int ya = 0; ya < ny; ya++)
	    if (s[nx-1][ya] < minv) minv = s[nx-1][ya];
	return minv;
}

void zerodata()  
{
	for(int i = 0; i < MAXX; i++) 
	    for(int j = 0; j < MAXY; j++)
	    {
			g_grid[i][j] = 0;
			s_grid[i][j] = NOT_SET;	// set the sum-path to not be set
		}
	xpts = 0;
	ypts = 0;
	
}

void parseline(char *c)
{
	int   x = 0;
	int   y = ypts;
	while (*c  && *c != '\n')
	{
		sscanf(c, "%d", &(g_grid[x++][y]));
		c = strchr(c, ',');
		if (c == NULL) break;
		c++;
	}
	ypts++;
	xpts = x;
}

void init(const char *v)
{
	FILE *f = fopen(v, "r");

	printf("Input file: %s\n", v);
	char c[MAXLINE];
	fgets(c, MAXLINE, f);
	zerodata();
	while (!feof(f))
	{
		parseline(c);
		fgets(c, MAXLINE, f);
	}
	
	g_nx = xpts;
	g_ny = ypts;
	//outgrid(g_grid, g_nx, g_ny);
	fclose(f);
}

void solve(const char *fn, int trisk)
{
	init(fn);
	int my_risk;
	int min_risk;
	for (int sy = 0; sy < g_ny; sy++)
	{
		
		if (sy == 0) min_risk = route(g_grid, s_grid, g_nx, g_ny, sy);
		else {
			my_risk = route(g_grid, s_grid, g_nx, g_ny, sy);
			if (my_risk < min_risk) min_risk = my_risk;
		}
	}
	//outgrid(s_grid, g_nx, g_ny);
	printf("Risk level: %d\n", min_risk);
	if (trisk > 0)
	{
		if (my_risk != trisk)
			printf("ERROR - risk answer does not agree with truth: %d!\n", trisk);
		else
			printf("Successfully esimated risk level!!\n");
	}

}

int main(int argc, char **argv)
{
	// From day 15 Advent of Code 2021 (Chiton)
	//outgrid(g_grid, g_nx, g_ny);
	printf("Example 5x5\n");
	solve("sample.txt", 994);
	//init("p082_matrix.txt");
	//outgrid(g_grid, g_nx, g_ny);
	printf("Problem 82 matrix\n");
	solve("p082_matrix.txt", 260324);
	return 0;
}
