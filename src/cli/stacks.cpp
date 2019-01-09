#include "stacks.h"
#include <vector>
#include <iostream>
#include <fstream>

stacks::stacks(char symbol) {
	this->symbol = symbol;
}

void stacks::cardAppend(cardCLI element) {
	stack.push_back(element);
}

void stacks::stackToField(rowCLI &destRow) {
	if (stack.size() > 0) {
		if (stack.back().getCardColor() != destRow.lastCardColor()) {
			if (stack.back().getCardNumber() + 1 == destRow.lastCardNumber()) {
				destRow.cardAppend(stack.back());
				stack.pop_back();
				return;
			}
		}
	}
	std::cout << "INVALID REQUEST\n";
	return;
}
int stacks::getStackSize() {
	return stack.size();
}
void stacks::printStack() {
	if (stack.size() > 0) {
		stack.back().printCard();
	}
	else {
		std::cout << "00";
	}
}
char stacks::getStackSymbol() {
	return this->symbol;
}

int stacks::getStackNumber() {
	if (stack.size() > 0) {
		return stack.back().getCardNumber();
	}
	else {
		return 0;
	}
}

void stacks::saveStack(std::ofstream &myfile) {
	for (int i = 0; i < stack.size(); i++) {
		myfile << stack[i].getCardSymbol() << " " << stack[i].getCardNumber() << " "  << stack[i].isFlipped();
		if (i != stack.size() - 1) {
			myfile << " ";
		}
	}
}