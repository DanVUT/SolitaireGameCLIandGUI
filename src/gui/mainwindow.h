/*!
 * @file
 * @brief Subor obsahuje objekt Hlavneho okna a metody pre volanie hry a volanie hernej sceny
 *
 * @author Martin Grnac
 */



#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QRgb>
#include <memory>
#include "gamescene.h"
#include "carditem.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGTH 768
#define SOLITAIRE_GREEN qRgb(0,102,51)

#include <QPointF>
#include <QFile>

namespace Ui {
class MainWindow;
class GameScene;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    /**
     * @brief metoda nastavuje novu hru a scenu
     */
    void NewGame(QFile *save_file = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief metoda vykonavana pri detekci signalu kliknutia na button "New" v okne hry
     */
    void on_actionRedo_triggered();

    void on_actionSave_triggered();

    void on_actionLoad_triggered();

private:
    /**
     * @brief ukazatel na user interface
     */
    Ui::MainWindow *ui;

    /**
     * @brief scena hry
     */
    std::shared_ptr<GameScene>game;

};

#endif // MAINWINDOW_H
