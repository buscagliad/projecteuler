#include <iostream>
using namespace std;

#include "deck.h"
#include "hand.h"
#include "card.h"
#include "handstat.h"

void    testCard()
{
	for (int i = 0; i < 52; i++)
	{
		Card c(i);
		cout << c << "  R: " << c.getRankValue() << "  " << c.getRankString()
				  << "   "
				  << "  S: " << c.getSuitValue() << "  " << c.getSuitString()
				  << "  ID: " << c.getID() << endl;
	}
}

void    testDeck()
{
	Deck    d;
	Card    c;
	int     i = 0;
	string  outS;
	string  cardS;

	i = 0;
	while (d.deal(c))
	{
		cout << ++i << c << endl;
	}

	d.reset();
	while (d.deal(c))
	{
		outS += c.getCardString();
		if (outS.length() >= 78)
		{
			cout << outS << endl;
			outS.clear();
		}
		else outS += " ";
	}
	cout << outS << endl;
	outS.clear();

	d.shuffle();
	i = 0;

	while (d.deal(c))
	{
		cout << ++i << c << endl;
	}

	d.display();
	d.reset();
	while (d.deal(c))
	{
		outS += c.getCardString();
		if (outS.length() >= 78)
		{
			cout << outS << endl;
			outS.clear();
		}
		else outS += " ";
	}
	cout << outS << endl;

	d.shuffle();
}

int     testHand(int numShuffles)
{
	Deck    d;
	Hand    h_7(7);
	Hand    h_def;

	for (int i = 1; i <= numShuffles; i++)
	{
		while(h_7.deal(d)) cout << "h_7:: " << h_7 << endl;
		d.reset();
		while(h_def.deal(d)) cout << "h_def:: " << h_def << endl;
		d.shuffle();
	}
	return 1;
}

enum    cList {INVALID,  // id == 0 is an invalid card
			   H2, H3, H4, H5, H6, H7, H8, H9, HT, HJ, HQ, HK, HA, 
               S2, S3, S4, S5, S6, S7, S8, S9, ST, SJ, SQ, SK, SA, 
               C2, C3, C4, C5, C6, C7, C8, C9, CT, CJ, CQ, CK, CA, 
               D2, D3, D4, D5, D6, D7, D8, D9, DT, DJ, DQ, DK, DA };
               
int testSF()
{
	Deck    d;
	Hand    h;
	d.test(H2, H3, H4, H5, HA);
	h.deal(d);
	h.display();

	d.test(S2, S3, S4, S5, SA);
	h.deal(d);
	h.display();

	d.test(C2, C3, C4, C5, CA);
	h.deal(d);
	h.display();

	d.test(D2, D3, D4, D5, DA);
	h.deal(d);
	h.display();
	
	d.test(D2, D3, D4, D5, D6);
	h.deal(d);
	h.display();
    return 1;
}

int     testTyping()
{

	Deck    d;
	Hand    h;
	Hand    h5;

	printf("\nA thru 5 low straight\n");
	d.test(H2, S3, C4, C5, DA);
	h.deal(d);
	h.display();

	printf("\nAce high straight\n");
	d.test(HT, SA, SJ, SK, SQ);
	h.deal(d);
	h.display();
	
    printf("\nFour of a kind - 4 6's\n");
	h5.test(H6, S6, SA, D6, C6);
	h5.display();
	
	
    printf("\nFour of a kind - 4 Jacks's\n");
	d.test(HJ, SJ, C6, CJ, DJ);
	h.deal(d);
	h.display();
	
    printf("\nThree of a kind - 3 3's\n");
	d.test(H7, S3, C3, D3, D2);
	h.deal(d);
	h.display();

    printf("\nTwo pair - Kings over twos's\n");
	d.test(H2, S2, CK, D3, DK);
	h.deal(d);
	h.display();

	printf("\nAce high\n");
	d.test(H2, SQ, CJ, CK, DA);
	h.deal(d);
	h.display();

	printf("\nAce high straight flush\n");
	d.test(S5, SA, S2, S4, S3);
	h.deal(d);
	h.display();

	printf("\nDiamond flush\n");
	d.test(D3, D7, DT, DK, D8);
	h.deal(d);
	h.display();

	printf("\nClub royal flush\n");
	d.test(CT, CK, CQ, CJ, CA);
	h.deal(d);
	h.display();
	return 1;
}

void     testShuffle(int iters)
{

	Deck      d;
	Hand      h;
	HandStat  hs(d, h);

	d.shuffle();
	for (int i = 1; i <= iters; i++)
	{
		 h.deal(d);
		 // h.display();
		 d.shuffle();
		 hs.add(h);
	}
	hs.display(cout);
}



void     test5Hands()
{
	Hand            h;
	HandStat        hs(h);
	int     c1, c2, c3, c4, c5;
	char    outstring[100];
	const int  C1_END = 48;
	const int  C2_END = 49;
	const int  C3_END = 50;
	const int  C4_END = 51;
	const int  C5_END = 52;

	for (c1 = 1; c1 <= C1_END; c1++)
	{
	  time_t now;
	  time(&now);
	  sprintf (outstring, "%s", asctime(localtime(&now)));

	  outstring[19]=0;
	  for (c2 = c1 + 1; c2 <= C2_END; c2++)
	  {
		for (c3 = c2 + 1; c3 <= C3_END; c3++)
		{
		  for (c4 = c3 + 1; c4 <= C4_END; c4++)
		  {
			for (c5 = c4 + 1; c5 <= C5_END; c5++)
			{
			  h.test(c1, c2, c3, c4, c5);
			  hs.add(h);
			}
		  }
		}
	  }
	}

	hs.display(cout);
	
	printf(
		   "High Card          1,302,540\n"
		   "One Pair           1,098,240\n"
		   "Two Pair             123,552\n"
		   "Three of a Kind       54,912\n"
		   "Straight              10,200\n"
		   "Flush                  5,108\n"
		   "Full house             3,744\n"
		   "Four of a Kind           624\n"
		   "Straight Flushes          40\n"
		   );
}


void     test7Hands()
{
	Hand            h(7);
	HandStat        hs(h);
	int     c1, c2, c3, c4, c5, c6, c7;
	char    outstring[100];
	const int  C1_END = 46;
	const int  C2_END = 47;
	const int  C3_END = 48;
	const int  C4_END = 49;
	const int  C5_END = 50;
	const int  C6_END = 51;
	const int  C7_END = 52;

	for (c1 = 0; c1 < C1_END; c1++)
	{
	  time_t now;
	  time(&now);
	  sprintf (outstring, "%s", asctime(localtime(&now)));
	  outstring[19]=0;

	  for (c2 = c1 + 1; c2 < C2_END; c2++)
	  {
		for (c3 = c2 + 1; c3 < C3_END; c3++)
		{
		  for (c4 = c3 + 1; c4 < C4_END; c4++)
		  {
			for (c5 = c4 + 1; c5 < C5_END; c5++)
			{
			  for (c6 = c5 + 1; c6 < C6_END; c6++)
			  {
				 for (c7 = c6 + 1; c7 < C7_END; c7++)
				 {
					 h.test(c1, c2, c3, c4, c5, c6, c7);
					 hs.add(h);
				 }
			  }
			}
		  }
		}
	  }
	}

	hs.display(cout);
}

int     main(int argc, char **argv)
{
        cout << "Entering main" << endl;
 //       testSF();
//       testCard();
       //  testHand(3);
      //  testTyping();
        // testShuffle(2598960);
        test5Hands();
     //   test7Hands();
//    x_test();
        return 0;
}
