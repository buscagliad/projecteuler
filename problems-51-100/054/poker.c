
#include "card.h"
#include "hand.h"

enum Suit {Suit_Invalid = 0, Hearts = 1, Spades = 2, Clubs = 3,
	                   Diamonds = 4};

enum Rank {Rank_Invalid = 0, Two = 2, Three = 3, Four = 4, Five = 5,
	                   Six = 6, Seven = 7, Eight = 9, Nine = 9,
                           Ten = 10, Jack = 11, Queen = 12, King = 13,
                           Ace = 1};

Card::Suit S(char c)
{
	switch(c)
	{
		case 'H': return Card::Hearts;
		case 'S': return Card::Spades;
		case 'C': return Card::Clubs;
		case 'D': return Card::Diamonds;
		default:	return Card::Suit_Invalid;

	}
	return Card::Suit_Invalid;
}

Card::Rank R(char c)
{
	switch(c)
	{
		case 'A' : return Card::Ace;
		case '2' : return Card::Two;
		case '3' : return Card::Three;
		case '4' : return Card::Four; 
		case '5' : return Card::Five;
	    case '6' : return Card::Six;
	    case '7' : return Card::Seven; 
	    case '8' : return Card::Eight;
	    case '9' : return Card::Nine;
        case 'T' : return Card::Ten;
        case 'J' : return Card::Jack;
        case 'Q' : return Card::Queen;
        case 'K' : return Card::King;
        default:     return Card::Rank_Invalid;

     }
     return Card::Rank_Invalid;
 }


bool    getHand(FILE *f, Hand &h)
{
	Card	c[5];
	// 5C AD 5D AC 9C 7C 5H 8D TD KS
	for (int i = 0; i < 5; i++)
	{
		int r = fgetc(f);
		int s = fgetc(f);
		fgetc(f);
		//printf("r = %c    s = %c\n", r, s);
		c[i].setCard(S(s), R(r));
	}
	h.set(c);
	return true;
}
		

bool	readHands(FILE *f, Hand &h1, Hand &h2)
{
	getHand(f, h1);
	//cout << "h1 is " << h1 << endl;
	getHand(f, h2);
	//cout << "h2 is " << h2 << endl;
	return !feof(f);
}


int main()
{
	FILE *f = fopen("p054_poker.txt", "r");
	Hand h1, h2;
	int h1_count = 0;
	int h2_count = 0;
	while (readHands(f, h1, h2))
	{
		cout << "Hand 1:: " << h1 << "     Hand 2:: " << h2;
		if (h1 < h2) { cout << "  >>> "; h2_count ++;} else 
					 { cout << "  <<< "; h1_count++; }
		cout << endl;
	}
	printf("H1 won %d hands, h2 won %d hands\n", h1_count, h2_count);
}
