#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include "board.h"
#include <QHash>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT
    const int NUM_BLOCKS_HORIZANTAL = 20;
    const int NUM_BLOCKS_VERTICAL = 20;

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_MusicVolumeSlider_sliderMoved(int position);

    void on_EffectVolumeSlider_sliderMoved(int position);

    void on_MusicVolumeSlider_valueChanged(int value);

    void on_EffectVolumeSlider_valueChanged(int value);

private:
    Ui::Dialog *ui;
    QGraphicsScene * mazeScene;
    Board *customBoard;
    QMediaPlayer * backgroundMusic;
    std::unordered_map<std::string, char> blockLabels;
    bool inCustomMode;
    int currentLevel=0;
    const int maxLevel=9;
    int volume;
    std::vector<std::string> levelNames
    {

        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level00.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level01.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level02.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level03.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level04.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level06.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level05.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level07.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level08.txt",
        "C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level09.txt",
    };
    std::vector<Board*> levels;
    Board* blockIcon = new Board('B');
    Board* keyIcon = new Board('b');
    Board* acceleratorIcon = new Board('a');
    Board* finishIcon = new Board('x');

};
#endif // DIALOG_H
