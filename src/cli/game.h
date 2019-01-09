/*!
* @file
* @brief Subor implementuje herne mechanizmy
*
*
*
*
* @author Daniel Florek, Martin Grnac
*
*/


#pragma once
#include <string>
#include <fstream>
#include "gameLogic.h"
#include "card.h"
#include "deckOfCards.h"
#include "row.h"
#include "pileOfCards.h"
#include "stacks.h"
#include "game.h"


/**
* @brief Trieda implementujuca herne mechanizmy
*/
class game {
public:
	/**
		* @brief Struktura obsahujuca zalohu jednotlivych radov kariet v hernej ploche
	*/
	struct undoStore{
		/**
			* @brief Zaloha baliku kariet
		*/
		pile undoPile;
		/**
			* @brief Zaloha radov
		*/
		std::vector<rowCLI> undoRowsVector;
		/**
			* @brief Zaloha foundation stackov
		*/
		std::vector<stacks> undoStacksVector;

		
	};
	
	
	/**
		* @brief Metoda ponuka vyber zacat novu hru, nacitat hru alebo ukoncit hru
	*/
	int menu();
	/**
		* @brief metoda implementujuca herny loop kedy sa nacitavaju informacie zo vstupu a vykonavaju sa ak su validne
	*/
	void game_loop();
	/**
		* @brief Pomocna interna funkcia na zistovanie validacie prikazov
	*/
	int is_number(std::string& str);
	/**
		* @brief Pomocna interna funkcia ktora rozkuskuje prikaz
	*/
	int parse(std::string command, char &cardSymbol, int &cardNumber);
	/**
		@brief Funkcia ulozi stav hry do suboru
		@param foundation stack vector
		@param vector radov
		@param balik kariet
		@param savefile
	*/
	void saveGame(std::vector<stacks> &stackVector, std::vector<rowCLI>& rowsVector, pile &cardsPile, std::ofstream &myfile);
	/**
		@brief Funkcia nacita poslednu ulozenu hru
		@param foundation stack vector
		@param vector radov
		@param balik kariet
		@param savefile
	*/
	void loadGame(std::vector<stacks> &stackVector, std::vector<rowCLI>& rowsVector, pile &cardsPile, std::ifstream &myfile);
	/**
		@brief Funkcia uschova stav hry pre pripadnu undo operaciu
		@param balik kariet
		@param vektor radov
		@param vektor foundation stackov
	*/
	void undoAppend(pile undoPile, std::vector<rowCLI> undoRowsVector, std::vector<stacks> undoStacksVector);
		/**
		@brief Funkcia nahra predchadzajuci stav hry
		@param balik kariet
		@param foundation stack vector
		@param vector radov
	*/
	void undoRestore(pile &Pile, std::vector<rowCLI> &RowsVector, std::vector<stacks> &stacksVector);
	/**
		@brief Funkcia ulozi stav hry do suboru
		@param foundation stack vector
		@return vracia bool hodnotu na zaklade toho ci vsetky foundation stacky su plne alebo nie
	*/
	bool isCompleted(std::vector<stacks> &stackVector);
private:
	bool loaded = false;
	std::vector<undoStore> undoStorage;


};