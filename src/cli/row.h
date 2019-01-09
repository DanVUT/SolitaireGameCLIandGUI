/*!
* @file
* @brief Subor implementuje rad kariet
*
*
*
*
* @author Daniel Florek, Martin Grnac
*
*/



#pragma once
#include "gameLogic.h"
#include "card.h"
#include "stacks.h"

/**
* @brief Implementacia triedy reprezentujuca rad v solitairi dediaca od abstraktnej  triedy row
*/
class rowCLI : public row {
private:
	/**
	* @brief Rad kariet
	*/
	std::vector<cardCLI> cardsRow;
public:
	/**
	* @brief Prida kartu do radu
	* @param Karta ktoru chceme pridat
	*/
	void cardAppend(cardCLI element);
	/**
	* @brief Pohne karty na vrchu so zadanou kartou do destinacneho radu
	* @param Symbol karty ktoru chceme pohnut
	* @param Cislo karty ktoru chceme pohnut
	* @param Rad destinacie kam chceme kartu pohnut
	*/
	void moveCards(char cardSymbol, int cardNumber, rowCLI &destRow);
	/**
	* @brief Ziska cislo poslendej karty v rade
	* @return int hodnota poslednej karty v rade
	*/
	int lastCardNumber();
	/**
	* @brief Ziska farbu poslednej karty v rade
	* @return char hodnota farby poslednej karty v rade
	*/
	char lastCardColor();
	/**
	* @brief Ziska symbol poslednej karty
	* @return char hodnota symbolu poslednej karty
	*/
	char lastCardSymbol();
	/**
	* @brief zoberie poslednú kartu z radu a prida ju do stacku
	* @param vector stackov ktory sa bude prehladavat kym sa nenajde pozadovany znak
	*/
	void rowToStack(std::vector<stacks> &stacksVector);
	/**
	* @brief Vypise karty v rade
	*/
	void printRow();
	/**
	* @brief Vytlaci jednu kartu v danom poradi
	* @param Index v rade kariet 
	*/
	void printElement(int index);
	/**
	* @brief Ulozi rad do suboru
	* @param Savefile do ktoreho sa ulozia data
	*/
	void saveRow(std::ofstream &myfile);
};