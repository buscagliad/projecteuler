//
// File: card.h
//
// Description:  Defines the Card class - which is any one of the valid
//               52 standard cards (Joker is under construction)
//
// Author:  Dave Buscaglia
//
// History:
//   08 Mar 2000        Dave Buscaglia  Initial release
//

#ifndef _Card_h_
#define _Card_h_

#include <iostream>
#include <string>
#include <ostream>

using namespace std;

const   int     numSuits = 4;
const   int     numRanks = 13;
const   int     cardLowerRange = 1;
const   int     cardUpperRange = numSuits * numRanks;

class Hand;

class	Card {
        friend ostream& operator<<(ostream& os, Card &c);
        friend Hand;
    public:

		enum Suit {Suit_Invalid = 0, Hearts = 1, Spades = 2, Clubs = 3,
	                   Diamonds = 4};

        enum Rank {Rank_Invalid = 0, Two = 2, Three = 3, Four = 4, Five = 5,
	                   Six = 6, Seven = 7, Eight = 8, Nine = 9,
                           Ten = 10, Jack = 11, Queen = 12, King = 13,
                           Ace = 14};

        string  getRankString() const;
        string  getSuitString() const;

        int     getRankValue() const { return (id - 1) % numRanks + 2; };
        int     getSuitValue() const { return (id - 1) / numRanks + 1;};

        Rank	getRank() const;

        Suit	getSuit() const;
        int     getID() const { return id; };
        int		setCard(Suit s, Rank r) ;
        bool    setID(int _id)  { if  ( (_id < cardLowerRange) ||
										(_id > cardUpperRange) ) return false;
										  id = _id;  return true;};

		void	display() { cout << "Rank: " << getRankString() <<
							" Suit: " << getSuitString() << endl; };

        string  getCardString(int long_format = 0) const;
		bool	setCardString(const char *c);	// c[0] is suit, c[1] is card

		Card	(Suit s = Suit_Invalid, Rank r = Rank_Invalid);
        Card    (int card_value);
		bool 	operator ==(const Card &b) const { return b.id == this->id; };
    private:
		int		id;	// 1 to 52, 0 is an invalid card
};

inline  
ostream& operator<<(ostream& os, Card &c)
{
        os << c.getRankString() << " of " << c.getSuitString();
        return os;
}

inline 
int	Card::setCard(Card::Suit s, Card::Rank r) {
	id = (int) (r - 1) + numRanks * ( (int) s - 1);
    return id;
}

inline  
Card::Card(Card::Suit s, Card::Rank r) {
    setCard(s, r);
    }

inline  
Card::Card(int card_value)
{
    if ( card_value >= cardLowerRange  &&  card_value <= cardUpperRange )
       id = card_value;
    else
       id = cardLowerRange;
 //   cout << "id = " << id <<
   //         "  Rank = " << getRankValue() << "  " << getRankString() <<
     //       "  Suit = " << getSuitValue() << "  " << getSuitString() << endl;
}

inline  
Card::Rank   Card::getRank() const 
{
	switch(getRankValue()) 
	{
		case 2: return Two;
		case 3: return Three;
		case 4: return Four;
		case 5: return Five;
		case 6: return Six;
		case 7: return Seven;
		case 8: return Eight;
		case 9: return Nine;
		case 10: return Ten;
		case 11: return Jack;
		case 12: return Queen;
		case 13: return King;
		case 14: return Ace;
			   // case 14: return Joker;
		default: return Rank_Invalid;
	}
	return Rank_Invalid;
}

inline  
Card::Suit	Card::getSuit() const 
{
	switch(getSuitValue()) 
	{
		case 1: return Hearts;
		case 2: return Spades;
		case 3: return Clubs;
		case 4: return Diamonds;

		default: return Suit_Invalid;
	}
	return Suit_Invalid;
}

inline  
string	Card::getRankString() const 
{
	switch(getRankValue()) 
	{
		case  2: return "Two";
		case  3: return "Three";
		case  4: return "Four";
		case  5: return "Five";
		case  6: return "Six";
		case  7: return "Seven";
		case  8: return "Eight";
		case  9: return "Nine";
		case 10: return "Ten";
		case 11: return "Jack";
		case 12: return "Queen";
		case 13: return "King";
		case 14: return "Ace";
		default: return "Invalid";
	}
	return "Invalid";
}

inline  
string	Card::getSuitString() const 
{
	printf("getSuitValue: %d  id: %d\n", getSuitValue(), id);
	switch(getSuitValue()) {
		case 1: return "Hearts";
		case 2: return "Spades";
		case 3: return "Clubs";
		case 4: return "Diamonds";

		default: return "Invalid";
	}
	return "Invalid";
}

inline  
string  Card::getCardString(int long_format) const
{
	string    rs;     // return string

	static    const   char _rank[] = {'0', 'A', '2', '3', '4', '5',
									  '6', '7', '8', '9', 'T', 'J',
									  'Q', 'K', 'A'};
	static    const   char _suit[] = {'0', 'H', 'S', 'C', 'D'};

	if (long_format)
	{
		rs = getRankString() + " of " + getSuitString();
	}
	else
	{
		// cout << "getRankValue " << getRankValue() << endl;
		rs = _rank[getRankValue()];
		// cout << "getSuitValue " << getSuitValue() << endl;
		rs += _suit[getSuitValue()];
		// cout << "rs = " << rs << endl;
	}
	// cout << "long_format " << long_format << " rs " << rs << endl;
	return rs;
}

inline  
bool  Card::setCardString(const char *c)	// c[0] is suit, c[1] is card
{
	string    rs;     // return string

	static    const   std::string crank = "023456789JQKA"; // R - Joker
	static    const   std::string csuit = "0HSCD";
	
	Rank	rank = (Rank) crank.find(c[0]);
	Suit	suit = (Suit) csuit.find(c[1]);
	return setCard(suit, rank);
}



#endif // _Card_h_
