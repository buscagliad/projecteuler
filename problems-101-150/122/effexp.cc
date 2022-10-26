//
// create n^k from predecessors.
//
// Note:  m(1) = 0 // no multiplication required
//        m(2) = 1 // only 1 way
//        m(3) = 2 // can only get to three thru 2
//        m(4) = 2 // n^2, then n^2 * n^2
//        m(5) = 3 // n^2, then n^3, then n^2 * n^3
//        m(6) = 3 // n^2 n^3 then n^3 * n^3
//        m(7) = 4
//
//     NOTE:  m(a*b) = m(a) + m(b)
//     Proof:
//     

#include <vector>
#include <cstdio>

using namespace std;

#define MAXM 201

int  m[MAXM];

void init()
{
	for (int i = 0; i < MAXM; i++) m[i] = 0;
	m[1] = 0;
	m[2] = 1;
	m[3] = 2;
}

bool done()
{
	for (int i = 2; i < MAXM; i++)
	    if (m[i] <= 0) return false;
	return true;
}

int sum()
{
	int s = 0;
	for (int i = 1; i < MAXM; i++)
	{
		s += m[i];
		printf("m[%3d] = %3d\n", i, m[i]);
	}
	return s;
}

void out(vector<int> &p)
{
	int li = p.size() - 1;
	printf("P Vector: {%d", p[0]);
	for (int i = 1; i <= li; i++)
	{
		printf(",%d", p[i]);
	}
	printf("}\n");
}

bool update(vector<int> &p)
{
	int li = p.size() - 1;
	bool rv = false;
	int v;
	//out(p);
	for (int i = 0; i <= li; i++)
	{
		v = p[i] + p[li];
		if (v > MAXM - 1) continue;
		if (m[v] == 0) 
		{
			printf("Initial m[%d] = %lu\n", v, p.size());
			m[v] =  p.size();
			if (v == 15) out(p);
			rv = true;
		}
		else if (m[v] > (int) p.size()) 
		{
			printf("Update m[%d] = %lu\n", v, p.size());
			m[v] =  p.size();
			if (v == 15) out(p);
			rv = true;
		}
	}
	return rv;
}

void	npower(vector<int> p)
{
	if ( p.size() > 12)
	{
		//printf("XXXXXXXXX\n");
		return;
	}
	int li = p.size() - 1;
	update(p);
	for (int i = li; i >= 0 ; i--)
	{
		vector<int> pa = p;
		int a = p[i] + p[li];
		//if (a < MAXM - 1) printf("a: %d  m[a]: %d  p.size(): %lu\n", a, m[a], p.size());
		if (( a < MAXM - 1))// &&  (m[a] == 0)  )
		{
			pa.push_back(a);
			npower(pa);
		}
	}
}


int main()
{
	init();
	vector<int> p= {1, 2};
	npower(p);
	printf("Done is: %d\n", done());
	printf("Total sum is: %d\n", sum());
}
