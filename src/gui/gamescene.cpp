#include "gamescene.h"
#include <QCursor>
#include <QFile>
#include <QGraphicsTextItem>


#define SIGN 1
#define VALUE 2
#define FLIP 3

GameScene::GameScene(QObject *parent): QGraphicsScene(parent)
{
    CardHeight = 110;
    CardWidth = 75;

    platform_img = QImage(":/resc/files/pos.png");

    background_img = QImage(":/resc/files/card_background_75x110.svg");
}

GameScene::~GameScene()
{
    while(!all_cards.empty())
    {
        delete all_cards.last();
        all_cards.removeLast();
    }

    delete main_deck;
    delete waste_deck;

    for(int i = 0; i < foundation_decks.size(); i++)
        delete foundation_decks[i];

    for(int i = 0; i < stacks.size(); i++)
        delete stacks[i];

}

int GameScene::getCardHeight()
{
    return CardHeight;
}

int GameScene::getCardWidth()
{
    return CardWidth;
}

void GameScene::setSolitaireScene(QFile *save_file)
{
    QColor color;
    color.setRgb(SOLITAIRE_GREEN);
    setBackgroundBrush(QBrush(color));
    setSceneRect(0,0,SCENE_WIDTH,SCENE_HEIGHT);

    loadCards(save_file);

    main_deck = new Deck(Deck::MainDeck,new CardItem((":/resc/files/card_background_75x110.svg")));
    main_deck->setPlatformPosition(20,20);
    addItem(main_deck->getPlatformCard());


    waste_deck = new Deck(Deck::Waste,new CardItem(":/resc/files/pos.png"));
    waste_deck->setPlatformPosition(150,20);
    addItem(waste_deck->getPlatformCard());

    foundation_decks.resize(4);
    for(int i = 0; i < 4; i++)
    {
        foundation_decks[i] = new Deck(Deck::Foundation,new CardItem(":/resc/files/pos.png"));
        foundation_decks[i]->setDeckId(i);
        foundation_decks[i]->setPlatformPosition(FOUNDATION_OFFSET +
                                                 (foundation_decks[i]->getPlatformCard()->getWidth()
                                                 +50)*i+1,20);

        addItem(foundation_decks[i]->getPlatformCard());
    }


    stacks.resize(7);
    for(int i = 0; i < 7; i++)
    {
        stacks[i] = new Deck(Deck::Stack,new CardItem(":/resc/files/pos.png"));
        stacks[i]->setDeckId(i);
        stacks[i]->setPlatformPosition(STACK_OFFSET +
                                                 (stacks[i]->getPlatformCard()->getWidth()
                                                 +70)*i+1,250);

        addItem(stacks[i]->getPlatformCard());
        stacks[i]->setDeckOffset(20);
    }


    if (save_file != nullptr)
    {

        QTextStream in(save_file);

        int row_counter = 1;

        while(!in.atEnd())
        {
            QString line = in.readLine();


            int line_size = line.size();
            int idx = 0;
            int state = SIGN;

            QString sign;
            int  value;
            bool flipped;

            QString temp_digit;

            while (idx < line_size)
            {

                switch (state) {
                case SIGN:

                    sign = line[idx];
                    idx += 2;
                    state = VALUE;

                    break;

                case VALUE:

                    if(!(line[idx].isDigit()))
                    {
                        idx++;
                        value = temp_digit.toInt();
                        state = FLIP;
                        temp_digit = "";

                    }
                    else
                    {
                        temp_digit += line[idx];
                        idx++;
                    }

                    break;


                case FLIP:

                    if (line[idx] == '0')
                        flipped = false;
                    else
                        flipped = true;

                    idx += 2;
                    state = SIGN;

                    CardItem* tmp_card = findCard(sign,value);


                    // PRIDAVANIE KARTIET DO BALIKOV
                    // MAIN DECK
                    if (row_counter == 1)
                    {
                        tmp_card->setMovable();
                        tmp_card->setVisible(false);
                        addItem(tmp_card);
                        main_deck->addCard(tmp_card);
                    }
                    else if (row_counter == 2)
                    {
                        tmp_card->setMovable();
                        tmp_card->setVisible(true);
                        addItem(tmp_card);
                        waste_deck->addCard(tmp_card);
                        //waste_deck->updateZValues();
                    }
                    else if (row_counter > 2 && row_counter < 10)
                    {
                        tmp_card->setVisible(true);

                        if (!flipped)
                            tmp_card->setFlipped(background_img,true);
                        else
                            tmp_card->setMovable();

                        addItem(tmp_card);
                        stacks[row_counter-3]->addCard(tmp_card);
                        stacks[row_counter-3]->updateZValues();

                    }
                    else if (row_counter >= 10)
                    {
                        tmp_card->setVisible(true);

                        addItem(tmp_card);
                        foundation_decks[row_counter-10]->addCard(tmp_card);
                        foundation_decks[row_counter-10]->updateZValues();

                        switch (tmp_card->getCardType()) {
                            case CardItem::Club: foundation_decks[row_counter-10]->setDeckSign(Deck::Club);
                                break;

                            case CardItem::Spade: foundation_decks[row_counter-10]->setDeckSign(Deck::Spade);
                                break;

                            case CardItem::Heart: foundation_decks[row_counter-10]->setDeckSign(Deck::Heart);
                                break;

                            case CardItem::Diamond: foundation_decks[row_counter-10]->setDeckSign(Deck::Diamond);
                                break;

                            default:
                                break;
                        }

                    }


                    break;

                }

            }

            row_counter++;
        }

        // OSETRENIE PRAZDNEHO MAIN DECKU
        if (main_deck->isEmpty())
            main_deck->getPlatformCard()->setFlipped(platform_img,false);

        update();

        //CLEAN MIXED CARDS
        while(!mixed_cards.empty())
            mixed_cards.removeLast();

    }
    else
    {
    // IF NEW GAME

    //Set cards to stacks
        for(int i = 0 ; i<7;i++)
        {
            for(int j = 0; j<=i; j++)
            {
                test_card = mixed_cards.last();
                test_card->setVisible(true);

                if (j == i)
                    test_card->setMovable();
                else
                    test_card->setFlipped(background_img,true);

                addItem(test_card);
                stacks[i]->addCard(test_card);
                stacks[i]->updateZValues();

                mixed_cards.removeLast();
            }
        }


        while(!mixed_cards.empty())
        {
            test_card = mixed_cards.last();
            test_card->setMovable();
            test_card->setVisible(false);
            addItem(test_card);
            main_deck->addCard(test_card);
            mixed_cards.removeLast();
        }
    }

/*

    QGraphicsTextItem * text = new QGraphicsTextItem;
    QGraphicsTextItem * shade = new QGraphicsTextItem;

    text->setPos(width()/2-280,height()/2-140);
    text->setDefaultTextColor(QColor(0,0,0,140));
    text->setScale(10);
    text->setPlainText("WINNER !");
    text->setZValue(findMaxZvalue() + 1);
    addItem(text);

    shade->setPos(text->pos().x()-5,text->pos().y()-5);
    shade->setDefaultTextColor(QColor(250,90,20));
    shade->setScale(10);
    shade->setPlainText("WINNER !");
    shade->setZValue(findMaxZvalue() + 1);
    addItem(shade);

*/

}

