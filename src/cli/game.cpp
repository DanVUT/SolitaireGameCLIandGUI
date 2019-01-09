#include "game.h"
#include "deckOfCards.h"
#include "row.h"
#include "stacks.h"
#include "pileOfCards.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>

int game::menu() {
	std::string answer = "";
	while (answer != "L" && answer != "N" && answer != "E") {
		std::cout << "ZAPNUT NOVU HRU ALEBO NACITAT POSLEDNU ALEBO UKONCIT HRU? N/L/E ";
		std::getline(std::cin, answer);
	}
	if (answer == "E") {
		exit(0);
	}
	if (answer == "N") {
		game_loop();
	}
	if (answer == "L") {
		loaded = true;
		game_loop();
	}
}
int game::is_number(std::string& str){
	if (str.size() == 0) {
		return 0;
	}
	return(strspn(str.c_str(), "0123456789") == str.size());
}

int game::parse(std::string command, char &cardSymbol, int &cardNumber) {
	cardSymbol = command[0];
	std::string tmpNumber;
	if (command.size() >= 3) {
		tmpNumber = command[2];
	}
	if (command.size() == 4) {
		tmpNumber += command[3];
	}
	if (command.size() > 4) {
		return 1;
	}
	if (tmpNumber == "10") {
		cardNumber = 10;
	}
	else if (tmpNumber == "J") {
		cardNumber = 11;
	}
	else if (tmpNumber == "Q") {
		cardNumber = 12;
	}
	else if (tmpNumber == "K") {
		cardNumber = 13;
	}
	else if (tmpNumber == "A") {
		cardNumber = 1;
	}
	else {
		if (tmpNumber[0] >= '2' && tmpNumber[0] <= '9') {
			cardNumber = std::stoi(tmpNumber);
		}
		else {
			return 1;
		}
	}
	return 0;

}

void game::undoAppend(pile undoPile, std::vector<rowCLI> undoRowsVector, std::vector<stacks> undoStacksVector) {
	undoStore tmp;
	tmp.undoPile = undoPile;
	tmp.undoRowsVector = undoRowsVector;
	tmp.undoStacksVector = undoStacksVector;
	if (undoStorage.size() == 5) {
		undoStorage.erase(undoStorage.begin());
	}
	undoStorage.push_back(tmp);

}

void game::undoRestore(pile &Pile, std::vector<rowCLI> &RowsVector, std::vector<stacks> &stacksVector) {
	if (undoStorage.size() == 0) {
		return;
	}
	Pile = undoStorage.back().undoPile;
	RowsVector = undoStorage.back().undoRowsVector;
	stacksVector = undoStorage.back().undoStacksVector;
	undoStorage.pop_back();
}

