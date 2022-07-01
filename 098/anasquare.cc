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
#include <algorithm>

#include "base10.h"

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

bool anagram(string s1, string s2)
{
	if (s1.size() != s2.size()) return false;
	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());
	if (s1 == s2) return true;
	return false;
}

typedef struct _sqpair {
	long	sq1;
	long	sq2;
} sqpair;

void scale(vector<int> &s, vector<sqpair> &sc)
{
	for (size_t i = 0; i < s.size() - 1; i++)
	{
		base10  s1(s[i]);
		for (size_t j = i+1; j < s.size(); j++)
		{
			base10 s2(s[j]);
			if (s1.sameDigits(s2))
			{
				sqpair sp = {s1.value(), s2.value()};
				sc.push_back(sp);
				printf("Found anagram square:  %ld  and  %ld\n",s1.value(), s2.value() );
			}
		}
	}
}

long transmap(long n1, long n2)
{
	base10 b1(n1);
	base10 b2(n2);
	return b1.map(b2);
}
	

bool similar(long n1, string s1, long n2, string s2)
{
	long tn = transmap(n1, n2);
	long ts = charmap(s1.c_str(), s2.c_str(), s1.size());
	printf("N1: %ld   N2: %ld   tn: %ld    s1: %s  s2: %s  ts: %ld\n",
		n1, n2, tn, s1.c_str(), s2.c_str(), ts);
	return (tn == ts);
}

void test(vector<sqpair> &sc)
{
	vector<int> sq;
	int min10 = 10;
	int max10 = 100;
	int curn = 4;
	int c2 = curn * curn;
	for (int numdigs = 2; numdigs <= 9; numdigs++)
	{
		sq.clear();
		while (c2 < max10)
		{
			if (c2 > max10) break;
			sq.push_back(c2);
			curn++;
			c2 = curn * curn;
			printf("curn: %d   c2: %d    numdigs: %d\n", curn, c2, numdigs);
		}
		scale(sq, sc);
		min10 *= 10;
		max10 *= 10;
	}
	fflush(stdout);
}

int main()
{
	const char *s1 = "ABCDEFGC";
	long n1 = 12345673;
	const char *s2 = "EFGCABCD";
	long n2 = 56731234;
	printf("%s %ld   %s %ld  -- %s\n", s1, n1, s2, n2, similar(n1, s1, n2, s2) ? "YES" : "NO");
	return 1;
	
	init("p098_words.txt");
	for (size_t i = 0; i < words.size(); i++)
	{
		for (size_t j = i+1; j < words.size(); j++)
		{
			if (anagram(words[i], words[j]))
			{
				printf("%s <--> %s\n", words[i].c_str(), words[j].c_str());
			}
		}
	}
	vector<sqpair> sq;
	test(sq);
}

				
	
