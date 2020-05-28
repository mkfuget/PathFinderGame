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
    ui->graphicsView->setInteractive(true);
    this->currentLevel=0;
    this->inCustomMode=false;

    ui->graphicsView_2->setScene(blockIcon);
    ui->graphicsView_3->setScene(keyIcon);
    ui->graphicsView_4->setScene(acceleratorIcon);
    ui->graphicsView_5->setScene(finishIcon);

    int initialVolume=99;
    customBoard = new Board(initialVolume);
    levels.resize(levelNames.size());
    for(int i=0; i<levelNames.size(); i++)
    {
        levels[i] = new Board(levelNames[i], NUM_BLOCKS_HORIZANTAL, NUM_BLOCKS_VERTICAL, initialVolume);
    }

    ui->graphicsView->setScene(this->levels[0]);
    this->levels[0]->displayBoard();


    backgroundMusic = new QMediaPlayer();
    backgroundMusic->setMedia(QUrl("qrc:/sounds/ClaireDeLune.mp3"));
    backgroundMusic->setVolume(99);
    backgroundMusic->play();



    //include data for a dropdown bocx that will allow the suer to select a block for making their own level
    this->blockLabels["Full Space"]='f';
    this->blockLabels["Empty Space"]='e';
    this->blockLabels["Start Space"]='s';
    this->blockLabels["Finish Space"]='x';
    this->blockLabels["Accelerator Space"]='a';
    this->blockLabels["Blue Space"]='B';
    this->blockLabels["Blue Key"]='b';
    this->blockLabels["Red Space"]='R';
    this->blockLabels["Red key"]='r';
    this->blockLabels["Yellow Space"]='Y';
    this->blockLabels["Yellow Key"]='y';
    this->blockLabels["Green Space"]='G';
    this->blockLabels["Green Key"]='g';

    ui->comboBox->addItem("Full Space");
    ui->comboBox->addItem("Empty Space");
    ui->comboBox->addItem("Start Space");
    ui->comboBox->addItem("Finish Space");
    ui->comboBox->addItem("Accelerator Space");
    ui->comboBox->addItem("Blue Space");
    ui->comboBox->addItem("Blue Key");
    ui->comboBox->addItem("Red Space");
    ui->comboBox->addItem("Red key");
    ui->comboBox->addItem("Yellow Space");
    ui->comboBox->addItem("Yellow Key");
    ui->comboBox->addItem("Green Space");
    ui->comboBox->addItem("Green Key");


}

Dialog::~Dialog()
{
    delete ui;
    for(int i=0; i<this->levels.size(); i++)
    {
        delete this->levels[i];
    }
    delete this->backgroundMusic;
    delete customBoard;
    delete mazeScene;
    delete blockIcon;
    delete finishIcon;
    delete acceleratorIcon;
    delete keyIcon;

}


void Dialog::on_pushButton_clicked()//Push Button for next level
{
    if(inCustomMode)
    {
        this->inCustomMode = false;
        this->customBoard->terminateProcesses();
        ui->graphicsView->setScene(this->levels[this->currentLevel]);
        this->levels[this->currentLevel]->displayBoard();
        this->levels[this->currentLevel]->setSoundEffectVolume(this->volume);
    }
    else if(this->currentLevel<this->maxLevel)
    {
        this->levels[this->currentLevel]->terminateProcesses();
        this->currentLevel++;
        ui->graphicsView->setScene(this->levels[this->currentLevel]);
        this->levels[this->currentLevel]->displayBoard();
        this->levels[this->currentLevel]->setSoundEffectVolume(this->volume);
    }
}

void Dialog::on_pushButton_2_clicked()//push button for last Level
{
    if(inCustomMode)
    {
        this->inCustomMode = false;
        this->customBoard->terminateProcesses();
        ui->graphicsView->setScene(this->levels[this->currentLevel]);
        this->levels[this->currentLevel]->displayBoard();
        this->levels[this->currentLevel]->setSoundEffectVolume(this->volume);
    }

    if(this->currentLevel>0)
    {
        this->levels[this->currentLevel]->terminateProcesses();
        this->currentLevel--;
        ui->graphicsView->setScene(this->levels[this->currentLevel]);
        this->levels[this->currentLevel]->displayBoard();
        this->levels[this->currentLevel]->setSoundEffectVolume(this->volume);

    }

}

void Dialog::on_pushButton_3_clicked()//push button to switch to edit level
{
    this->levels[this->currentLevel]->terminateProcesses();
    this->inCustomMode = true;
    ui->graphicsView->setScene(customBoard);
    customBoard->setToEditMode();
    customBoard->displayBoard();
}

void Dialog::on_comboBox_currentTextChanged(const QString &arg1)//for setting the custom block being added
{
    std::string input = arg1.toStdString();
    char c = this->blockLabels[input];
    customBoard->setCustomBlock(blockLabels[input]);
}

void Dialog::on_pushButton_4_clicked()
{
    this->levels[this->currentLevel]->terminateProcesses();
    this->inCustomMode = true;

    ui->graphicsView->setScene(customBoard);
    customBoard->setToPlayMode();
    customBoard->displayBoard();

}

void Dialog::on_MusicVolumeSlider_sliderMoved(int position)
{
    this->backgroundMusic->setVolume(position);
}

void Dialog::on_EffectVolumeSlider_sliderMoved(int position)
{
    customBoard->setSoundEffectVolume(position);
    this->levels[this->currentLevel]->setSoundEffectVolume(position);
    this->volume = position;
}

void Dialog::on_MusicVolumeSlider_valueChanged(int value)
{
    this->backgroundMusic->setVolume(value);
}

void Dialog::on_EffectVolumeSlider_valueChanged(int value)
{
    customBoard->setSoundEffectVolume(value);
    this->levels[this->currentLevel]->setSoundEffectVolume(value);
    this->volume = value;

}