void GameScene::loadCards(QFile *savefile)
{
    mixed_cards.append(new CardItem(":/resc/files/clubs/Club_10_75x110.svg",CardItem::Black,CardItem::Club,10));
    mixed_cards.append(new CardItem(":/resc/files/clubs/Club_2_75x110.svg",CardItem::Black,CardItem::Club,2));
    mixed_cards.append(new CardItem(":/resc/files/clubs/Club_3_75x110.svg",CardItem::Black,CardItem::Club,3));
    mixed_cards.append(new CardItem(":/resc/files/clubs/Club_4_75x110.svg",CardItem::Black,CardItem::Club,4));
    mixed_cards.append(new CardItem(":/resc/files/clubs/Club_5_75x110.svg",CardItem::Black,CardItem::Club,5));
    mixed_cards.append(new CardItem(":/resc/files/clubs/Club_6_75x110.svg",CardItem::Black,CardItem::Club,6));
    mixed_cards.append(new CardItem(":/resc/files/clubs/Club_7_75x110.svg",CardItem::Black,CardItem::Club,7));
    mixed_cards.append(new CardItem(":/resc/files/clubs/Club_8_75x110.svg",CardItem::Black,CardItem::Club,8));
    mixed_cards.append(new CardItem(":/resc/files/clubs/Club_9_75x110.svg",CardItem::Black,CardItem::Club,9));
    mixed_cards.append(new CardItem(":/resc/files/clubs/Club_ace_75x110.svg",CardItem::Black,CardItem::Club,1));
    mixed_cards.append(new CardItem(":/resc/files/clubs/Club_jack_75x110.svg",CardItem::Black,CardItem::Club,11));
    mixed_cards.append(new CardItem(":/resc/files/clubs/Club_king_75x110.svg",CardItem::Black,CardItem::Club,13));
    mixed_cards.append(new CardItem(":/resc/files/clubs/Club_queen_75x110.svg",CardItem::Black,CardItem::Club,12));

    mixed_cards.append(new CardItem(":/resc/files/diamond/Diamond_10_75x110.svg",CardItem::Red,CardItem::Diamond,10));
    mixed_cards.append(new CardItem(":/resc/files/diamond/Diamond_2_75x110.svg",CardItem::Red,CardItem::Diamond,2));
    mixed_cards.append(new CardItem(":/resc/files/diamond/Diamond_3_75x110.svg",CardItem::Red,CardItem::Diamond,3));
    mixed_cards.append(new CardItem(":/resc/files/diamond/Diamond_4_75x110.svg",CardItem::Red,CardItem::Diamond,4));
    mixed_cards.append(new CardItem(":/resc/files/diamond/Diamond_5_75x110.svg",CardItem::Red,CardItem::Diamond,5));
    mixed_cards.append(new CardItem(":/resc/files/diamond/Diamond_6_75x110.svg",CardItem::Red,CardItem::Diamond,6));
    mixed_cards.append(new CardItem(":/resc/files/diamond/Diamond_7_75x110.svg",CardItem::Red,CardItem::Diamond,7));
    mixed_cards.append(new CardItem(":/resc/files/diamond/Diamond_8_75x110.svg",CardItem::Red,CardItem::Diamond,8));
    mixed_cards.append(new CardItem(":/resc/files/diamond/Diamond_9_75x110.svg",CardItem::Red,CardItem::Diamond,9));
    mixed_cards.append(new CardItem(":/resc/files/diamond/Diamond_ace_75x110.svg",CardItem::Red,CardItem::Diamond,1));
    mixed_cards.append(new CardItem(":/resc/files/diamond/Diamond_jack_75x110.svg",CardItem::Red,CardItem::Diamond,11));
    mixed_cards.append(new CardItem(":/resc/files/diamond/Diamond_king_75x110.svg",CardItem::Red,CardItem::Diamond,13));
    mixed_cards.append(new CardItem(":/resc/files/diamond/Diamond_queen_75x110.svg",CardItem::Red,CardItem::Diamond,12));

    mixed_cards.append(new CardItem(":/resc/files/heart/Heart_10_75x110.svg",CardItem::Red,CardItem::Heart,10));
    mixed_cards.append(new CardItem(":/resc/files/heart/Heart_2_75x110.svg",CardItem::Red,CardItem::Heart,2));
    mixed_cards.append(new CardItem(":/resc/files/heart/Heart_3_75x110.svg",CardItem::Red,CardItem::Heart,3));
    mixed_cards.append(new CardItem(":/resc/files/heart/Heart_4_75x110.svg",CardItem::Red,CardItem::Heart,4));
    mixed_cards.append(new CardItem(":/resc/files/heart/Heart_5_75x110.svg",CardItem::Red,CardItem::Heart,5));
    mixed_cards.append(new CardItem(":/resc/files/heart/Heart_6_75x110.svg",CardItem::Red,CardItem::Heart,6));
    mixed_cards.append(new CardItem(":/resc/files/heart/Heart_7_75x110.svg",CardItem::Red,CardItem::Heart,7));
    mixed_cards.append(new CardItem(":/resc/files/heart/Heart_8_75x110.svg",CardItem::Red,CardItem::Heart,8));
    mixed_cards.append(new CardItem(":/resc/files/heart/Heart_9_75x110.svg",CardItem::Red,CardItem::Heart,9));
    mixed_cards.append(new CardItem(":/resc/files/heart/Heart_ace_75x110.svg",CardItem::Red,CardItem::Heart,1));
    mixed_cards.append(new CardItem(":/resc/files/heart/Heart_jack_75x110.svg",CardItem::Red,CardItem::Heart,11));
    mixed_cards.append(new CardItem(":/resc/files/heart/Heart_king_75x110.svg",CardItem::Red,CardItem::Heart,13));
    mixed_cards.append(new CardItem(":/resc/files/heart/Heart_queen_75x110.svg",CardItem::Red,CardItem::Heart,12));

    mixed_cards.append(new CardItem(":/resc/files/spade/Spade_10_75x110.svg",CardItem::Black,CardItem::Spade,10));
    mixed_cards.append(new CardItem(":/resc/files/spade/Spade_2_75x110.svg",CardItem::Black,CardItem::Spade,2));
    mixed_cards.append(new CardItem(":/resc/files/spade/Spade_3_75x110.svg",CardItem::Black,CardItem::Spade,3));
    mixed_cards.append(new CardItem(":/resc/files/spade/Spade_4_75x110.svg",CardItem::Black,CardItem::Spade,4));
    mixed_cards.append(new CardItem(":/resc/files/spade/Spade_5_75x110.svg",CardItem::Black,CardItem::Spade,5));
    mixed_cards.append(new CardItem(":/resc/files/spade/Spade_6_75x110.svg",CardItem::Black,CardItem::Spade,6));
    mixed_cards.append(new CardItem(":/resc/files/spade/Spade_7_75x110.svg",CardItem::Black,CardItem::Spade,7));
    mixed_cards.append(new CardItem(":/resc/files/spade/Spade_8_75x110.svg",CardItem::Black,CardItem::Spade,8));
    mixed_cards.append(new CardItem(":/resc/files/spade/Spade_9_75x110.svg",CardItem::Black,CardItem::Spade,9));
    mixed_cards.append(new CardItem(":/resc/files/spade/Spade_ace_75x110.svg",CardItem::Black,CardItem::Spade,1));
    mixed_cards.append(new CardItem(":/resc/files/spade/Spade_jack_75x110.svg",CardItem::Black,CardItem::Spade,11));
    mixed_cards.append(new CardItem(":/resc/files/spade/Spade_king_75x110.svg",CardItem::Black,CardItem::Spade,13));
    mixed_cards.append(new CardItem(":/resc/files/spade/Spade_queen_75x110.svg",CardItem::Black,CardItem::Spade,12));


    if (savefile == nullptr)
    {
        std::srand(unsigned (std::time(0)));
        std::random_shuffle(mixed_cards.begin(),mixed_cards.end());
    }

    all_cards = mixed_cards;

}


