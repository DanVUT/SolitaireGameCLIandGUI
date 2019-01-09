#include "row.h"
#include "card.h"
#include <iostream>
#include <fstream>

void rowCLI::cardAppend(cardCLI element) {
	cardsRow.push_back(element);
}

int rowCLI::lastCardNumber() {
	if (cardsRow.size() > 0) {
		return cardsRow.back().getCardNumber();
	}
	else {
		return 14;
	}
}

char rowCLI::lastCardColor() {
	if (cardsRow.size() > 0) {
		return cardsRow.back().getCardColor();
	}
	else {
		return 'n';
	}
}

char rowCLI::lastCardSymbol() {
	return cardsRow.back().getCardSymbol();
}

void rowCLI::printRow() {
	for (int i = 0; i < cardsRow.size(); i++) {
		cardsRow[i].printCard();
	}
}

void rowCLI::printElement(int index) {
	if (index < cardsRow.size()) {
		cardsRow[index].printCard();
		if (cardsRow[index].getCardNumber() != 10 || !cardsRow[index].isFlipped()) {
			std::cout << "  ";
		}
		else {
			std::cout << " ";
		}
	}
	else {
		std::cout << "--    ";
	}
}


void rowCLI::moveCards(char cardSymbol, int cardNumber, rowCLI &destRow) {
	for (int i = 0; i < cardsRow.size(); i++) {
		if (cardsRow[i].getCardNumber() == cardNumber) {
			if (cardsRow[i].getCardSymbol() == cardSymbol) {
				if (cardsRow[i].getCardColor() != destRow.lastCardColor() ) {
					if (cardsRow[i].getCardNumber() + 1 == destRow.lastCardNumber()) {
						for (int j = i; j < cardsRow.size(); j++) {
							destRow.cardAppend(cardsRow[j]);
						}
						cardsRow.erase(cardsRow.begin() + i, cardsRow.end());
						if (cardsRow.size() > 0) {
							if (!cardsRow.back().isFlipped()) {
								cardsRow.back().flipCard();
							}
						}
						return;
					}
				}
			}
		}
	}
	std::cout << "INVALID MOVE\n";
	return;
}

void rowCLI::rowToStack(std::vector<stacks> &stackVector) {
	if (cardsRow.size() > 0) {
		for (int i = 0; i < stackVector.size(); i++) {
			if (stackVector[i].getStackSymbol() == cardsRow.back().getCardSymbol()) {
				if (stackVector[i].getStackNumber() + 1 == cardsRow.back().getCardNumber()) {
					stackVector[i].cardAppend(cardsRow.back());
					cardsRow.pop_back();
					if (cardsRow.size() > 0) {
						if (!cardsRow.back().isFlipped()) {
							cardsRow.back().flipCard();
						}
					}
					return;
				}
			}
		}
	}
	std::cout << "INVALID REQUEST\n";
	return;
}

void rowCLI::saveRow(std::ofstream &myfile) {
	for (int i = 0; i < cardsRow.size(); i++) {
		myfile << cardsRow[i].getCardSymbol() << " " << cardsRow[i].getCardNumber() << " " << cardsRow[i].isFlipped();
		if (i != cardsRow.size() - 1) {
			myfile << " ";
		}
	}
	myfile << "\n";
}