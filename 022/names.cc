/*
 * 

Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over five-thousand first names, begin by sorting it into alphabetical order. Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?
*/

#include <string>
#include <list>
#include <stdio.h>

using namespace std;

list<string> names;

long score(string &s, long pos)
{
	long rv = 0;
	for (size_t i = 0; i < s.size(); i++)
	{
		rv += s[i] - 'A' + 1;
	}
	return rv * pos;
}

long eval()
{
	long total = 0;
	list<string>:: iterator it = names.begin();
	long pos = 1;
	while (it != names.end())
	{
		total += score(*it, pos);
		if (pos == 938) printf("Pos: %ld  Name: %s  Score: %ld\n", pos, (*it).c_str(), score(*it, pos));
		it++;
		pos++;
	}
	return total;
}
	

void init(const char *fname)
{
	FILE *f = fopen(fname, "r");
	if (!f) return;
	string ns;
	int		c;
	while (!feof(f))
	{
		c = fgetc(f);
		if (isalpha(c)) { ns += (char) c; continue; }
		else if (ns.size() == 0) {continue;}
		// we get here we have a good name
		names.push_back(ns);
		ns.clear();
	}
	fclose(f);
}

int main()
{
	init("p022_names.txt");
	names.sort();
	printf("Total name score: %ld\n", eval());
}
