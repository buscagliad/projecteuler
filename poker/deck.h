//
// File:  Deck.h
//
// Description:  Defines a variety of types of decks of card:
//                    ** Poker_Deck     Standard 52 card deck w/Joker
//                    ** Bridge_Deck    Standard 52 card deck
//                       Deck           Standard 52 card deck
//                    ** Pinochle_Deck  48 card pinochle deck
//         ** Under construction - not yet available
//
// Author:  Dave Buscaglia
//
// History:
//    08 Mar 2000       Dave Buscaglia  Initial release
//

#ifndef _Deck_h_
#define _Deck_h_


#include <time.h>

#include "card.h"
#include "stdlib.h"

class   Deck {
        public:
               void     shuffle(int seed = 0);
               int      deal(Card &c);   // returns 0 card if deck has been dealt
               void     display() const;
               int      cardsLeft() const;
               void     reset();        // resets deck to last shuffle
               void     test(int i1, int i2, int i3, int i4,
                                     int i5, int i6, int i7) {
                                     *deck[0] = Card(i1);
                                     *deck[1] = Card(i2);
                                     *deck[2] = Card(i3);
                                     *deck[3] = Card(i4);
                                     *deck[4] = Card(i5);
                                     *deck[5] = Card(i6);
                                     *deck[6] = Card(i7); top_card = 0; }
              void     test(int i1, int i2, int i3, int i4,
                                     int i5) {
                                     *deck[0] = Card(i1);
                                     *deck[1] = Card(i2);
                                     *deck[2] = Card(i3);
                                     *deck[3] = Card(i4);
                                     *deck[4] = Card(i5); top_card = 0; }
               Deck(int size = 52, int seed = time(0));
               ~Deck();
               int      size() const { return numCards; }
        private:
               int      numCards;
               Card     **deck;
               int      top_card;       // assigned to top of deck
};

inline
void    Deck::reset()
{
        top_card = 0;
}

inline
Deck::Deck(int size, int seed)
{
        if (seed) srand(seed);
        deck = new Card* [size+1];
        numCards = size;
        top_card = 0;
        for (int i = 0; i <= numCards; i++)
            deck[i] = new Card(i);

}

inline
Deck::~Deck()
{
        for (int i = 0; i < numCards; i++)
            delete deck[i];
        delete [] deck;
}

inline
void    Deck::shuffle(int seed)
{
        top_card = 0;
        if (seed) srand(seed);
        Card     *t;
        for (int i = 0; i < numCards; i++)
        {
            int j = random() % numCards;
            t = deck[j];
            deck[j] = deck[i];
            deck[i] = t;
        }
}


inline
int     Deck::cardsLeft() const
{
        return numCards - top_card;
}

inline
int    Deck::deal(Card &c)
{
        if (top_card < numCards)
        {
            c = *deck[top_card++];
            return 1;
        }
        return 0;
}

inline
void    Deck::display() const
{
        for (int i = 0; i < numCards; i++)
        {
            deck[i]->display();
        }
}
#endif
