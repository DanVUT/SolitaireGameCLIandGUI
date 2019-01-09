#include "deck.h"

Deck::Deck(DeckType type, CardItem* platform, DeckSign sign, QObject *parent)
    : QObject(parent),deck_type(type),platform_handle(platform)
{
   platform->setDeck(this);
   deck_offset = 0;
   DeckId = 0;
   deck_sign = sign;
}

Deck::~Deck()
{
    delete platform_handle;
}

int Deck::type()
{
    return deck_type;
}

void Deck::addCard(CardItem *card)
{
    card->setDeck(this);
    card->setStackId(cardStack.size());

    qreal x = platform_handle->pos().x();
    qreal y = platform_handle->pos().y();

    card->setPos(x,y + deck_offset*cardStack.size());
    card->setDefaultPos(card->pos());

    cardStack.append(card);
}

//Setting platform position
void Deck::setPlatformPosition(qreal x, qreal y)
{
    platform_handle->setPos(x,y);
}

CardItem *Deck::getPlatformCard()
{
    return platform_handle;
}

bool Deck::isEmpty()
{
   return cardStack.empty();
}

CardItem *Deck::removeLastCard()
{
    CardItem *last = cardStack.last();
    cardStack.pop_back();
    return last;
}

CardItem *Deck::removeFirstCard()
{
    CardItem *first = cardStack.first();
    cardStack.pop_front();
    return first;
}

void Deck::setDeckId(int id)
{
    DeckId = id;
}

int Deck::getDeckId()
{
    return DeckId;
}

void Deck::updateZValues()
{
    qreal Zval = 0.0;
    foreach (auto card, cardStack) {
        Zval = Zval + 0.1;
        card->setZValue(Zval);
        card->setDefaultZValue(Zval);
    }
}

void Deck::setDeckOffset(int offset)
{
    deck_offset = offset;
}

int Deck::getDeckOffset()
{
    return deck_offset;
}

int Deck::getDeckSize()
{
    return cardStack.size();
}

CardItem* Deck::getCardFromDeck(int i)
{
    return cardStack[i];
}

CardItem *Deck::getLastCard()
{
    if (!cardStack.empty())
        return cardStack.last();
    else
        return nullptr;
}

