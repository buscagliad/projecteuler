#ifdef PROBLEM_DESCRIPTION

Roman numerals


  [Show HTML problem content]  
Problem 89

For a number written in Roman numerals to be considered valid there are basic rules which must be followed. Even though the rules allow some numbers to be expressed in more than one way there is always a "best" way of writing a particular number.

For example, it would appear that there are at least six ways of writing the number sixteen:

IIIIIIIIIIIIIIII
VIIIIIIIIIII
VVIIIIII
XIIIIII
VVVI
XVI

However, according to the rules only XIIIIII and XVI are valid, and the last example is considered to be the most efficient, as it uses the least number of numerals.

The 11K text file, roman.txt (right click and 'Save Link/Target As...'), contains one thousand numbers written in valid, but not necessarily minimal, Roman numerals; see About... Roman Numerals for the definitive rules for this problem.

Find the number of characters saved by writing each of these in their minimal form.

Note: You can assume that all the Roman numerals in the file contain no more than four consecutive identical units.


raditional Roman numerals are made up of the following denominations:

I = 1
V = 5
X = 10
L = 50
C = 100
D = 500
M = 1000

In order for a number written in Roman numerals to be considered valid there are three basic rules which must be followed.

Numerals must be arranged in descending order of size.
M, C, and X cannot be equalled or exceeded by smaller denominations.
D, L, and V can each only appear once.

For example, the number sixteen could be written as XVI or XIIIIII, with the first being the preferred form as it uses the least number of numerals. We could not write IIIIIIIIIIIIIIII because we are making X (ten) from smaller denominations, nor could we write VVVI because the second and third rule are being broken.

The "descending size" rule was introduced to allow the use of subtractive combinations. For example, four can be written IV because it is one before five. As the rule requires that the numerals be arranged in order of size it should be clear to a reader that the presence of a smaller numeral out of place, so to speak, was unambiguously to be subtracted from the following numeral rather than added.

For example, nineteen could be written XIX = X (ten) + IX (nine). Note also how the rule requires X (ten) be placed before IX (nine), and IXX would not be an acceptable configuration (descending size rule). Similarly, XVIV would be invalid because V can only appear once in a number.

Generally the Romans tried to use as few numerals as possible when displaying numbers. For this reason, XIX would be the preferred form of nineteen over other valid combinations, like XIIIIIIIII or XVIIII.

By mediaeval times it had become standard practice to avoid more than three consecutive identical numerals by taking advantage of the more compact subtractive combinations. That is, IV would be written instead of IIII, IX would be used instead of IIIIIIIII or VIIII, and so on.

In addition to the three rules given above, if subtractive combinations are used then the following four rules must be followed.

    Only one I, X, and C can be used as the leading numeral in part of a subtractive pair.
    I can only be placed before V and X.
    X can only be placed before L and C.
    C can only be placed before D and M.

Which means that IL would be considered to be an invalid way of writing forty-nine, and whereas XXXXIIIIIIIII, XXXXVIIII, XXXXIX, XLIIIIIIIII, XLVIIII, and XLIX are all quite legitimate, the latter is the preferred (minimal) form. However, minimal form was not a rule and there still remain in Rome many examples where economy of numerals has not been employed. For example, in the famous Colosseum the numerals above the forty-ninth entrance is written XXXXVIIII rather than XLIX.

It is also expected, but not required, that higher denominations should be used whenever possible; for example, V should be used in place of IIIII, L should be used in place of XXXXX, and D should be used in place of CCCCC. However, in the church of Sant'Agnese fuori le Mura (St Agnes' outside the walls), found in Rome, the date, MCCCCCCVI (1606), is written on the gilded and coffered wooden ceiling; I am sure that many would argue that it should have been written MDCVI.

So if we believe the adage, "when in Rome do as the Romans do," and we see how the Romans write numerals, then it clearly gives us much more freedom than many would care to admit.
#endif

#include <cstdio>
#include <cstring>

int rchar(char c)
{
	switch(c)
	{
		case 'I': return 1;
		case 'V': return 5;
		case 'X': return 10;
		case 'L': return 50;
		case 'C': return 100;
		case 'D': return 500;
		case 'M': return 1000;
	}
	return 0;
}

static const char *hund[] = {
 "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X",
	"XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX",
	"XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX",
	"XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL",
	"XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L",
	"LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX",
	"LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX",
	"LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX",
	"LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",
	"XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"};
	
static const char *tthou[] = {
	"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM", "M",
	"MC", "MCC", "MCCC", "MCD", "MD", "MDC", "MDCC", "MDCCC", "MCM", "MM",
	"MMC", "MMCC", "MMCCC", "MMCD", "MMD", "MMDC", "MMDCC", "MMDCCC", "MMCM", "MMM",
	"MMMC", "MMMCC", "MMMCCC", "MMMCD", "MMMD", "MMMDC", "MMMDCC", "MMMDCCC", "MMMCM", "MMMM",
	"MMMMC", "MMMMCC", "MMMMCCC", "MMMMCD", "MMMMD", "MMMMDC", "MMMMDCC", "MMMMDCCC", "MMMMCM", "MMMMM"}; 

//MMMDCCCLXXI
int rvalue(const char *s)
{
	int lv = rchar(*s++);
	int rv = 0;
	int tv;
	while ((tv = rchar(*s++)))
	{
		if (lv < tv) rv -= lv;
		else rv += lv;
		lv = tv;
	}
	rv += lv;
	return rv;
}

void getroman(char *s, int v)
{
	strcpy(s, tthou[v/100]);
	strcat(s, hund[v%100]);
}

int main()
{
	#define MAXS 100
	char s[MAXS];
	char rc[MAXS];  //roman compressed form
	int numc = 0;
	FILE *f = fopen("p089_roman.txt", "r");
	int cnt = 1;
	while (!feof(f))
	{
		fgets(s, MAXS, f);
		if (feof(f)) break;
		s[strlen(s)-1] = 0;
		int val = rvalue(s);
		getroman(rc, val);
		int nval = rvalue(rc);
		numc += strlen(s) - strlen(rc);
		printf("[%5d]  Value: %8d   Roman: %s   Proper: %s   PValue: %d [[ %lu :: %d]]\n", cnt++, val, s, rc, nval, strlen(s) - strlen(rc), numc);
		if (val != nval)
		{
			printf("ERRRRRRRRROR\n");
			return(1);
		}
	}
	printf("Number of characters save: %d\n", numc);
}

