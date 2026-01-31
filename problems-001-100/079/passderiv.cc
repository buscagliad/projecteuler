#ifdef PROBLEM_DESCRIPTION

Passcode derivation

Problem 79

A common security method used for online banking is to ask the user for three random characters from a passcode. For example, if the passcode was 531278, they may ask for the 2nd, 3rd, and 5th characters; the expected reply would be: 317.

The text file, keylog.txt, contains fifty successful login attempts.

Given that the three characters are always asked for in order, analyse the file so as to determine the shortest possible secret passcode of unknown length.

    1 <     0     6     2    12     0     0     8    21     1     0  <    0
            0     1     2     3     4     5     6     7     8     9 

    1 <     0    15    10     2     0     0    10     0     9     4  <    0
            0     1     2     3     4     5     6     7     8     9 

    1 <    16     1     5     0     0     0     5     0     6    17  <    0
            0     1     2     3     4     5     6     7     8     9 

7 needs to be first digit as it does not appear ANYWHERE but dig1
0 needs to be the last digit as it does not appear ANYWHERE but dig3
4, 5 do not appear in security code
1, 2, 3, 6, 8, and 9 are interior digits
3 (1,6,8), 9 are likely orders


#endif

#include <string>
#include <cstring>
#include <iostream>

#include "factor.h"
#include "hist.hh"

hist dig1(0,9);
hist dig2(0,9);
hist dig3(0,9);

#define MAXLOGS 50

typedef struct keylog {
	char  c1, c2, c3;
	bool  used;
} keylog_t;

keylog_t klogs[MAXLOGS];
int klog_count = 0;

bool insert(char *code, char c1, char c2, char c3)
{
	if (strlen(code) == 0) {
		code[0] = c1; 
		code[1] = c2; 
		code[2] = c3; 
		code[3] = 0; 
		return true;
	}
	return false;
}

void init(const char *fname)
{
	FILE *f = fopen(fname, "r");
	
	while (!feof(f))
	{
		int c = fgetc(f);
		if ( (c < '0') || (c > '9') ) continue;
		dig1.add(c - '0');
		klogs[klog_count].c1 = c;
		c  = fgetc(f);
		dig2.add(c - '0');
		klogs[klog_count].c2 = c;
		c  = fgetc(f);
		dig3.add(c - '0');
		klogs[klog_count].c3 = c;
		fgetc(f);  // return <cr>
		klogs[klog_count++].used = false;
	}
}

bool valid(const char *s, keylog_t &k)
{
	const char *p = strchr(s, k.c1);
	if (!p) return false;
	p = strchr(p, k.c2);
	if (!p) return false;
	p = strchr(p, k.c3);
	if (!p) return false;
	return true;
}

bool valid_code(const char *s)
{
	for (int i = 0; i < klog_count; i++)
	{
		if (!valid(s, klogs[i]))
		{
			printf("Code %s NOT valid at %d : %c%c%c  %d\n", s, i,
				klogs[i].c1, klogs[i].c2, klogs[i].c3, klog_count);
			return false;
		}
	}
	printf("Code %s IS valid \n", s);
	return true;
}

bool trythis(std::string s, char add)	// checks if s + add is 'valid'
{
	char last = s.back();
	for (int i = 0; i < klog_count; i++)
	{
		if ( (klogs[i].c1 == last) && (klogs[i].c2 == add) )
		{
			printf("++ %s + %c match\n", s.c_str(), add);
			return true;
		}
		if ( (klogs[i].c2 == last) && (klogs[i].c3 == add) )
		{
			printf("== %s + %c match\n", s.c_str(), add);
			return true;
		}
	}
	printf("-- %s + %c NO match\n", s.c_str(), add);
	return false;
}


std::string	build_code(std::string s, char cadd)
{
	s += cadd;
	if (valid_code(s.c_str())) 
	{
		printf("Valid code: %s\n", s.c_str());
		exit(1);
	}
	for (char c = '0'; c <= '9'; c++)
	    if (trythis(s, c)) build_code(s, c);
	return "ERROR";
} 
	
	

int main()
{
	init("p079_keylog.txt");
	// first digit has to be histogram element dig1 with non-zero entry AND
	// zero entry in dig2 and dig3 -- if more than one - not sure what to do
	
	dig1.out();
	dig2.out();
	dig3.out();
	std::string s;
	s = build_code(s, '7');
	cout << "CODE: " << s << std::endl;
}