bool GameScene::try_move(CardItem *to, CardItem * from)
{

    if (to == nullptr || from == nullptr)
        return false;


    // Presun na foundation
    if (to->getDeck()->type() == Deck::Foundation)
    {

        //Ak je foundation balik prazdny
        if (to->getDeck()->getDeckSign() == Deck::None
            && from->getCardValue() == 1)
        {

            switch (from->getCardType()) {
                case CardItem::Club: to->getDeck()->setDeckSign(Deck::Club);
                    break;

                case CardItem::Spade: to->getDeck()->setDeckSign(Deck::Spade);
                    break;

                case CardItem::Heart: to->getDeck()->setDeckSign(Deck::Heart);
                    break;

                case CardItem::Diamond: to->getDeck()->setDeckSign(Deck::Diamond);
                    break;

                default:
                    break;
            }

            return true;
        }
        else  //Ak foundation balik nie je prazdny
        {
            CardItem* last_card = to->getDeck()->getLastCard();

            if (last_card == nullptr)
                return false;

            if (from->getCardValue() == last_card->getCardValue()+1)
            {

                if (from->getCardType() == CardItem::Club
                    && to->getDeck()->getDeckSign() == Deck::Club)
                    return true;
                else if (from->getCardType() == CardItem::Spade
                         && to->getDeck()->getDeckSign() == Deck::Spade)
                    return true;
                else if (from->getCardType() == CardItem::Heart
                         && to->getDeck()->getDeckSign() == Deck::Heart)
                    return true;
                else if (from->getCardType() == CardItem::Diamond
                         && to->getDeck()->getDeckSign() == Deck::Diamond)
                    return true;

            }

        }


    }
    else if (to->getDeck()->type() == Deck::Stack)
    {
           CardItem* last_card = to->getDeck()->getLastCard();

           // Ak je deck prazdny
           if (last_card == nullptr &&  from->getCardValue() == 13)
           {
               return true;
           }
           else if (last_card != nullptr)
           {
               // Sleduj podmienku
               if (last_card->getCardColor() != from->getCardColor()
                   && last_card->getCardValue() == from->getCardValue() +1)
                   return true;
           }

    }


    return false;
}


