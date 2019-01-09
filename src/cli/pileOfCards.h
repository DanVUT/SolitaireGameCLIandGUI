/*!
* @file
* @brief Subor implementuje triedu reprezentujucu pile a waste
*
*
*
*
* @author Daniel Florek, Martin Grnac
*
*/

#pragma once
#include "gameLogic.h"
#include <vector>
#include "card.h"
#include "row.h"
/**
* @brief Implementacia triedy reprezentujuca Pile a Waste
*/
class pile : public pileOfCards {
private:
	/**
	* @brief vektor obsahujuci kopku kariet
	*/
	std::vector<cardCLI> cardsPile;
	/**
	* @brief vektor obsahujuci waste kariet
	*/
	std::vector<cardCLI> cardsWaste;
public:
	/**
	* @brief Metoda prida do balicku kartu
	* @param Karta ktora sa prida do pile
	*/
	void cardAppend(cardCLI element);
	/**
	* @brief Metoda prida do waste pouziva sa pri nacitani hry
	* @param Karta ktora sa prida do waste
	*/
	void wasteAppend(cardCLI element);
	/**
	* @brief Metoda vytiahne kartu z balicku do waste
	*/
	void drawCard() ;
	/**
	* @brief Metoda vrati velkost pile
	* @return int hodnota velkosti balicku
	*/
	int getPileSize();
	/**
	* @brief Vypise hodnoty balicku a waste
	*/
	void printPile();
	/**
	* @brief Presunie kartu z Waste do pola
	* @param rad do ktoreho sa prenesie karta
	*/
	void pileToField(rowCLI &destRow);
	/**
	* @brief Presunie kartu z Waste do stacku
	* @param Vektor stackov ktory sa preiteruje aby sa nasiel pozadovany znak
	*/
	void pileToStack(std::vector<stacks> &stack);
	/**
	* @brief uloží pile do suboru
	* @param Savefile do ktoreho sa ulozi stav balicku
	*/
	void savePile(std::ofstream &myfile);
};