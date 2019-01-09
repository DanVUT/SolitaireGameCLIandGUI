/*!
 * @file
 * @brief Subor obsahuje metody pre operacie nad objektom hernej sceny
 *
 * @author Martin Grnac
 */


#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QRgb>
#include <QDebug>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>
#include "carditem.h"
#include <QFile>

#define SOLITAIRE_GREEN qRgb(0,102,51)
#define SCENE_WIDTH 1024
#define SCENE_HEIGHT 768

#define OFFSET_WASTE 50
#define FOUNDATION_OFFSET 420
#define STACK_OFFSET 20

class GameScene: public QGraphicsScene
{
    Q_OBJECT
public:

    /**
     * @brief Konstruktor objektu. Tato trieda je oddedena od QGraphicsScene
     * @param parent - ukazatel na rodicovsky objekt
     */
    GameScene(QObject *parent=0);

    ~GameScene();

    /**
     * @brief Metoda nastavuje prvky hernej sceny, farbu pozadia, velkost sceny
     * a vola nacitanie kariet a nasledne rozdelenie keriet do balikov a ich umiestnenie
     * v scene
     */
    void setSolitaireScene(QFile *save_file);

    /**
     * @brief Metoda zalohuje aktualnu poziciu karty a hodnotu jej viditelnosti v scene
     * @param card - ukazatel na zalohovanu kartu
     */
    void saveCardData(CardItem * card);

    /**
     * @brief Sirka karty v scene
     * @return Sirka karty
     */
    int getCardWidth();

    /**
     * @brief Vyska karty v scene
     * @return Vyska karty
     */
    int getCardHeight();

    /**
     * @brief Najdenie navacsej hodnoty viditelnosti grafickeho objektu v scene
     * @return Hodnota viditelnosti objektu
     */
    qreal findMaxZvalue();

    /**
     * @brief Obnovenie zalohovanych dat karty
     * @param card - obnovovana karta
     */
    void restoreCardParams(CardItem *card);

    /**
     * @brief Metoda zistuje ci sa premiestnovana karta kryje s nejakymi kartami z ineho
     * baliku
     * @param colliding_list - zoznam kolidujucich sa objektov
     * @param pressed - vybrana/presuvana karta alebo rad kariet
     * @return Vracia sa ukazatel na povodne vybranu kartu alebo ak sa najde karta z
     * ineho baliku medzi klidujucimi objektami tak je vratena tato karta
     */
    CardItem *collidingDeck(QList<QGraphicsItem *> colliding_list, CardItem *pressed);

    /**
     * @brief Nacitavanie kartie, priradovanie obrazkov a miesanie kariet
     */
    void loadCards(QFile *savefile);


    /**
     * @brief Zamiesane karty
     */
    QVector<CardItem*> mixed_cards;

    /**
     * @brief Vsetky karty v hre - zoznam sa pouziva pre uvolnovanie objektov pri destrukcii
     * sceny
     */
    QVector<CardItem*> all_cards;


    bool try_move(CardItem* to, CardItem *from);


    void save_to_file(QString path);

    QString write_card_to_file(CardItem * card);

    CardItem* findCard(QString sign, int value);


protected:

    /**
     * @brief Zachytenie udalosti stlacenia tlacidla na mysi
     * @param event - zachytena udalost
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief Zachytenie udalosti pustenia tlacidla na mysi
     * @param event - zachytena udalost
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief Zachytenie udalosti pohybu mysi po scene
     * @param event - zachytena udalost
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    bool Pressed;

    Deck* main_deck;
    Deck* waste_deck;

    QVector<Deck*> foundation_decks;
    QVector<Deck*> stacks;

    QImage platform_img;
    QImage background_img;

    QGraphicsItem * current_item;
    CardItem* test_card;

    int CardWidth;
    int CardHeight;


};

#endif // GAMESCENE_H