// ZMENA
void GameScene::save_to_file(QString path)
{
    QFile save_file(path);

    if (!save_file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&save_file);


    QString row_data;
    QString gap;

    // Main Deck save
    int temp_deck_size = main_deck->getDeckSize();

    //qDebug() << "----";

    for (int i = temp_deck_size - 1; i >= 0; i--)
    {
        if (i == temp_deck_size - 1)
            gap = "";
        else
            gap = " ";

        row_data = row_data + gap + write_card_to_file(main_deck->getCardFromDeck(i));
    }

    row_data += "\n";

    out << row_data;

    //qDebug() << row_data;

    //qDebug() << "waste";

    row_data = "";
    temp_deck_size = waste_deck->getDeckSize();

    for (int i = 0; i < temp_deck_size; i++)
    {
        if (i == 0)
            gap = "";
        else
            gap = " ";

        row_data = row_data + gap + write_card_to_file(waste_deck->getCardFromDeck(i));
    }

    row_data += "\n";

    out << row_data;

    //qDebug() << row_data;

    //qDebug() << "Stacks";

    for(int stack_idx = 0; stack_idx < 7; stack_idx++)
    {
        row_data = "";
        temp_deck_size = stacks[stack_idx]->getDeckSize();

        for (int i = 0; i < temp_deck_size; i++)
        {
            if (i == 0)
                gap = "";
            else
                gap = " ";

            row_data = row_data + gap + write_card_to_file(stacks[stack_idx]->getCardFromDeck(i));
        }

        row_data += "\n";

        out << row_data;

        //qDebug() << row_data;

    }


    //qDebug() << "Foundations";

    for(int foundation_idx = 0; foundation_idx < 4; foundation_idx++)
    {
        row_data = "";
        temp_deck_size = foundation_decks[foundation_idx]->getDeckSize();

        for (int i  = 0; i < temp_deck_size; i++)
        {
            if (i == 0)
                gap = "";
            else
                gap = " ";

            row_data = row_data + gap + write_card_to_file(foundation_decks[foundation_idx]->getCardFromDeck(i));
        }

        if (foundation_idx < 3)
            row_data += "\n";

        out << row_data;

        //qDebug() << row_data;
    }

    save_file.close();

}