void game::game_loop() {
	cardsDeck deck;
	pile cardsPile;
	rowCLI row1, row2, row3, row4, row5, row6, row7;
	stacks stack1('c');
	stacks stack2('d');
	stacks stack3('s');
	stacks stack4('h');
	std::vector<stacks> stackVector;
	std::vector<rowCLI> rowsVector;
	stackVector.push_back(stack1);
	stackVector.push_back(stack2);
	stackVector.push_back(stack3);
	stackVector.push_back(stack4);
	rowsVector.push_back(row1);
	rowsVector.push_back(row2);
	rowsVector.push_back(row3);
	rowsVector.push_back(row4);
	rowsVector.push_back(row5);
	rowsVector.push_back(row6);
	rowsVector.push_back(row7);
	if (loaded) {
		std::ifstream myfile;
		myfile.open("savefile");
		if(myfile.good()){
			loadGame(stackVector, rowsVector, cardsPile, myfile);
		}
		else{
			std::cout << "ZIADNA ULOZENA HRA SA NENASLA, VYTVARAM NOVU HRU\n\n";
			deck.dealCards(rowsVector, cardsPile);
		}
	}
	else {
		deck.dealCards(rowsVector, cardsPile);
	}
	while (!isCompleted(stackVector)) {
		cardsPile.printPile();
		std::cout << "\nPILE         WASTE";
		std::cout << "\n --------------------------------------- \n";
		std::cout << "1      2      3     4     5     6     7\n";
		std::cout << "---------------------------------------- \n";

		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 7; j++) {
				rowsVector[j].printElement(i);
				
			}
			std::cout << "\n";
		}
		std::cout << "clubs     diamonds     spades     hearts\n ";
		stackVector[0].printStack();
		if (stackVector[0].getStackSize() == 0) {
			std::cout << "          ";
		}
		else {
			std::cout << "        ";
		}
		stackVector[1].printStack();
		if (stackVector[1].getStackSize() == 0) {
			std::cout << "          ";
		}
		else {
			std::cout << "        ";
		}
		stackVector[2].printStack();
		if (stackVector[2].getStackSize() == 0) {
			std::cout << "          ";
		}
		else {
			std::cout << "        ";
		}
		stackVector[3].printStack();
		std::cout << "\n";

		std::string command = "";
		std::string cardCommand = "";
		std::string srcRowStr;
		std::string dstRowStr;

		std::cout << "1-Pohyb kariet v ramci hracieho pola.\n2-Pohyb Karty z Waste do hracieho pola.\n3-Potiahnutie jednej karty.\n4-Pohyb Karty z hracej plochy do Stackov.\n5-Pohyb karty z waste do stackov.\n6- Pohyb karty zo stacku do pola.\nU- Undo.\nE- Ukonci hru.\n";
		std::cout << "ZADAJ PRIKAZ: ";
		std::getline(std::cin, command);
		if (command == "E") {
			while (command != "Y" && command != "N") {
				std::cout << "CHCES ULOZIT HRU? Y/N ";
				getline(std::cin, command);
			}
			if (command == "N") {
				exit(0);
			}
			else {
				std::ofstream myfile;
				myfile.open("savefile");
				saveGame(stackVector, rowsVector, cardsPile, myfile);
				myfile.close();
				exit(0);
			}
		}
		if (command == "U") {
			undoRestore(cardsPile, rowsVector, stackVector);
			continue;
		}

		if (!this->is_number(command)) {
			std::cout << "INVALID REQUEST\n";
			continue;
		}
		switch (stoi(command))
		{
		case 1:
			undoAppend(cardsPile, rowsVector, stackVector);
			std::cout << "ZADAJ RAD Z KTOREHO CHES BRAT KARTU (1-7): ";
			std::getline(std::cin, srcRowStr);
			std::cout << "ZADAJ KARTU KTORU CHCES PRESUNUT: ";
			std::getline(std::cin, cardCommand);
			std::cout << "ZADAJ RAD DO KTOREHO CHCES PRESUNUT KARTU (1-7): ";
			std::getline(std::cin, dstRowStr);
			if (this->is_number(srcRowStr)) {
				if (stoi(srcRowStr) < 1 || stoi(srcRowStr) > 7) {
					std::cout << "INVALID REQUEST\n";
					continue;
				}
			}
			else {
				std::cout << "INVALID REQUEST\n";
				continue;
			}
			if (this->is_number(dstRowStr)) {
				if (stoi(dstRowStr) < 1 || stoi(dstRowStr) > 7) {
					std::cout << "INVALID REQUEST\n";
					continue;
				}
			}
			else {
				std::cout << "INVALID REQUEST\n";
				continue;
			}
			if (cardCommand.size() != 3 && cardCommand.size() != 4) {
				std::cout << "INVALID REQUEST\n";
				continue;
			}
			int cardNumber;
			char cardSymbol;
			if (this->parse(cardCommand, cardSymbol, cardNumber) != 0) {
				std::cout << "INVALID REQUEST\n";
				continue;
			}
			rowsVector[stoi(srcRowStr) - 1].moveCards(cardSymbol, cardNumber, rowsVector[stoi(dstRowStr) - 1]);
			break;
		case 2:
			undoAppend(cardsPile, rowsVector, stackVector);
			std::cout << "ZADAJ RAD DO KTOREHO CHCES KARTU PRESUNUT(1-7): ";
			std::getline(std::cin, dstRowStr);
			if (this->is_number(dstRowStr)) {
				if (stoi(dstRowStr) < 1 || stoi(dstRowStr) > 7) {
					std::cout << "INVALID REQUEST\n";
					continue;
				}
			}
			else {
				std::cout << "INVALID REQUEST\n";
				continue;
			}
			cardsPile.pileToField(rowsVector[stoi(dstRowStr) - 1]);
			break;
		case 3:
			undoAppend(cardsPile, rowsVector, stackVector);
			cardsPile.drawCard();
			break;
		case 4:
			undoAppend(cardsPile, rowsVector, stackVector);
			std::cout << "ZADAJ RAD Z KTOREHO CHCES PRENASAT DO STACKU(1-7): ";
			std::getline(std::cin, srcRowStr);
			if (this->is_number(srcRowStr)) {
				if (stoi(srcRowStr) < 1 || stoi(srcRowStr) > 7) {
					std::cout << "INVALID REQUEST\n";
					continue;
				}
			}
			else {
				std::cout << "INVALID REQUEST\n";
				continue;
			}
			rowsVector[stoi(srcRowStr) - 1].rowToStack(stackVector);
			break;
		case 5:
			undoAppend(cardsPile, rowsVector, stackVector);
			cardsPile.pileToStack(stackVector);
			break;
		case 6:
			undoAppend(cardsPile, rowsVector, stackVector);
			std::cout << "ZADAJ FARBU Z KTOREJ CHCES TAHAT (c, d, h, s): ";
			std::getline(std::cin, srcRowStr);
			if (srcRowStr != "c" && srcRowStr != "d" && srcRowStr != "h" && srcRowStr != "s") {
				std::cout << "INVALID REQUEST\n";
				continue;
			}
			std::cout << "ZADAJ RAD DO KTOREHO CHCES UKLADAT (1-7): ";
			std::getline(std::cin, dstRowStr);
			if (this->is_number(dstRowStr)) {
				if (stoi(dstRowStr) < 1 || stoi(dstRowStr) > 7) {
					std::cout << "INVALID REQUEST\n";
					continue;
				}
			}
			else {
				std::cout << "INVALID REQUEST\n";
				continue;
			}
			for (int i = 0; i < 4; i++) {
				if (stackVector[i].getStackSymbol() == srcRowStr[0]) {
					stackVector[i].stackToField(rowsVector[stoi(dstRowStr) - 1]);
				}
			}

		}

		std::cout << std::string(100, '\n');

	}
	std::cout << "GRATULUJEM UKONCIL SI HRU\n";
}

