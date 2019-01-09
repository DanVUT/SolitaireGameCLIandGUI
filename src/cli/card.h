/*!
* @file
* @brief Implementacia triedy reprezentujuca kartu
*
* 
* 
*
* @author Daniel Florek, Martin Grnac
*
*/


#pragma once
#include "gameLogic.h"
/**
* @brief Trieda implementujuca metody karty upravena pre potreby CLI dediaca od vseobecnej triedy karta
*/
class cardCLI : public card {
public:
	/**
	* @brief Nastavi atributy karty, atribut flipped sa nastavi automaticky na false
	*
	* @param char cardSymbol
	* @param int cardNumber
	*/
	 void setCard(char cardSymbol, int cardNumber);
	 /**
	 * @brief Nastavi atributy karty, atribut flipped sa nastavi podla toho ako je ulozeny v savefile. Vyuziva sa pri nacitani ulozenej hry
	 *
	 * @param char cardSymbol
	 * @param int cardNumber
	 * @param bool flipped
	 */
	 void setCard(char cardSymbol, int cardNumber, bool flipped);
	 /**
	 * @brief Metoda otoci kartu
	 */
	 void flipCard();
	 /**
	 * @brief Metoda ziska hodnotu symbolu karty
	 * @return char hodnota symbolu karty
	 */
	 char getCardSymbol();
	 /**
	 * @brief Metoda ziska hodnotu cisla karty
	 * @return int hodnota cisla karty
	 */
	 int getCardNumber();
	 /**
	 * @brief Metoda ziska farbu karty
	 * @return char hodnota farby karty
	 */
	 char getCardColor();
	 /**
	 * @brief Metoda otoci kartu
	 * @return bool zisti sa ci je karta otocena alebo nie
	 */
	 bool isFlipped();
	 /**
	 * @brief vypise hodnoty karty
	 */
	 void printCard();
};