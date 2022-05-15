//
// File: hand.h
//
// Description:  Defines the class hand - which is a set of Cards from
//               a Deck.
//
// Author: Dave Buscaglia
//
// History:
//    12 Mar 2000       D. Buscaglia    Initial release
//

#ifndef _Hand_h_
#define _Hand_h_

#include <iostream>
#include <string>
#include <ostream>
#include "card.h"
#include "deck.h"

using namespace std;

class   HandStat;   // needed for HandStat to "see" Hand

class   Hand {
	friend class HandStat;
	friend ostream& operator<<(ostream& os, Hand &h);
	public:
		enum HandType {
			Nothing = 0,      // only used when no of the below are detected
			OnePair,          // 2 cards in hand have matching rank
			TwoPair,          // 2 sets of 2 cards in hand have matching rank
			ThreeOfKind,      // hand contains a three of a kind
			Straight,         // standard 5 card straight
			Flush,            // standard 5 card flush
			FullHouse,		  // 3 of a kind with a pair
			FourOfKind,		  // four of a kind
			StraightFlush,    // 5 card straight flush
			numHandTypes      // number of different kinds of hands
		};
		Hand(int handSize = 5);
		~Hand();
		Hand(Hand &h, int n = 0);     // n <= 0, n > numCards means copy
		Hand(Hand &h, Card::Suit);
		HandType    Type() {return (HandType)ht;};
		HandType    set(Card d[5]) {
			for (int i = 0; i < 5; i++) { c[i] = d[i];} typeIt(); 
			return (HandType) ht;};
		int		isType(HandType t){ return ht == t; };
		string  strType();
		void    display(ostream &os = cout, int cr = 1);
		int     deal(Deck &d);
		int     size() const {return numCards; }
		void    test(int, int, int, int, int);
		void    test(int, int, int, int, int, int, int);
		int     match()
		{
			int rv = 0;
			int lv = 1;
			for (int i = 0; i < numCards - 3; i++)
			{
				for (int j = i+1; j < numCards; j++)
				if (c[i].getRankValue() == c[j].getRankValue()) lv++;
				if (rv < lv) rv = lv;
				lv = 1;
			}
			return rv;
		}
		bool 	operator<( Hand &b) ;
	private:
		enum SortType {ByRank, BySuit, ByID};
		int		straighsNflushes();

		void    sort(SortType) ;
		int 	isFlush();
		int     largestStraight();   // returns largest consecutive run of cards
		int     largestFlush();      // returns largest number of cards of same suit
		int     largestStraightFlush();
		int     getMatches();   // finds cards in hand that match (if any)
		void    typeIt();       // method to type hand

		Card    c[7];        // array of cards that make up the hand
		int     numCards;  // number of cards in the hand
		int		straightFlush; // if not-zero, Rank of the highest card in straigh flush
		int		straight;	// if not-zero, Rank of the highest card in straight
		int		flush;		// if non-zero, Rank of the highest card in flush
		int		fourOfAKind;	// if non-zero, Rank of the four of a kind
		int		threeOfAKind;	// if non-zero, Rank of the three of a kind
		int		pair1;			// if non-zero, Rank of the highest pair in hand
		int     pair2;          // if non-zero, Rank of the second highes pair in hand
		int		highCard;		// if nothing - this is the highest card
		int     ht;

};

bool 	Hand::operator<( Hand &h)  
{
	if (this->ht < h.ht) return true;
	if (this->ht == h.ht)
	{
		this->sort(ByRank);
		h.sort(ByRank);
		switch(h.ht)
		{
			case Nothing:      // only used when no of the below are detected
				for (int i = numCards - 1; i >= 0; i--)
				{
					if (this->c[i].getRank() == h.c[i].getRank()) continue;
					if (this->c[i].getRank() < h.c[i].getRank()) return true;
					return false;
				}
				return false;

			case OnePair:          // 2 cards in hand have matching rank
				if (this->pair1 < h.pair1) return true;
				if (this->pair1 > h.pair1) return false;
				for (int i = numCards - 1; i >= 0; i--)
				{
					if (this->c[i].getRank() == h.c[i].getRank()) continue;
					if (this->c[i].getRank() < h.c[i].getRank()) return true;
					return false;
				}
				return false;
	
			case TwoPair:          // 2 sets of 2 cards in hand have matching rank
				if (this->pair1 < h.pair1) return true;
				if (this->pair1 > h.pair1) return false;
				if (this->pair2 < h.pair2) return true;
				if (this->pair2 > h.pair2) return false;
				for (int i = numCards - 1; i >= 0; i--)
				{
					if (this->c[i].getRank() == h.c[i].getRank()) continue;
					if (this->c[i].getRank() < h.c[i].getRank()) return true;
					return false;
				}
				return false;
	
			case ThreeOfKind:      // hand contains a three of a kind
				if (this->threeOfAKind < h.threeOfAKind) return true;
				return false;

			case StraightFlush:    // 5 card straight flush
			case Straight:         // standard 5 card straight
				if (this->straight < h.straight) return true;
				return false;
				
			case Flush:            // standard 5 card flush
				if (this->flush < h.flush) return true;
				for (int i = numCards - 1; i >= 0; i--)
				{
					if (this->c[i].getRank() == h.c[i].getRank()) continue;
					if (this->c[i].getRank() < h.c[i].getRank()) return true;
					return false;
				}
				return false;
			
			case FullHouse:		  // 3 of a kind with a pair
				if (this->threeOfAKind < h.threeOfAKind) return true;
				return false;
			
			case FourOfKind:		  // four of a kind
				if (this->fourOfAKind < h.fourOfAKind) return true;
				return false;
			
			 default:
				printf("SHOULD NEVER GET HERE!!!\n");
		}
	}
	return false;
}