QString GameScene::write_card_to_file(CardItem *card)
{

    QString data_stream = "";

    switch (card->getCardType()) {
    case CardItem::Diamond:
        data_stream = "d";
        break;

    case CardItem::Spade:
        data_stream = "s";
        break;

    case CardItem::Heart:
        data_stream = "h";
        break;

    case CardItem::Club:
        data_stream = "c";
        break;

    default:
        break;
    }

    int turned;

    if (card->getDeck()->type() == Deck::MainDeck)
    {
        turned = 0;
    }
    else
    {
        //FLIPPED BY BACKGROUND
        if (card->isFlipped())
            turned = 0;
        else
        // FLIPPED BY SIGN TOWARDS PLAYER
            turned = 1;
    }



    data_stream = data_stream + " " + QString::number(card->getCardValue())
                + " " + QString::number(turned);

   // qDebug() << data_stream;

    return data_stream;


}

CardItem *GameScene::findCard(QString sign, int value)
{
    CardItem::CardType tmp_type;

    if (sign == "d")
        tmp_type = CardItem::Diamond;
    else if (sign == "s")
        tmp_type = CardItem::Spade;
    else if (sign == "c")
        tmp_type = CardItem::Club;
    else if (sign == "h")
        tmp_type = CardItem::Heart;

    int length  = mixed_cards.size();

    for(int i = 0; i < length; i++)
        if (mixed_cards[i]->getCardType() == tmp_type && mixed_cards[i]->getCardValue() == value)
            return mixed_cards[i];

    return nullptr;

}

// ZMENA


