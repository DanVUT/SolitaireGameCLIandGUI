/*!
 * @file
 * @brief Subor obsahuje metody pre operacie nad objektom balicku - deck
 *
 * @author Martin Grnac
 */

#ifndef DECK_H
#define DECK_H

#include <QObject>
#include "carditem.h"

class CardItem;

class Deck: QObject
{

    Q_OBJECT
public:

    /**
     * @brief Enumerator typu balicku - Waste, MainDeck, Foundation, Stack
     */
    enum DeckType{
        Waste,
        MainDeck,
        Foundation,
        Stack
    };

    enum DeckSign{
        Club,
        Diamond,
        Spade,
        Heart,
        None
    };

public:

    /**
     * @brief Konstruktor objektu balicku, trieda je oddedena od QObjektu
     * @param type - typ balicku
     * @param platform - platforma balicku, nesie informacie o pozicii balicku
     * @param parent - rodicovsky objekt balicku
     */
    Deck(DeckType type, CardItem *platform,DeckSign sign = None,QObject *parent = 0);
    ~Deck();

    /**
     * @brief Vracia typ balicku
     * @return typ balicku
     */
    int type();

    /**
     * @brief Pridanie karty do balicku, karte sa nastavi ukazatel na balicek v
     * ktorom sa nachadza, a taktiez aj jej novu poziciu v tomto baliku pre informaciu
     * pre graficku scenu
     * @param card - pridavana karta
     */
    void addCard(CardItem *card);

    /**
     * @brief Nastavenie pozicie platformy balicku
     * @param x - Xova pozicia platformy v scene
     * @param y - Yova pozicia platformy v scene
     */
    void setPlatformPosition(qreal x, qreal y);

    /**
     * @brief Ziskanie platformovej karty balicka
     * @return Ukazatel na platformovu kartu
     */
    CardItem* getPlatformCard();

    /**
     * @brief Zistenie ci je balik prazdny
     * @return true prazdny - false neprazdny
     */
    bool isEmpty();

    /**
     * @brief Odoberie poslednu kartu z balicku a vrati ukazatel na jej objekt
     * @return Ukazatel na odobranu kartu
     */
    CardItem *removeLastCard();

    /**
     * @brief Odoberie prvu kartu z balicku a vrati ukazatel na jej objekt
     * @return Ukazatel na odobranu kartu
     */
    CardItem *removeFirstCard();

    /**
     * @brief Nastavenie indexu balicku
     * @param id - index balicka
     */
    void setDeckId(int id);

    /**
     * @brief Ziskanie indexu balicka
     * @return index balicka
     */
    int getDeckId();

    /**
     * @brief Obnovi viditelnosti vsetkych kariet v balicku, zacinajuc viditelnostou 0.0
     */
    void updateZValues();

    /**
     * @brief Nastavenie odsadenia karat v balicku v grafickej scene
     * @param offset - odsadenie kariet v balicku
     */
    void setDeckOffset(int offset);

    /**
     * @brief Ziskanie odsadenia kariet v balicku
     * @return odsadenie
     */
    int getDeckOffset();

    /**
     * @brief Ziskanie aktualneho poctu kariet v balicku
     * @return pocet kartiet v balicku
     */
    int getDeckSize();

    /**
     * @brief Ziska kartu z balicku na aktualnej pozicii v balicku
     * @param i - index danej karty
     * @return Ukazatel na objekt na danom indexe
     */
    CardItem* getCardFromDeck(int i);

    DeckSign getDeckSign() {return deck_sign;}

    void setDeckSign(DeckSign sign) {deck_sign = sign;}

    CardItem* getLastCard();

private:
    QList<CardItem *> cardStack;
    DeckType deck_type;
    DeckSign deck_sign;
    CardItem *platform_handle;
    int deck_offset;
    int DeckId;

};

#endif // DECK_H