void game::saveGame(std::vector<stacks> &stackVector, std::vector<rowCLI> &rowsVector, pile &cardsPile, std::ofstream &myfile) {
	cardsPile.savePile(myfile);
	for (int i = 0; i < rowsVector.size(); i++) {
		rowsVector[i].saveRow(myfile);
	}
	for (int i = 0; i < stackVector.size(); i++) {
		stackVector[i].saveStack(myfile);
		if (i != stackVector.size() - 1) {
			myfile << "\n";
		}
	}
}

bool game::isCompleted(std::vector<stacks> &stackVector) {
	return (stackVector[0].getStackSize() == 13 && stackVector[1].getStackSize() == 13 && stackVector[2].getStackSize() == 13 && stackVector[3].getStackSize() == 13);
}

void game::loadGame(std::vector<stacks> &stackVector, std::vector<rowCLI>& rowsVector, pile &cardsPile, std::ifstream &myfile) {
	std::string pile = "";
	std::string waste = "";
	std::string row1(""), row2(""), row3(""), row4(""), row5(""), row6(""), row7("");
	std::string stack1(""), stack2(""), stack3(""), stack4("");
	cardCLI tmp;
	std::string tmpStr = "";
	std::string boolStr = "";
	int index = 0;
	char cardSymbol;
	std::string cardNumberStr;
	std::getline(myfile, pile);
	std::getline(myfile, waste);
	std::getline(myfile, row1);
	std::getline(myfile, row2);
	std::getline(myfile, row3);
	std::getline(myfile, row4);
	std::getline(myfile, row5);
	std::getline(myfile, row6);
	std::getline(myfile, row7);
	std::getline(myfile, stack1);
	std::getline(myfile, stack2);
	std::getline(myfile, stack3);
	std::getline(myfile, stack4);
	
    //std::cout <<  waste;
	
	
	while (index < pile.size() && pile.size() > 1)
	{
		cardSymbol = pile[index];
		index += 2;
		while (pile[index] != ' ') {
			cardNumberStr += pile[index++];
		}
		index++;
		boolStr = pile[index];
		index += 2;
		tmp.setCard(cardSymbol, stoi(cardNumberStr), stoi (boolStr));
		cardsPile.cardAppend(tmp);
		cardNumberStr = "";
		boolStr = "";
	}
	index = 0;
	while (index < waste.size() && waste.size() > 1 )
	{
		cardSymbol = waste[index];
		index += 2;
		while (waste[index] != ' ') {
			cardNumberStr += waste[index++];
		}
		index++;
		boolStr = waste[index];
		index += 2;
		tmp.setCard(cardSymbol, stoi(cardNumberStr), stoi(boolStr));
		cardsPile.wasteAppend(tmp);
		cardNumberStr = "";
		boolStr = "";
	}
	index = 0;
	while (index < row1.size() && row1.size() > 1)
	{
		cardSymbol = row1[index];
		index += 2;
		while (row1[index] != ' ') {
			cardNumberStr += row1[index++];
		}
		index++;
		boolStr = row1[index];
		index += 2;
		tmp.setCard(cardSymbol, stoi(cardNumberStr), stoi(boolStr));
		rowsVector[0].cardAppend(tmp);
		cardNumberStr = "";
		boolStr = "";
	}
	
	index = 0;
	while (index < row2.size() && row2.size() > 1)
	{
		cardSymbol = row2[index];
		index += 2;
		while (row2[index] != ' ') {
			cardNumberStr += row2[index++];
		}
		index++;
		boolStr = row2[index];
		index += 2;
		tmp.setCard(cardSymbol, stoi(cardNumberStr), stoi(boolStr));
		rowsVector[1].cardAppend(tmp);
		cardNumberStr = "";
		boolStr = "";
	}
	index = 0;
	while (index < row3.size() && row3.size() > 1)
	{
		cardSymbol = row3[index];
		index += 2;
		while (row3[index] != ' ') {
			cardNumberStr += row3[index++];
		}
		index++;
		boolStr = row3[index];
		index += 2;
		tmp.setCard(cardSymbol, stoi(cardNumberStr), stoi(boolStr));
		rowsVector[2].cardAppend(tmp);
		cardNumberStr = "";
		boolStr = "";
	}
	index = 0;
	while (index < row4.size() && row4.size() > 1)
	{
		cardSymbol = row4[index];
		index += 2;
		while (row4[index] != ' ') {
			cardNumberStr += row4[index++];
		}
		index++;
		boolStr = row4[index];
		index += 2;
		tmp.setCard(cardSymbol, stoi(cardNumberStr), stoi(boolStr));
		rowsVector[3].cardAppend(tmp);
		cardNumberStr = "";
		boolStr = "";
	}
	index = 0;
	while (index < row5.size() && row5.size() > 1)
	{
		cardSymbol = row5[index];
		index += 2;
		while (row5[index] != ' ') {
			cardNumberStr += row5[index++];
		}
		index++;
		boolStr = row5[index];
		index += 2;
		tmp.setCard(cardSymbol, stoi(cardNumberStr), stoi(boolStr));
		rowsVector[4].cardAppend(tmp);
		cardNumberStr = "";
		boolStr = "";
	}
	index = 0;
	while (index < row6.size() && row6.size() > 1)
	{
		cardSymbol = row6[index];
		index += 2;
		while (row6[index] != ' ') {
			cardNumberStr += row6[index++];
		}
		index++;
		boolStr = row6[index];
		index += 2;
		tmp.setCard(cardSymbol, stoi(cardNumberStr), stoi(boolStr));
		rowsVector[5].cardAppend(tmp);
		cardNumberStr = "";
		boolStr = "";
	}
	index = 0;
	while (index < row7.size() && row7.size() > 1)
	{
		cardSymbol = row7[index];
		index += 2;
		while (row7[index] != ' ') {
			cardNumberStr += row7[index++];
		}
		index++;
		boolStr = row7[index];
		index += 2;
		tmp.setCard(cardSymbol, stoi(cardNumberStr), stoi(boolStr));
		rowsVector[6].cardAppend(tmp);
		cardNumberStr = "";
		boolStr = "";
	}
	index = 0;
	
	
	while (index < stack1.size() && stack1.size() > 1)
	{
		cardSymbol = stack1[index];
		index += 2;
		while (stack1[index] != ' ') {
			cardNumberStr += stack1[index++];
		}
		index++;
		boolStr = stack1[index];
		index += 2;
		tmp.setCard(cardSymbol, stoi(cardNumberStr), stoi(boolStr));
		stackVector[0].cardAppend(tmp);
		cardNumberStr = "";
		boolStr = "";
	}
	index = 0;
	while (index < stack2.size() && stack2.size() > 1)
	{
		
		cardSymbol = stack2[index];
		index += 2;
		while (stack2[index] != ' ') {
			cardNumberStr += stack2[index++];
		}
		index++;
		boolStr = stack2[index];
		index += 2;
		tmp.setCard(cardSymbol, stoi(cardNumberStr), stoi(boolStr));
		stackVector[1].cardAppend(tmp);
		cardNumberStr = "";
		boolStr = "";
	}
	index = 0;
	
	while (index < stack3.size() && stack3.size() > 1)
	{
		cardSymbol = stack3[index];
		index += 2;
		while (stack3[index] != ' ') {
			cardNumberStr += stack3[index++];
		}
		index++;
		boolStr = stack3[index];
		index += 2;
		tmp.setCard(cardSymbol, stoi(cardNumberStr), stoi(boolStr));
		stackVector[2].cardAppend(tmp);
		cardNumberStr = "";
		boolStr = "";
	}
	index = 0;
	while (index < stack4.size() && stack4.size() > 1)
	{
		cardSymbol = stack4[index];
		index += 2;
		while (stack4[index] != ' ') {
			cardNumberStr += stack4[index++];
		}
		index++;
		boolStr = stack4[index];
		index += 2;
		tmp.setCard(cardSymbol, stoi(cardNumberStr), stoi(boolStr));
		stackVector[3].cardAppend(tmp);
		cardNumberStr = "";
		boolStr = "";
	}
	
}