//
// File: hand.cc
//
// Description:  Defines the class hand - which is a set of Cards //			from a Deck.
//
// Author: Dave Buscaglia
//
// History:
//    12 Mar 2000       D. Buscaglia    Initial release
//

inline
int	Hand::getMatches()
{
	pair1 = pair2 = threeOfAKind = fourOfAKind = 0;
	int	cMatch = 1;
	int lMatch = 0;
	sort(ByRank);
	int rv = Nothing;
	for (int i = 0; i < numCards; i++)
	{
		if ((i+1 < numCards) && c[i+1].getRankValue() == c[i].getRankValue()) cMatch++;
		else
		{
			if (lMatch < cMatch) lMatch = cMatch;
			if (cMatch == 2) {
				if (pair1 == 0){
					 pair1 = c[i-1].getRankValue();
					 rv = OnePair;
				}
				else {
		            pair2 = c[i-1].getRankValue();
		            rv = TwoPair;
				}
			}
			if (cMatch == 3){
				threeOfAKind = c[i-1].getRankValue();
				rv = ThreeOfKind;
			}
			if (cMatch == 4) {
				fourOfAKind = c[i-1].getRankValue();
				rv = FourOfKind;
			}
			cMatch = 1;
		}
	}
	if (pair2 == Card::Ace)
	{
		int pair1_hold = pair1;
		pair1 = pair2;
		pair2 = pair1_hold;
	}
	if (pair1 && threeOfAKind)
	{
		rv = FullHouse;
	}


	return rv;
}


//
// returns highest card in straight flush (Ace is considered HIGH in this case)
// otherwise returns 0
inline
int     Hand::largestStraightFlush()
{
	int		isF = isFlush();	// isFlush returns Card::Suit if flush, < 0 otherwise
	int 	ace = -1;
	int		cRun = 1;		// current run, always have a run of 1
	int     rRank = 0;

	sort(ByID);
	if (isF >= 0)  // check if the flush is 'straight'
	{
		//cout << "ACE: " << ac << endl;
		for (int i = 0; i < numCards; i++)
		{
			if (c[i].getSuit() != (Card::Suit)isF) continue;
			if (c[i].getRankValue() == Card::Ace) ace = i;
			//printf("i = %d  rRank: %d\n", i, rRank);
			if ( (i < numCards - 1) && ( (c[i+1].getRankValue() - c[i].getRankValue() == 1) ) )	
			{
				cRun++;
				rRank = c[i+1].getRankValue();
				//printf("LSF: ace: %d  cRun: %d  i: %d\n", ace, cRun, i);
			}
			else if ( (cRun == 4) && (rRank == 5) && ace != -1)
			{
				cRun++;
				//printf("LSFxx: ace: %d cRun: %d  i: %d\n", ace, cRun, i);
			}
			if (cRun >= 5) return rRank;
		}
	}
	return 0;
}

inline
int Hand::isFlush()
{
	sort(BySuit);
	int	ns[5] = {0, 0, 0, 0, 0};	// 0 is invalid, 1,2,3,4 represet Hearts, Spades, Clubs, Diamonds
	for (int i = 0; i < numCards; i++)
		ns[c[i].getSuit()]++;
	for (int i = 1; i <= 4; i++)
		if (ns[i] >= 5) {
			//printf("ns: %d %d %d %d %d   i: %d\n", ns[0], ns[1], ns[2], ns[3], ns[4], i);
			return i;
		}
	return -1;
}


inline
int	Hand::largestFlush()
{
	int		isF = isFlush();
	int		tRank = 0;

	if (isF >= 0)
	{
		Card ac((Card::Suit)isF, Card::Ace);
		for (int i = 0; i < numCards; i++)
		{
			if (c[i] == ac) return Card::Ace;
			if (c[i].getRank() > tRank) tRank = c[i].getRank();
			//printf("i = %d  tRank: %d\n", i, tRank);
		}
		return tRank;
	}

	return 0;
}

	
inline
int     Hand::largestStraight()
{
	int     cRun = 1;     // continuous run counter, initially 1
	int 	ace = -1;
	int     rRank = 0;
	

	sort(ByRank);
	for (int i = 0; i < numCards; i++)
	{
		if (c[i].getRankValue() == Card::Ace) ace = i;
		//printf("c[%d] %d  ace: %d \n", i, c[i].getRankValue(), ace);
		if (((i+1) < numCards) && (c[i+1].getRankValue() - c[i].getRankValue() == 1))
		{
			cRun++;
			rRank = c[i+1].getRankValue();
			//printf("i: %d  cRun: %d  rank: %d\n", i, cRun, rRank);
		}
		else if ( (cRun == 4) && (rRank == 5) && ace != -1)
		{
			cRun++;
			//printf("xx i: %d  cRun: %d  rank: %d\n", i, cRun, rRank);
		}

		if (cRun >= 5) return rRank;

	}
	return 0;
}


