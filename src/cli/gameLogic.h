/*!
* @file
* @brief Deklaracia abstraktnych tried popisujucich hernu logiku. Su tu zadefinovane triedy karta, vsetkych kariet, balicku kariet, stackov, radov
*
*
*
*
* @author Daniel Florek, Martin Grnac
*
*/


#pragma once
#include <vector>

class card;
class deckOfCards;
class pileOfCards;
class row;
class stacks;


class card {
protected:
	char cardSymbol;
	int cardNumber;
	bool flipped;
	char color;
public:
	~card() {};
	virtual void setCard(char cardSymbol, int cardNumber) = 0;
	virtual void flipCard() =0;
	virtual char getCardSymbol() = 0;
	virtual int getCardNumber() = 0;
	virtual char getCardColor() = 0;
	virtual bool isFlipped() = 0;
};

class deckOfCards {
public:
	~deckOfCards() {};
};

class pileOfCards {
public:
	virtual void drawCard() = 0;
	virtual int getPileSize() = 0;
};


class finalStacks {
protected:
	char symbol;
public:
	virtual char getStackSymbol() = 0;
	virtual int getStackNumber() = 0;
	virtual void printStack() = 0;
	virtual int getStackSize() = 0;
};

class row {
public:
	~row() {};
	virtual int lastCardNumber() = 0;
	virtual char lastCardColor() = 0;
};
