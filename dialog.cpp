#include "dialog.h"
#include "ui_dialog.h"
#include "board.h"

#include <vector>
#include <unordered_map>
#include <fstream>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //Constants defining size of the board and size of each space
    const int NUM_BLOCKS_HORIZANTAL = 20;
    const int NUM_BLOCKS_VERTICAL = 20;
    ui->graphicsView->setInteractive(true);

    ui->comboBox->addItem("Empty Space");
    ui->comboBox->addItem("Full Space");
    ui->comboBox->addItem("Start Space");
    ui->comboBox->addItem("Finish Space");
    ui->comboBox->addItem("Acellerator Space");
    ui->comboBox->addItem("Blue Space");
    ui->comboBox->addItem("Blue Key");
    ui->comboBox->addItem("Red Space");
    ui->comboBox->addItem("Red Key");
    ui->comboBox->addItem("Yellow Space");
    ui->comboBox->addItem("Yellow Key");
    ui->comboBox->addItem("Green Space");
    ui->comboBox->addItem("Green Key");

    mazeScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(mazeScene);
    customBoard = new Board(mazeScene);
    currentBoard= new Board("C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level01.txt", NUM_BLOCKS_VERTICAL, NUM_BLOCKS_HORIZANTAL, mazeScene);
    currentBoard->displayBoard();
    mazeScene->addItem(currentBoard);
    currentBoard->setFlag(QGraphicsItem::ItemIsFocusable);
    currentBoard->setFocus();

    QMediaPlayer * backgroundMusic = new QMediaPlayer();
    backgroundMusic->setMedia(QUrl("qrc:/sounds/ClaireDeLune.mp3"));
    backgroundMusic->play();



}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()//Push Button for next level
{
    if(this->currentLevel<this->maxLevel)
    {
        this->currentLevel++;
        const int NUM_BLOCKS_HORIZANTAL = 20;
        const int NUM_BLOCKS_VERTICAL = 20;
        delete currentBoard;
        currentBoard= new Board(this->levels[this->currentLevel], NUM_BLOCKS_VERTICAL, NUM_BLOCKS_HORIZANTAL, mazeScene);
        currentBoard->displayBoard();

        mazeScene->addItem(currentBoard);
        currentBoard->setFlag(QGraphicsItem::ItemIsFocusable);
        currentBoard->setFocus();
    }
}

void Dialog::on_pushButton_2_clicked()//push button for last Level
{
    if(this->currentLevel>0)
    {
        this->currentLevel--;
        const int NUM_BLOCKS_HORIZANTAL = 20;
        const int NUM_BLOCKS_VERTICAL = 20;
        delete currentBoard;
        currentBoard= new Board(this->levels[this->currentLevel], NUM_BLOCKS_VERTICAL, NUM_BLOCKS_HORIZANTAL, mazeScene);
        currentBoard->displayBoard();

        mazeScene->addItem(currentBoard);
        currentBoard->setFlag(QGraphicsItem::ItemIsFocusable);
        currentBoard->setFocus();
    }

}

void Dialog::on_pushButton_3_clicked()//push button to switch to edit level
{

    delete currentBoard;
    customBoard->displayBoard();
    mazeScene->addItem(customBoard);
    customBoard->setFlag(QGraphicsItem::ItemIsFocusable);
    customBoard->setFocus();

}
