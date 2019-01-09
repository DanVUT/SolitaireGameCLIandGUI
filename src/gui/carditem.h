/*!
 * @file
 * @brief Subor obsahuje metody pre operacie nad objektom karty
 *
 * @author Martin Grnac
 */

#ifndef CARDITEM_H
#define CARDITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include <QImage>
#include <QString>
#include <QCursor>

#include "deck.h"

class Deck;

class CardItem : public QGraphicsItem
{

public:

    enum { Card = UserType + 1};

    // ZMENA
    enum CardColor{
        Black,
        Red,
        Neutral
    };

    enum CardType{
        Club,
        Diamond,
        Heart,
        Spade,
        Platform
    };

public:
    CardItem();
    ~CardItem();
    CardItem(GraphicsItemFlag flag, QString s, Qt::AspectRatioMode ratio = Qt::IgnoreAspectRatio);

    /**
     * @brief Konstruktor objektu karty
     * @param s - Cesta k obrazku karty
     * @param ratio - Zapnutie/vypnutie ignoracie pomeru stran pri transformacnych operaciach
     * - defaultne je nastavene ignorovanie
     */
    CardItem(QString s, CardColor color = Neutral, CardType type = Platform, int value = 0, Qt::AspectRatioMode ratio = Qt::IgnoreAspectRatio);


    //CardItem(QString s, Qt::AspectRatioMode ratio = Qt::IgnoreAspectRatio);

    /**
     * @brief Pretazena funkcia QGraphicsItem triedy - zadava hranice grafickeho objektu
     * @return Obdlznik znaciaci hranice grafickeho objektu
     */
    QRectF boundingRect() const;

    /**
     * @brief Metoda sa stara o vykreslenie grafickeho objektu
     * @param painter - vykreslovac obrazka
     * @param option - moznosti grafickeho objektu
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief Metoda vracia sirku grafickeho objektu
     * @return Sirka grafickeho objektu
     */
    int getWidth();

    /**
     * @brief Metoda vracia vysku grafickeho objektu
     * @return Vyska grafickeho objektu
     */
    int getHeight();

    /**
     * @brief Pretazena funkcia QGraphicsItem triedy - vracia typ daneho grafickeho objektu
     * v nasom pripade mame len v enumeratore objekt Card - Karta
     * @return Typ objektu
     */
    int type() const;

    /**
     * @brief Prepojenie karty a decku - vieme vytiahnut informaciu v ktorom balicku sa
     * dany graficky objekt karta nachadza
     * @param deck_ptr - Ukazatel na prepojovany balicek
     */
    void setDeck(Deck * deck_ptr);

    /**
     * @brief Metoda vracia ukazatel na balicek v ktorom sa dana karta nachadza
     * @return Ukazatel na balicek
     */
    Deck* getDeck();

    /**
     * @brief Metoda nastavuje viditelnost karty v grafickej scene
     * @param v - true = viditelny , false = neviditelny
     */
    void setCardVisible(bool v);

    /**
     * @brief Metoda obracia kartu chrbtom k hracovi, skryva ju
     * @param image - obrazok pozadia karty
     * @param keep_ratio - zachovanie pomeru stran karty
     */
    void setFlipped(QImage image, bool keep_ratio);

    bool isFlipped();

    /**
     * @brief Nastavenie ukazatela na potomka - potomok je karta pod prave vybranou kartou
     * ak je karta v balicku posledna, nema potomka
     * @param child - Ukazatel na potomka
     */
    void setChild(CardItem *child);

    /**
     * @brief Nastavenie pozicie do ktorej sa bude karta vraciat po nezdarenej interakcii
     * @param pos - Pozicia v ramci sceny
     */
    void setDefaultPos(QPointF pos);

    /**
     * @brief Nastavenie viditelnosti karty do ktorej sa bude vraciat po nezdarenej interakcii
     * @param zval - Viditelnost karty
     */
    void setDefaultZValue(qreal zval);

    /**
     * @brief Vracia poziciu do ktorej sa bude karta vraciat po nezdarenej interakcii
     * @return Pozicia v ramci sceny
     */
    QPointF getDefaultPos();

    /**
     * @brief Vracia viditelnost do ktorej sa bude karta vraciat po nezdarenej interakcii
     * @return Viditelnost karty
     */
    qreal getDefaultZValue();

    /**
     * @brief Vratenie potomka karty
     * @return Ukazatel potomka karty ak karta nema potomka vracia nullptr
     */
    CardItem* getChild();

    /**
     * @brief Nastavenie karty do stavu kedy je pre scenu viditelna tvarou
     */
    void setUnFlipped();

    /**
     * @brief Nastavenie objektu na pohyblivy  - je mozna interakcia s mysou
     * @return Vracia ukazatel na tento objekt pre pokus o vyuzitie navrhoveho vzoru
     * Builder a tak dalej zavolat modifikacne metody ak by sa triede nejake pridali
     */
    CardItem* setMovable();

    /**
     * @brief Vracia informaciu o tom ci je objekt pohyblivy
     * @return true - pohyblivy, false - nepohyblivy
     */
    bool isMovable();

    /**
     * @brief Nastavenie pozicie karty v ramci balicka kariet triedy Deck
     * @param id  -  index karty v balicku
     */
    void setStackId(int id);

    /**
     * @brief Vratenie indexu karty v ramci balicku kariet
     * @return index
     */
    int getStackId();


    //ZMENA
    CardColor getCardColor() {return card_color;}

    CardType getCardType() {return card_type;}

    int getCardValue() {return card_value;}
    //

protected:

    /**
    * @brief Zachytenie udalosti stlacenia tlacidla na mysi nad grafickym objektom
    * @param event
    */
   void mousePressEvent(QGraphicsSceneMouseEvent *event);

   /**
    * @brief Zachytenie udalosti uvolnenia tlacidla mysi nad grafickym objektom
    * @param event
    */
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

   void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);



private:
   QImage img;
   QImage save_img;

   int width;
   int height;
   int StackId;

   Deck* inDeck;
   CardItem * child;

   bool visible;
   bool flipped;
   bool movable;

   // ZMENA
   CardColor card_color;
   CardType card_type;
   int card_value;
   //

   qreal defaultZValue;
   QPointF defaultPos;

};

#endif // CARDITEM_H
