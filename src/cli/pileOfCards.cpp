#include "card.h"
#include "pileOfCards.h"
#include <iostream>
#include <fstream>
#include "stacks.h"

void pile::cardAppend(cardCLI element) {
	cardsPile.push_back(element);
}
void pile::wasteAppend(cardCLI element) {
	cardsWaste.push_back(element);
}
void pile::printPile() {
	if (cardsPile.size() > 0) {
		std::cout << "==           ";
	}
	else {
		std::cout << "00           ";
	}
	if (cardsWaste.size() > 0) {
		cardsWaste.back().printCard();
	}
	else {
		std::cout << "--";
	}
}
void pile::drawCard() {
	if (cardsPile.size() == 0 && cardsWaste.size() == 0) {

	}
	if (cardsPile.size() != 0) {
		cardsWaste.push_back(cardsPile.back());
		cardsWaste.back().flipCard();
		cardsPile.pop_back();
	}
	else {
		while (cardsWaste.size()) {
			cardsPile.push_back(cardsWaste.back());
			cardsPile.back().flipCard();
			cardsWaste.pop_back();
		}
	}
}

int pile::getPileSize() {
	return cardsPile.size();
}

void pile::pileToField(rowCLI &destRow) {
	if (cardsWaste.size() > 0) {
		if (destRow.lastCardColor() != cardsWaste.back().getCardColor()) {
			if (destRow.lastCardNumber() == cardsWaste.back().getCardNumber() + 1) {
				destRow.cardAppend(cardsWaste.back());
				cardsWaste.pop_back();
				return;
			}
		}
	}
	std::cout << "INVALID REQUEST\n";
	return;

}

void pile::pileToStack(std::vector<stacks> &stackVector) {
	if (cardsWaste.size() > 0) {
		for (int i = 0; i < stackVector.size(); i++) {
			if (stackVector[i].getStackSymbol() == cardsWaste.back().getCardSymbol()) {
				if (stackVector[i].getStackNumber() + 1 == cardsWaste.back().getCardNumber()) {
					stackVector[i].cardAppend(cardsWaste.back());
					cardsWaste.pop_back();
					return;
				}
			}
		}
	}
	std::cout << "INVALID REQUEST\n";
	return;
}

void pile::savePile(std::ofstream &myfile) {
	for (int i = 0; i < cardsPile.size(); i++){
		myfile << cardsPile[i].getCardSymbol() << " " << cardsPile[i].getCardNumber() << " " << cardsPile[i].isFlipped();
		if (i != cardsPile.size() - 1) {
			myfile<< " ";
		}
	}
	myfile << "\n";
	for (int i = 0; i < cardsWaste.size(); i++) {
		myfile << cardsWaste[i].getCardSymbol() << " " << cardsWaste[i].getCardNumber() << " " << cardsWaste[i].isFlipped();
		if (i != cardsWaste.size() - 1) {
			myfile << " ";
		}
	}
	myfile << "\n";
}