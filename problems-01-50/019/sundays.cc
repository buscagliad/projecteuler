/*

You are given the following information, but you may prefer to do some research for yourself.

    1 Jan 1900 was a Monday.
    Thirty days has September,
    April, June and November.
    All the rest have thirty-one,
    Saving February alone,
    Which has twenty-eight, rain or shine.
    And on leap years, twenty-nine.
    A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.

How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?

*/

#include <stdio.h>

// Note - day 1 will represent Monday, Jan 1, 1900
//        day 7 thus represents Sunday, Jan 7, 1900
//

bool is_leap_year(int y)
{
	if (y % 100 == 0)
	{
		if (y % 400 == 0) return true;
		return false;
	}
	if (y % 4 == 0) return true;
	return false;
}

int num_days_in_year(int y)
{
	if (is_leap_year(y)) return 366;
	return 365;
}

static const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
							   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
static int month_days[]  = {  31,     28,    31,    30,    31,   30,
							  31,     31,    30,    31,    30,   31};
static int leap_days[]   = {  31,     29,    31,    30,    31,   30,
							  31,     31,    30,    31,    30,   31};

static int cumdays[13];
static int cumleapdays[13];

void init()
{
	cumdays[0] = 0;
	cumleapdays[0] = 0;
	for (int i = 1; i < 12; i++)
	{
		cumdays[i] = cumdays[i-1]+month_days[i];;
		cumleapdays[i] = cumleapdays[i-1]+leap_days[i];
	}
}

#define FIRST_SUNDAY 7
//
// all numbers are 0 based
int	cyear = 1900;	// 1900 and above
int cmonth = 0;	// 0 thru 11
int cday = FIRST_SUNDAY;	// day of month
int yday = FIRST_SUNDAY;	// day of year
int eday = FIRST_SUNDAY;	// number of days since epoch

void nextweek()
{
	bool leap = is_leap_year(cyear);
	eday += 7;
	cday += 7;
	yday += 7;
	// check for > 365 for normal year
	// and > 366 for leap year 
	if (yday > num_days_in_year(cyear)) 
	{
		yday -= num_days_in_year(cyear);
		cyear++;
		cday = yday;
		cmonth = 0;
	}
	// check for month roll over
	else if (leap)
	{
		if (cday > leap_days[cmonth])
		{
			cday -= leap_days[cmonth];
			cmonth++;
		}
	}
	else
	{
		if (cday > month_days[cmonth])
		{
			cday -= month_days[cmonth];
			cmonth++;
		}
	}	
}

void printday()
{
	printf("%s %d, %4.4d\n", months[cmonth], cday, cyear);
}

int	main()
{
	init();
	int numSundays = 0;
	while (cyear < 1901) nextweek();
	while (cyear < 2001)
	{
		nextweek();
		if (cday == 1) {
			numSundays++;
			printf("** ");
			printday();
		}
		//else
		//    printf("   ");
		//printday();
	}
	printf("Number of Sundays that fall on the first of the month in the 20th century are: %d\n", 
			numSundays);
}
