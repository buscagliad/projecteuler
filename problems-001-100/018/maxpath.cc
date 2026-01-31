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
int save_first = 0;
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
			printf("%2d", g[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}

void outtriangle(int g[MAXX][MAXY], int nx, int ny)
{
	printf("TRIANGLE  X: %d  Y: %d\n", nx, ny);
	for (int y = 0; y < ny; y++)
	{
		for (int x = 0; x <= y; x++)
		{
			printf("%3d", g[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}

//
// x, y are the positions on the triangle - only BELOW (0, +1) and BELOW RIGHT (+1, +1)
//                                           movements are allowed
//  s is the matrix of already computed path values - if set, we use it
//    if not, we compute it and use it later
bool maxdval(int g[MAXX][MAXY], int s[MAXX][MAXY], int nx, int ny, int x, int y)
{
	bool	rv = false;
	int	sumv = 0;
	if (s[x][y] != NOT_SET)
	{
        if (y + 1 < ny) // BELOW
        {
            sumv = s[x][y] + g[x][y+1];
            if ( (sumv > s[x][y+1]) || (s[x][y+1] == NOT_SET) )
            {
                s[x][y+1] = sumv;
                rv = true;
            }
        }
        if ( (y + 1 < ny) && (x + 1 < nx) )// BELOW - RIGHT
        {
            sumv = s[x][y] + g[x+1][y+1];
            if ( (sumv > s[x+1][y+1]) || (s[x+1][y+1] == NOT_SET) )
            {
                s[x+1][y+1] = sumv;
                rv = true;
            }
        }
	}
	return rv;
}



int route(int g[MAXX][MAXY], int s[MAXX][MAXY], int nx, int ny)
{
	save_first = g[0][0];
	//g[0][0] = 0;
	s[0][0] = g[0][0];
	bool done = false;
	while (!done)
	{
		done = true;
		for (int x = 0; x < nx; x++)
		{
			for (int y = 0; y < ny; y++)
			{
				if (maxdval(g, s, nx, ny, x, y))
				    done = false;
			}
			//outgrid(g, nx, ny);
		}
	}
	int m = s[0][ny - 1];
	for (int k = 1; k < nx; k++)
	{
		if (m < s[k][ny-1]) m = s[k][ny-1];
	}
	return m;
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
	while (c && *c != '\n')
	{
		sscanf(c, "%d", &(g_grid[x++][y]));
		c = strchr(c, ' ');
		if (c) c++;
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
		//printf("%s\n", c);
		parseline(c);
		fgets(c, MAXLINE, f);
	}
	
	g_nx = xpts;
	g_ny = ypts;
	//outgrid(g_grid, g_nx, g_ny);
	fclose(f);
}

void solve(int trisk)
{
	int my_risk = 0;
	my_risk = route(g_grid, s_grid, g_nx, g_ny);
	//outgrid(s_grid, g_nx, g_ny);

	printf("Largest path sum: %d\n", my_risk);
	if (trisk > 0)
	{
		if (my_risk != trisk)
			printf("ERROR - path sum answer does not agree with truth: %d!\n", trisk);
		else
			printf("Successfully esimated path sum!!\n");
	}

}



int main(int argc, char **argv)
{
	init("extri.txt");
	outtriangle(g_grid, g_nx, g_ny);
	printf("Example for small triangle\n");
	solve(23);
	init("triangle.txt");
	outtriangle(g_grid, g_nx, g_ny);
	printf("Example for large triange\n");
	solve(1074);
	return 0;
}
