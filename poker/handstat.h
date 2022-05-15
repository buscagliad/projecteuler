//
// File: handstat.h
//
// Description:  Defines the HandStat class to keep track of
//		hands and the cards they are dealt.
//
// Author:  Dave Buscaglia
//
// History:
//   08 Mar 2000        Dave Buscaglia  Initial release
//

#ifndef _HandStat_h_
#define _HandStat_h_

#include <string>
#include <iostream>
using namespace std;

#include "card.h"
#include "deck.h"
#include "hand.h"

class	HandStat {
    friend ostream& operator<<(ostream& os, HandStat &hs);

    public:

		HandStat (const Deck &d, const Hand &h);
		// stats are based on
		// hand and deck sizes

		HandStat (const Hand &h);	// stats are based on
		// hand size - object
		// only report hand stats

		HandStat (const Deck &d);	// stats are based on
		// deck size - object will
		// only report deck stats

        ~HandStat();

        void    display(ostream &os);
        int     add(Hand &d);

    private:
		void    cardInit();
		void    cardInit(const Deck &d);
		void    handInit();
		void    handInit(const Hand &d);

		int		cardCount[60];	// array of counts
		int		cardCountSize;	// size of cardCount array
		int		handCount[20];	// array of hand counts
		int		handCountSize;	// size of handCount array
		int		handSize;	// number of cards in a hand
		int     numHands;       // number of hands in stats

};

inline  
ostream& operator<<(ostream& os, HandStat &hs)
{
        hs.display(os);
        return os;
}

//
// File: handstat.cc
//
// Description:  Keeps track of hands and their statistics
//
// Author: Dave Buscaglia
//
// History:
//    12 Mar 2000       D. Buscaglia    Initial release
//

inline  
void	HandStat::cardInit()
{
	cardCountSize = 0;
}

inline  
void	HandStat::handInit()
{
	handCountSize = 0;
	handCountSize = 0;
}

inline  
void	HandStat::cardInit(const Deck &d)
{
	cardCountSize = d.size();

	for (int i = 0; i < cardCountSize; i++) 
		cardCount[i] = 0;
}

inline  
void	HandStat::handInit(const Hand &h)
{	
	handCountSize = Hand::numHandTypes;
	handSize = h.size();

	for (int i = 0; i < handCountSize; i++) 
		handCount[i] = 0;
}

inline  
HandStat::HandStat(const Deck &d, const Hand &h)
{
	handInit(h);
	cardInit(d);
	numHands = 0;
}
inline  
HandStat::HandStat(const Hand &h)
{
	handInit(h);
	cardInit();
	numHands = 0;
}
inline  
HandStat::HandStat(const Deck &d)
{
	handInit();
	cardInit(d);
	numHands = 0;
}

inline  
HandStat::~HandStat()
{
}

inline  
int     HandStat::add(Hand &h)
{
	handCount[(int)h.Type()]++;
	return ++numHands;
}

inline  
void    HandStat::display(ostream &os)
{
	os << "Number of Hands played:: " << numHands << endl;

	// display deck stats
	for (int i = 0; i < cardCountSize; i++)
	{
		Card        c(i);
		double      percent = (double) cardCount[i] / (double) numHands;
		cout << c << "  " << cardCount[i] << "  " << 
		percent << endl;
	}

	// display hand stats for hands of size 5
	// don't display three pair

	for (int i = 0; i < handCountSize; i++)
	{
		Hand	h;
		double      percent = (double) handCount[i] / (double) numHands;
		h.ht = (Hand::HandType)i;

		os.width(30);
		os << h.strType() << ":  ";
		os << "   (";
		os.width(7);
		os << handCount[i] << '/';
		os.width(7);
		os << numHands << ")   ";
		os.precision(6);
		os << percent;
		os << endl;
	}
}    
	    



#endif // _Card_h_