void GameScene::saveCardData(CardItem *card)
{
    card->setDefaultPos(card->scenePos());
    card->setDefaultZValue(card->zValue());
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;

    current_item = itemAt(event->scenePos().x(),event->scenePos().y(),QTransform());


    //AK bola nejaka polozka vybrana
    if (current_item)
    {
        CardItem* pressed = static_cast<CardItem*>(current_item);

        if (pressed->isMovable())
        {
                qreal max_Zvalue =  findMaxZvalue();

                saveCardData(pressed);
                pressed->setZValue(max_Zvalue + 0.1);

            if (pressed->getDeck()->type() == Deck::Stack)
            {
                int Tmp_Deck_Size = pressed->getDeck()->getDeckSize();
                int Card_Item_Index = pressed->getStackId();
                Deck* Selected_Deck = pressed->getDeck();

                //ak je karta v stacku treba obnovit defaultne nastavenia Zvalue
                pressed->setZValue(pressed->getDefaultZValue());

                for(int i = Card_Item_Index; i < Tmp_Deck_Size;i++)
                {
                    saveCardData(Selected_Deck->getCardFromDeck(i));

                    Selected_Deck->getCardFromDeck(i)->setZValue(max_Zvalue + 0.1);

                    max_Zvalue = max_Zvalue + 0.1;

                    if (i+1 < Tmp_Deck_Size)
                    {
                        Selected_Deck->getCardFromDeck(i)->setChild(Selected_Deck->getCardFromDeck(i+1));
                        Selected_Deck->getCardFromDeck(i+1)->setParentItem(Selected_Deck->getCardFromDeck(i));
                        Selected_Deck->getCardFromDeck(i+1)->setPos(0,Selected_Deck->getDeckOffset());
                    }
                }

                update();

            }
        }
    }


    QGraphicsScene::mousePressEvent(event);
}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;

    QGraphicsScene::mouseReleaseEvent(event);

    QGraphicsItem* released_item = itemAt(event->scenePos().x(),
                                          event->scenePos().y(),QTransform());

    if (released_item &&  current_item)
    {
        bool moveEvent = false;
        CardItem *released = static_cast<CardItem*>(released_item);
        CardItem *pressed = static_cast<CardItem*>(current_item);
        bool empty_collide = released->collidingItems().empty();

        if (!empty_collide)
        {
            //released = static_cast<CardItem*>(released->collidingItems().first());
            released = collidingDeck(released->collidingItems(),pressed);

            if (released != pressed)
                moveEvent = true;

        }

        // Ak je kliknutie na Maindeck
        if (released->getDeck()->type() == Deck::MainDeck
            && pressed->getDeck()->type() == Deck::MainDeck)
        {
                if(!main_deck->isEmpty())
                {
                    CardItem * removedFirstCard = main_deck->removeFirstCard();
                    removedFirstCard->setCardVisible(true);
                    //Waste position
                    removedFirstCard->setPos(150,20);
                    removedFirstCard->setZValue(0.1);
                    waste_deck->addCard(removedFirstCard);

                    waste_deck->updateZValues();

                    if (main_deck->isEmpty())
                        main_deck->getPlatformCard()->setFlipped(platform_img,false);

                    update();
                }
                else //if main deck is empty
                {
                    CardItem *wasteFirstCard;
                    while (!waste_deck->isEmpty())
                    {
                        wasteFirstCard = waste_deck->removeFirstCard();
                        wasteFirstCard->setPos(20,20);
                        wasteFirstCard->setVisible(false);
                        main_deck->addCard(wasteFirstCard);

                    }
                    if (!main_deck->isEmpty())
                        main_deck->getPlatformCard()->setUnFlipped();

                    update();
                }

        }//Moving from Waste to Foundation
        else if (!empty_collide && released->getDeck()->type() == Deck::Foundation
                  && pressed->getDeck()->type() == Deck::Waste && try_move(released,pressed))
         {
            if (!waste_deck->isEmpty())
            {

                int found_id = released->getDeck()->getDeckId();

                //Pri tahani z Waste do Foundation netreba riesit rodicovsku poziciu
                CardItem* wasteLastCard = waste_deck->removeLastCard();
                wasteLastCard->setPos(foundation_decks[found_id]->getPlatformCard()->pos());
                foundation_decks[found_id]->addCard(wasteLastCard);

                foundation_decks[found_id]->updateZValues();
                update();
            }
        }
        else if (moveEvent && pressed->getDeck()->type() == Deck::Stack
                 && released->getDeck()->type() == Deck::Stack  && try_move(released,pressed))
        {

               int from_stack_index = pressed->getDeck()->getDeckId();
               int to_stack_index = released->getDeck()->getDeckId();
               int moved_card_index = pressed->getStackId();

               if (pressed->isMovable())
               {

                   int items_to_append = 0;

                   if (moved_card_index - 1 >= 0)
                   {
                       if (!stacks[from_stack_index]->getCardFromDeck(moved_card_index-1)->isMovable())
                       {
                           stacks[from_stack_index]->getCardFromDeck(moved_card_index-1)->setMovable();
                           stacks[from_stack_index]->getCardFromDeck(moved_card_index-1)->setUnFlipped();
                       }
                   }


                   for(int i = moved_card_index; i < stacks[from_stack_index]->getDeckSize(); i++, items_to_append++)
                   {
                       CardItem* card = stacks[from_stack_index]->getCardFromDeck(i);

                       stacks[to_stack_index]->addCard(card);
                   }


                   for(int i = 0; i < items_to_append; i++)
                   {
                       if(!stacks[from_stack_index]->isEmpty())
                            stacks[from_stack_index]->removeLastCard();
                   }


                   if (pressed != nullptr && pressed->isMovable())
                       restoreCardParams(pressed);

               }
               stacks[from_stack_index]->updateZValues();
               stacks[to_stack_index]->updateZValues();

               update();
        }
        else if (moveEvent && pressed->getDeck()->type() == Deck::Waste
                 && released->getDeck()->type() == Deck::Stack && try_move(released,pressed))
        {

            CardItem* wasteLastCard;

            if(!waste_deck->isEmpty())
            {
                wasteLastCard = waste_deck->removeLastCard();
                released->getDeck()->addCard(wasteLastCard);
            }


            if (pressed != nullptr && pressed->isMovable())
                restoreCardParams(pressed);

            // Pozor kolizia waste_deck->updateZValues();
            stacks[released->getDeck()->getDeckId()]->updateZValues();

            update();

        }
        else if (moveEvent && pressed->getDeck()->type() == Deck::Stack
                 && released->getDeck()->type() == Deck::Foundation && try_move(released,pressed))
        {

            CardItem * stackLastCard;
            int stack_id = pressed->getDeck()->getDeckId();
            int foundation_id = released->getDeck()->getDeckId();

            if (pressed->getChild() == nullptr &&  pressed->isMovable())
            {

                int stackLastCard_index = pressed->getStackId();

                if (stackLastCard_index - 1 >= 0)
                {
                    if(!stacks[stack_id]->getCardFromDeck(stackLastCard_index - 1)->isMovable())
                    {
                        stacks[stack_id]->getCardFromDeck(stackLastCard_index - 1)->setMovable();
                        stacks[stack_id]->getCardFromDeck(stackLastCard_index - 1)->setUnFlipped();
                    }
                }

                stackLastCard = stacks[stack_id]->removeLastCard();
                foundation_decks[foundation_id]->addCard(stackLastCard);

            }

            stacks[stack_id]->updateZValues();
            foundation_decks[foundation_id]->updateZValues();

            if (pressed != nullptr && pressed->isMovable())
                restoreCardParams(pressed);

            update();
        }
        else
        {
            //Restore position
            if (pressed != nullptr && pressed->isMovable())
                restoreCardParams(pressed);

            update();
        }
    }
}


void GameScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);
}

void GameScene::restoreCardParams(CardItem* card)
{
    if (card->getChild() != nullptr)
    {
        CardItem * temp_card;
        while(card != nullptr)
        {
            //temp_card->setParentItem(0);
            temp_card = card;
            card = card->getChild();

            temp_card->setChild(nullptr);
            temp_card->setParentItem(0);
            temp_card->setPos(temp_card->getDefaultPos());
            temp_card->setZValue(temp_card->getDefaultZValue());

        }

    }
    else
    {
        card->setPos(card->getDefaultPos());
        card->setZValue(card->getDefaultZValue());
    }

}


void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}


CardItem* GameScene::collidingDeck(QList<QGraphicsItem*> colliding_list, CardItem* pressed)
{

    foreach (auto graph_item, colliding_list)
    {
        CardItem* card = static_cast<CardItem*>(graph_item);

            if (pressed->getDeck()->type() == card->getDeck()->type())
            {
                if (pressed->getDeck()->getDeckId() != card->getDeck()->getDeckId())
                    return card;
            }
            else
            {
                return card;
            }
    }

    return pressed;
}


qreal GameScene::findMaxZvalue()
{
    qreal max = 0.0;
    foreach(auto item,items())
    {
        if (max < item->zValue())
            max = item->zValue();
    }

    return max;
}
