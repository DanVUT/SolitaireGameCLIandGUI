#include "card.h"
#include <iostream>
#include <string>

void cardCLI::setCard(char cardSymbol, int cardNumber) {
	this->cardNumber = cardNumber;
	this->cardSymbol = cardSymbol;
	this->flipped = false;
	if (cardSymbol == 'd' || cardSymbol == 'h') {
		this->color = 'r';
	}
	else {
		this->color = 'b';
	}
}

void cardCLI::setCard(char cardSymbol, int cardNumber, bool flipped) {
	this->cardNumber = cardNumber;
	this->cardSymbol = cardSymbol;
	this->flipped = flipped;
	if (cardSymbol == 'd' || cardSymbol == 'h') {
		this->color = 'r';
	}
	else {
		this->color = 'b';
	}
}
char cardCLI::getCardColor() {
	return this->color;
}

void cardCLI::flipCard() {
	this->flipped = !this->flipped;
}

char cardCLI::getCardSymbol() {
	return this->cardSymbol;
}

int cardCLI::getCardNumber() {
	return this->cardNumber;
}

bool cardCLI::isFlipped() {
	return this->flipped;
}

void cardCLI::printCard() {
	std::string tmpChar;
	switch (this->cardNumber)
	{
	case 1:
		tmpChar = 'A';
		break;
	case 11:
		tmpChar = 'J';
		break;
	case 12:
		tmpChar = 'Q';
		break;
	case 13:
		tmpChar = 'K';
		break;
	default:
		tmpChar = std::to_string(this->cardNumber);
		break;
	}
	if (isFlipped()) {
		std::cout << this->cardSymbol << "(" << tmpChar << ")";
	}
	else {
		std::cout << "-(-)";
	}
}