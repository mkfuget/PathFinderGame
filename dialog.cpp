#include "dialog.h"
#include "ui_dialog.h"
#include "space.h"
#include "cursor.h"

#include <vector>
#include <unordered_map>
#include <fstream>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //Constants defining size of the board and size of each space
    const int BLOCK_SIZE = 30;
    const int TOP_LEFT_X_COORD = 0;
    const int TOP_LEFT_Y_COORD = 0;
    const int NUM_BLOCKS_HORIZANTAL = 20;
    const int NUM_BLOCKS_VERTICAL = 20;

    mazeBoard = new QGraphicsScene(this);
    ui->graphicsView->setScene(mazeBoard);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    std::unordered_map<char, Space*> factory;
    Space* factoryFullSpace = new FullSpace();factoryFullSpace->setData("fullDummy", BLOCK_SIZE);
    Space* factoryEmptySpace = new EmptySpace(); factoryEmptySpace->setData("emptyDummy", BLOCK_SIZE);
    Space* factoryStartSpace = new StartSpace();factoryStartSpace->setData("startDummy", BLOCK_SIZE);
    Space* factoryFinishSpace = new FinishSpace(); factoryFinishSpace->setData("finishDummy", BLOCK_SIZE);
    Space* factoryAcceleratorSpace = new AcceleratorSpace(); factoryAcceleratorSpace->setData("acceleratorDummy", BLOCK_SIZE);
    Space* factoryBlueKey = new BlueKey(); factoryBlueKey->setData("blueKeyDummy", BLOCK_SIZE);
    Space* factoryBlueBlock = new BlueBlock(); factoryBlueBlock->setData("blueClockDummy", BLOCK_SIZE);

    factory['f'] = factoryFullSpace;
    factory['e'] = factoryEmptySpace;
    factory['s'] = factoryStartSpace;
    factory['x'] = factoryFinishSpace;
    factory['a'] = factoryAcceleratorSpace;
    factory['b'] = factoryBlueKey;
    factory['B'] = factoryBlueBlock;

    std::vector<std::vector<char>> mazeGrid(NUM_BLOCKS_VERTICAL, std::vector<char> (NUM_BLOCKS_HORIZANTAL, 0));
    std::ifstream level01File;
    level01File.open("C:\\Users\\micha\\OneDrive\\Documents\\PathFinder\\Levels\\Level01.txt");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), mazeBoard, SLOT(advance));
    timer->start(100);

    int xCoord = TOP_LEFT_X_COORD;
    int yCoord = TOP_LEFT_Y_COORD;
    char spaceKey;
    int xStart=0;
    int yStart=0;
    for(int i=0; i<NUM_BLOCKS_VERTICAL; i++)
    {
        for(int j=0; j<NUM_BLOCKS_HORIZANTAL; j++)
        {
            level01File>>spaceKey;
            mazeGrid[i][j]=spaceKey;
            factory[spaceKey]->displaySpace(xCoord, yCoord, mazeBoard);
            xCoord+=BLOCK_SIZE;
            if(spaceKey=='s')
            {
                xStart=j;
                yStart=i;
            }
        }
        xCoord=TOP_LEFT_X_COORD;
        yCoord+=BLOCK_SIZE;
    }

    Cursor * gameCursor = new Cursor(xStart, yStart,BLOCK_SIZE, mazeGrid, factory);
    gameCursor->setRect(xStart*BLOCK_SIZE+BLOCK_SIZE/4, yStart*BLOCK_SIZE+BLOCK_SIZE/4, BLOCK_SIZE/2, +BLOCK_SIZE/2);
    gameCursor->setFlag(QGraphicsItem::ItemIsFocusable);
    gameCursor->setFocus();
    mazeBoard->addItem(gameCursor);

}

Dialog::~Dialog()
{
    delete ui;
}