inline
void    Hand::typeIt()
{
	straightFlush = 0; // if not-zero, Rank of the highest card in straigh flush
	straight = 0;	// if not-zero, Rank of the highest card in straight
	flush = 0;		// if non-zero, Rank of the highest card in flush
	ht = 0;
	straightFlush = largestStraightFlush();
	if (!straightFlush)
	{
		flush = largestFlush();
		if (!flush)
		{
			straight = largestStraight();
			if (straight)
			    ht = Straight;
		}
		else
			ht = Flush;
	}
	else
		ht = StraightFlush;
	if (!ht)
	{
		ht = getMatches();
	}
}	
    
inline
string  Hand::strType()
{
#define CASE(m) case m: return #m;
	switch(ht)
	{
		  CASE(Nothing);          // only used when no of the below are detected
		  CASE(OnePair);          // only valid for hands of >= 2 cards
		  CASE(TwoPair);          // only valid for hands of >= 4 cards
		  CASE(Straight);         // standard 5 card straight
		  CASE(ThreeOfKind);      // hand contains a three of a kind
		  CASE(FullHouse);
		  CASE(FourOfKind);
		  CASE(Flush);            // standard 5 card straight
		  CASE(StraightFlush);    // 5 card straight flush
		  default: return "Unknown";
	}
	return "Unknown";
}


inline
void    Hand::sort(SortType st)    // sorts hand by rank and suit
{
	int    t;
	//display();
	//printf("numCards: %d\n", numCards);
	// enum SortType {ByRank, BySuit, ByID};
	for (int i = 0; i < numCards; i++)
	{
		for (int j = i + 1; j < numCards; j++)
		{
			if ( ( st == ByID   &&
				(c[i].getID() > c[j].getID())     ) ||
				( st == BySuit &&
				(c[i].getSuitValue() > c[j].getSuitValue()) ) ||
				( st == ByRank &&
				(c[i].getRankValue() > c[j].getRankValue()) )   )
			{
				t = c[i].id;
				c[i].id = c[j].id;
				c[j].id = t;
			}
		}
	}
}

inline
int     Hand::deal(Deck &d)
{
	//printf("Num Cards: %d   Deck: %d\n", numCards, d.cardsLeft());
	if (d.cardsLeft() < numCards)
		return 0;     // indicate that there is not enough cards in deck
	for (int i = 0; i < numCards; i++)
		if (!d.deal(c[i])) return 0;  // a real problem here??
	typeIt();
	return 1;
}

inline
void    Hand::test(int c1, int c2, int c3, int c4, int c5)
{
	if (numCards < 5)
	{
		cerr << "Bad test case - less than 5 card hand" << endl;
		return;
	}
	c[0] = c1; c[1] = c2; c[2] = c3; c[3] = c4; c[4] = c5;
	numCards = 5;
	typeIt();
}

inline
void    Hand::test(int c1, int c2, int c3, int c4, int c5, int c6, int c7)
{
	if (numCards < 7)
	{
		cerr << "Bad test case - less than 7 card hand" << endl;
		return;
	}
	c[0] = c1; c[1] = c2; c[2] = c3; c[3] = c4;
	c[4] = c5; c[5] = c6; c[6] = c7;
	numCards = 7;
	typeIt();
}

inline
void    Hand::display(ostream &os, int cr)
{
	for (int i = 0; i < numCards; i++)
		os << c[i].getCardString(0) << " ";
	os << "    " << strType();
	if (cr) os << endl;
}

inline
ostream& operator<<(ostream& os, Hand &h)
{
	h.display(os, 0);
	return os;
}

inline
Hand::Hand(int n)
{
	numCards = n;
}

inline
Hand::Hand(Hand &h, int n)
{
	if (n <= 0 || n > h.numCards) n = h.numCards;
	for (int i = 0; i < numCards; i++) c[i]=h.c[i];
}

inline
Hand::Hand(Hand &h, Card::Suit s)
{
	int     n = 0;
	for (int i = 0; i < h.numCards; i++)
		 if (h.c[i].getSuit() == s) n++;
	// cout << "Hand size " << n;
	n = 0;
	for (int i = 0; i < h.numCards; i++)
		 if (h.c[i].getSuit() == s) c[n++] = h.c[i];
	// cout << "   New hand: " << *this << endl;

}

inline
Hand::~Hand()
{
	numCards = 0;
}

#endif
