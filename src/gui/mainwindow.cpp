#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QColor>
#include <QBrush>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->statusBar->hide();
    ui->graphicsView->setCursor(QCursor(Qt::CursorShape(Qt::OpenHandCursor)));
    ui->graphicsView->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGTH);
    setWindowIcon(QIcon(":/files/icon.png"));
    setWindowTitle("Solitaire 2017 - GUI");

    NewGame();
}

void MainWindow::NewGame(QFile *save_file)
{
        game = std::make_shared<GameScene>(this);
        GameScene *ptr_game = game.get();

        ui->graphicsView->setScene(ptr_game);
        ptr_game->setSolitaireScene(save_file);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionRedo_triggered()
{
    NewGame();
}

void MainWindow::on_actionSave_triggered()
{
    this->game->save_to_file("../cli/savefile");
}

void MainWindow::on_actionLoad_triggered()
{
    QFile load_file("../cli/savefile");

    if (!load_file.open(QIODevice::ReadOnly))
        return;

    NewGame(&load_file);


    load_file.close();

}
