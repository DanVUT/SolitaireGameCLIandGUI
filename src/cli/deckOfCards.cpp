#include "card.h"
#include "deckOfCards.h"
#include "pileOfCards.h"
#include <time.h>
#include "row.h"

cardsDeck::cardsDeck(){
	int index = 0;
	cardCLI tmp;
	char symbols[] = { 'c' , 'd', 'h', 's' };
	int numbers[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			tmp.setCard(symbols[i], numbers[j]);
			deck.push_back(tmp);
		}
	}

	for (int i = 0; i < 52; i++) {
		int index = (rand() + time(0)) % 52;
		cardCLI tmpCard;
		tmpCard = deck[i];
		deck[i] = deck[index];
		deck[index] = tmpCard;
	}
}

void cardsDeck::dealCards(std::vector<rowCLI> &rowsVector, pile &cardsPile) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == i) {
				deck.back().flipCard();
			}
			rowsVector[i].cardAppend(deck.back());
			deck.pop_back();
		}
	}
	int size = deck.size();
	for (int i = 0; i < size; i++) {
		cardsPile.cardAppend(deck.back());
		deck.pop_back();
	}
}