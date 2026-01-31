#ifdef PROBLEM_DESCRIPTION



Three distinct points are plotted at random on a Cartesian plane, for which -1000 ≤ x, y ≤ 1000, such that a triangle is formed.

Consider the following two triangles:

A(-340,495), B(-153,-910), C(835,-947)

X(-175,41), Y(-421,-714), Z(574,-645)

It can be verified that triangle ABC contains the origin, whereas triangle XYZ does not.

Using triangles.txt (right click and 'Save Link/Target As...'), a 27K text file containing the co-ordinates of one thousand "random" triangles, find the number of triangles for which the interior contains the origin.

NOTE: The first two examples in the file represent the triangles in the example given above.


#endif

#include <cstdio>

typedef enum {
	LEFT,
	RIGHT,
	CONTAINS} lrc_e;

lrc_e lrc(int ax, int ay, int bx, int by, int cx, int cy)
{
	int v ((bx - ax)*(cy - ay) - (by - ay)*(cx - ax));
	if (v > 0) return LEFT;
	if (v == 0) return CONTAINS;
	return RIGHT;
}


bool containsOrigin(int ax, int ay, int bx, int by, int cx, int cy)
{
	lrc_e	c1 = lrc(ax, ay, bx, by, 0, 0);
	lrc_e	c2 = lrc(bx, by, cx, cy, 0, 0);
	lrc_e	c3 = lrc(cx, cy, ax, ay, 0, 0);
	bool rv = false;
	
	if ( (c1 == c2) && (c2 == c3) ) rv = true;
	//else if ( (c1 == CONTAINS) || (c2 == CONTAINS) || (c3 == CONTAINS) )
//	{
//		rv = true;
//	}
	
	printf("The trainagle formed by the points (%d,%d), (%d,%d) and (%d,%d) %s the origin\n", ax, ay, bx, by, cx, cy, (rv ? "CONTAIN":
	"does NOT contain"));
	return rv;
}

int test(const char *fname)
{
	FILE *f = fopen(fname, "r");
	int ax, ay, bx, by, cx, cy;
	if (!f)
	{
		printf("Cannot open file %s\n", fname);
		return 0;
	}
	int inCount = 0;
	int outCount = 0;
	while (!feof(f))
	{
		fscanf(f, "%d,%d,%d,%d,%d,%d", &ax, &ay, &bx, &by, &cx, &cy);
		if (feof(f)) continue;
		if (containsOrigin(ax, ay, bx, by, cx, cy))
		    inCount++;
		else
		    outCount++;
	}
	printf("A total of %d triangles contain the origin out of %d\n",
		inCount, inCount + outCount);
	fclose(f);
	return 1;
}

	
int main()
{
	containsOrigin(-340, 495, -153, -910, 835,-947);
	containsOrigin(-175,  41, -421, -714, 574,-645);
	test("p102_triangles.txt");
}		
