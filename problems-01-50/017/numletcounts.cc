
#ifdef USE_COMMENTS
If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.

If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?

NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing out numbers is in compliance with British usage.
#endif

#include <string>
#include <iostream>
using namespace std;

int count_chars(string &str)
{
	int	n = 0;
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (isalpha(str[i])) n++;
	}
	return n;
}

string	write_number(int n)
{
	int nc = n;
	int thous = nc / 1000;
	nc -= 1000 * thous;
	int hunds = nc / 100;
	nc -= 100 * hunds;
	int	tens = nc / 10;
	nc -= 10 * tens;
	int	ones = nc % 10;

	if (n < 10)
	{
		switch (n)
		{
			case 0 : return "";
			case 1 : return "one";
			case 2 : return "two";
			case 3 : return "three";
			case 4 : return "four";
			case 5 : return "five";
			case 6 : return "six";
			case 7 : return "seven";
			case 8 : return "eight";
			case 9 : return "nine";
		}
	}
	if ( n < 20)
	{
		switch (n)
		{
			case 10 : return "ten";
			case 11 : return "eleven";
			case 12 : return "twelve";
			case 13 : return "thirteen";
			case 14 : return "fourteen";
			case 15 : return "fifteen";
			case 16 : return "sixteen";
			case 17 : return "seventeen";
			case 18 : return "eighteen";
			case 19 : return "nineteen";
		}
	}
	if (n < 100)
	{
		string s_ones = write_number(n % 10);
		string s_tens;
		switch(n / 10)
		{
			case 1 : s_tens = "ERROR"; break;
			case 2 : s_tens = "twenty"; break;
			case 3 : s_tens = "thirty"; break;
			case 4 : s_tens = "forty"; break;
			case 5 : s_tens =  "fifty"; break;
			case 6 : s_tens = "sixty"; break;
			case 7 : s_tens = "seventy"; break;
			case 8 : s_tens = "eighty"; break;
			case 9 : s_tens = "ninety"; break;
		}
		string dash = "";
		if (s_ones != "") dash = "-";
		return s_tens + dash + s_ones;
	}
	if (n < 1000)
	{
		string rs = write_number(n / 100) + " hundred";
		if (ones || tens)
		{
			rs += " and ";
			rs += write_number(10 * tens + ones);
		}

		return rs;
	}
	if (n == 1000)
	{
		return "one thousand";
	}
	return "ERROR";
}

int	main()
{
	int total_chars = 0;
	for (int i = 1; i <= 1000; i++)
	{
		string wn = write_number(i);
		int cc = count_chars(wn);
		total_chars += cc;
	    cout << cc << "  "<< wn << endl;
	}
	printf("Total chars: %d\n", total_chars);
}
