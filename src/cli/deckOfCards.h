/*!
* @file
* @brief Implementacia triedy reprezentujuca vsetky karty
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
#include "row.h"
#include "pileOfCards.h"


/**
* @brief Trieda implementujuca metody implementujuca vsetky karty
*/
class cardsDeck : public deckOfCards {
private:
	/**
	* @brief vektor obsahujuci vsetky karty
	*/
	std::vector<cardCLI> deck;
public:
	/**
	* @brief Konstruktor, ktory vygeneruje vsetky karty
	*/
	cardsDeck();
	/**
	* @brief rozda karty do balicku a radov
	* @param Vektor vsetkych  radov 
	* @param Balik kariet
	*/
	void dealCards(std::vector<rowCLI> &rowsVector, pile &cardsPile);
};
