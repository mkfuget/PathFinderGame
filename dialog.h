#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Dialog *ui;
    QGraphicsScene * mazeScene;
    QGraphicsItem * maze;
    Board *currentBoard;
    Board *customBoard;

    int currentLevel=0;
    const int maxLevel=9;
    std::vector<std::string> levels
    {
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level00.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level01.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level02.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level03.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level04.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level05.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level06.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level07.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level08.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level09.txt",
    };
};
#endif // DIALOG_H
