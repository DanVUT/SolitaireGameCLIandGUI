/*!
* @file
* @brief Subor implementuje foundation stacky
*
*
*
*
* @author Daniel Florek, Martin Grnac
*
*/


#pragma once
#include <iostream>
#include "gameLogic.h"
#include <vector>
#include "card.h"
#include "row.h"
#include <fstream>

class rowCLI;

/**
* @brief Implementacia triedy reprezentujuca foundation stack dedi od abstraktnej triedy
*/
class stacks : public finalStacks {
private:
	/**
	* @brief Vektor kariet reprezentujuci foundation stack
	*/
	std::vector<cardCLI> stack;
	/**
	* @brief Symbol daneho foundation stacku
	*/
	char symbol;
public:
	/**
	* @brief Konstruktor nastavi stacku symbol
	* @param Symbol daneho foundation stacku
	*/
	stacks(char symbol);
	/**
	* @brief Metoda vlozi kartu na koniec stacku
	* @param Karta ktoru chceme vlozit do foundation stacku
	*/
	void cardAppend(cardCLI element);
	/**
	* @brief Presunie kartu spat do hracej plochy
	* @param Rad kam sa ma karta presunut
	*/
	void stackToField(rowCLI &destRow);
	/**
	* @brief ziska velkost stacku
	* @return int velkost foundation stacku
	*/
	int getStackSize();
	/**
	* @brief Vytlaci najvyssiu kartu stacku
	*/
	void printStack();
	/**
	* @brief Ziska cislo poslednej karty
	*/
	int getStackNumber();
	/**
	* @brief Ziska symbol stacku
	*/
	char getStackSymbol();
	/**
	* @brief Ulozi stack do suboru
	* @param Savefile
	*/
	void saveStack(std::ofstream &myfile);
};