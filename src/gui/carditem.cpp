#include "carditem.h"

CardItem::~CardItem()
{

}

CardItem::CardItem()
{
    inDeck = nullptr;
    child = nullptr;
}

CardItem::CardItem(QString s, CardColor color, CardType type, int value,Qt::AspectRatioMode ratio)
{
    inDeck = nullptr;
    child = nullptr;
    movable = false;
    flipped = false;
    img = QImage(s);
    img = img.scaled(75,110,ratio);
    width = img.width();
    height = img.height();

    card_color = color;
    card_value = value;
    card_type = type;
}


QRectF CardItem::boundingRect() const
{
    return QRectF(0,0,img.width(),img.height());
}


void CardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    painter->drawImage(rect,img);
}


int CardItem::getWidth()
{
    return width;
}


int CardItem::getHeight()
{
    return height;
}


int CardItem::type() const
{
    return Card;
}

void CardItem::setDeck(Deck *deck_ptr)
{
    inDeck = deck_ptr;
}

Deck *CardItem::getDeck()
{
    return inDeck;
}

void CardItem::setCardVisible(bool v)
{
    setVisible(v);
}

void CardItem::setFlipped(QImage image,bool keep_ratio)
{
    flipped = true;
    save_img = img;
    img = image;
    if (keep_ratio == true)
        img = img.scaled(75,110,Qt::KeepAspectRatio);
    else
        img = img.scaled(75,110);

}

bool CardItem::isFlipped()
{
  return flipped;
}

void CardItem::setChild(CardItem *child)
{
    this->child = child;
}

void CardItem::setDefaultPos(QPointF pos)
{
    defaultPos = pos;
}

void CardItem::setDefaultZValue(qreal zval)
{
    defaultZValue = zval;
}


QPointF CardItem::getDefaultPos()
{
    return defaultPos;
}

qreal CardItem::getDefaultZValue()
{
    return defaultZValue;
}


CardItem *CardItem::getChild()
{
    return child;
}

void CardItem::setUnFlipped()
{
    flipped = false;
    img = save_img;
}


void CardItem::setStackId(int id)
{
    StackId = id;
}

int CardItem::getStackId()
{
    return StackId;
}

bool CardItem::isMovable()
{
    return movable;
}

CardItem* CardItem::setMovable()
{
    movable = true;
    setFlag(ItemIsMovable);
    return this;
}

void CardItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(QCursor(Qt::CursorShape(Qt::ClosedHandCursor)));

    update();
    QGraphicsItem::mousePressEvent(event);
}

void CardItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
     update();

     setCursor(QCursor(Qt::CursorShape(Qt::OpenHandCursor)));
     QGraphicsItem::mouseReleaseEvent(event);
}

void CardItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseDoubleClickEvent(event);
}
