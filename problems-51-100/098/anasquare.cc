#ifdef PROBLEM_DESCRIPTION

Anagramic squares


  [Show HTML problem content]  
Problem 98

By replacing each of the letters in the word CARE with 1, 2, 9, and 6 respectively, we form a square number: 1296 = 36^2. What is remarkable is that, by using the same digital substitutions, the anagram, RACE, also forms a square number: 9216 = 96^2. We shall call CARE (and RACE) a square anagram word pair and specify further that leading zeroes are not permitted, neither may a different letter have the same digital value as another letter.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, find all the square anagram word pairs (a palindromic word is NOT considered to be an anagram of itself).

What is the largest square number formed by any member of such a pair?

NOTE: All anagrams formed must be contained in the given text file.

#endif

#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>

#include "base10.h"
#include "factor.h"

using namespace std;

vector<string> words;


int init(const char *fname)
{
	FILE *f = fopen(fname, "r");
	char	inword[100];
	char	*inw = inword;
	if (!f) return 0;
	while (!feof(f))
	{
		*inw = fgetc(f);
		//printf("c: %c\n", *inw);
		if (*inw == '"')
		{
			if (inw != inword) 
			{
				*inw = 0;
				inw = inword;
				words.push_back(inword);
				//printf("Adding: %s\n", inword);
				*inw = 0;
			}
		}
		if (isalpha(*inw)) inw++;
	}
	fflush(stdout);
	return words.size();
}

long anagram(string s1, string s2)
{
	if (s1.size() != s2.size()) return 0;
	return charmap(s1.c_str(), s2.c_str(), s1.size());
}


typedef struct _wdpair{
	string  s1;
	string  s2;
	long    map;
	vector<long> sql;
} wdpair;



bool canmap(const char *s, base10 b)
{
	return b.canorder(s);
}

bool compatible(const char *s, long n)
{
	return canmap(s, base10(n));
}

int main()
{

	long lw;
	init("p098_words.txt");
	vector<wdpair> wplist;
	for (size_t i = 0; i < words.size(); i++)
	{
		for (size_t j = i+1; j < words.size(); j++)
		{
			if ((lw = anagram(words[i], words[j])))
			{
				printf("%s <--> %s  [%ld]\n", words[i].c_str(), words[j].c_str(), lw);
				wdpair  wp = {words[i], words[j], lw};
				wplist.push_back(wp);
			}

		}
	}
	for (int len = 9; len >= 1; len--)
	{
		vector<int> pn;
		for (size_t i = 0; i < wplist.size(); i++)
		{
			if ((int)wplist[i].s1.size() == len)
			{
				printf(">>> %s <--> %s  [%ld]\n", wplist[i].s1.c_str(), wplist[i].s2.c_str(), wplist[i].map);
				long maxn = xpower(10, len);
				long minn = xpower(10, len - 1);
				long sqrtn = sqrt(maxn);
				long sq = sqrtn * sqrtn;
				while (sq > minn)
				{
					if ( (compatible(wplist[i].s1.c_str(), sq) ) && (compatible(wplist[i].s2.c_str(), sq) ) )
					{
						wplist[i].sql.push_back(sq);
						printf("%ld is compatible with %s\n", sq, wplist[i].s1.c_str());
					}
					sqrtn--;
					sq = sqrtn * sqrtn;
				}
				if (wplist[i].sql.size() == 0) continue;

				for (size_t k = 0; k < wplist[i].sql.size() - 1; k++)
				{
					base10 b1(wplist[i].sql[k]);
					for (size_t j = 0; j < wplist[i].sql.size(); j++)
					{
						if (j == k) continue;
						base10 b2(wplist[i].sql[j]);
						long mb1 = b1.map(b2);
						printf("(len = %d)  wplist[%lu].sql[%lu] = %ld  wplist[%lu].sql[%lu] = %ld"
							"     strmap: %ld   bmap: %ld\n",
							len, i, k, wplist[i].sql[k], i, j, wplist[i].sql[j], wplist[i].map, mb1);
						if (mb1 == wplist[i].map)
						{
							printf("HERE!!\n");
							return 1;
						}
					}
				}			
			}			
		}			
	}
		
}

				
	
