#include "board.h"


Board::Board(QGraphicsScene* mazeScene)
{
    this->numBlocksVertical = 20;
    this->numBlocksHorizantal = 20;
    this->mazeScene = mazeScene;
    Space* factoryFullSpace = new FullSpace();
    Space* factoryEmptySpace = new EmptySpace();
    Space* factoryStartSpace = new StartSpace();
    Space* factoryFinishSpace = new FinishSpace();
    Space* factoryAcceleratorSpace = new AcceleratorSpace();
    Space* factoryBlueKey = new BlueKey();
    Space* factoryBlueBlock = new BlueBlock();
    Space* factoryRedKey = new RedKey();
    Space* factoryRedBlock = new RedBlock();
    Space* factoryYellowKey = new YellowKey();
    Space* factoryYellowBlock = new YellowBlock();
    Space* factoryGreenKey = new GreenKey();
    Space* factoryGreenBlock = new GreenBlock();

    factory['f'] = factoryFullSpace;
    factory['e'] = factoryEmptySpace;
    factory['s'] = factoryStartSpace;
    factory['x'] = factoryFinishSpace;
    factory['a'] = factoryAcceleratorSpace;
    factory['b'] = factoryBlueKey;
    factory['B'] = factoryBlueBlock;
    factory['r'] = factoryRedKey;
    factory['R'] = factoryRedBlock;
    factory['y'] = factoryYellowKey;
    factory['Y'] = factoryYellowBlock;
    factory['g'] = factoryGreenKey;
    factory['G'] = factoryGreenBlock;

    mazeGrid.resize(numBlocksVertical+2);
    for (int i = 0; i < numBlocksVertical+2; i++)
    {
        mazeGrid[i].resize(numBlocksHorizantal+2);
    }
    for(int i=0; i<numBlocksVertical+2; i++)
    {
        mazeGrid[i][0]='f';
        mazeGrid[i][numBlocksVertical+1]='f';
    }
    for(int i=0; i<numBlocksHorizantal+2; i++)
    {
        mazeGrid[0][i]='f';
        mazeGrid[numBlocksHorizantal+1][i]='f';
    }
    for(int i=1; i<numBlocksVertical+1; i++)
    {
        for(int j=1; j<numBlocksHorizantal+1; j++)
        {
            mazeGrid[i][j]='e';
            factory['e']->displaySpace(indexToCoord(j), indexToCoord(i), mazeScene);
        }
    }



}

Board::~Board()
{

}

Board::Board(std::string fileName, int numBlocksVertical, int numBlocksHorizantal, QGraphicsScene* mazeScene)
{
    this->numBlocksVertical = numBlocksVertical;
    this->numBlocksHorizantal = numBlocksHorizantal;
    this->mazeScene = mazeScene;
    Space* factoryFullSpace = new FullSpace();
    Space* factoryEmptySpace = new EmptySpace();
    Space* factoryStartSpace = new StartSpace();
    Space* factoryFinishSpace = new FinishSpace();
    Space* factoryAcceleratorSpace = new AcceleratorSpace();
    Space* factoryBlueKey = new BlueKey();
    Space* factoryBlueBlock = new BlueBlock();
    Space* factoryRedKey = new RedKey();
    Space* factoryRedBlock = new RedBlock();
    Space* factoryYellowKey = new YellowKey();
    Space* factoryYellowBlock = new YellowBlock();
    Space* factoryGreenKey = new GreenKey();
    Space* factoryGreenBlock = new GreenBlock();

    factory['f'] = factoryFullSpace;
    factory['e'] = factoryEmptySpace;
    factory['s'] = factoryStartSpace;
    factory['x'] = factoryFinishSpace;
    factory['a'] = factoryAcceleratorSpace;
    factory['b'] = factoryBlueKey;
    factory['B'] = factoryBlueBlock;
    factory['r'] = factoryRedKey;
    factory['R'] = factoryRedBlock;
    factory['y'] = factoryYellowKey;
    factory['Y'] = factoryYellowBlock;
    factory['g'] = factoryGreenKey;
    factory['G'] = factoryGreenBlock;

    mazeGrid.resize(numBlocksVertical+2);
    for (int i = 0; i < numBlocksVertical+2; i++)
    {
        mazeGrid[i].resize(numBlocksHorizantal+2);
    }
    for(int i=0; i<numBlocksVertical+2; i++)
    {
        mazeGrid[i][0]='f';
        mazeGrid[i][numBlocksVertical+1]='f';
    }
    for(int i=0; i<numBlocksHorizantal+2; i++)
    {
        mazeGrid[0][i]='f';
        mazeGrid[numBlocksHorizantal+1][i]='f';
    }

    std::ifstream currentFile;
    currentFile.open(fileName);
    char spaceKey;

    for(int i=1; i<numBlocksVertical+1; i++)
    {
        for(int j=1; j<numBlocksHorizantal+1; j++)
        {
            currentFile>>spaceKey;
            mazeGrid[i][j]=spaceKey;
        }
    }    
}

void Board::displayBoard()
{
    char spaceKey;
    int xStart=0;
    int yStart=0;
    for(int i=1; i<numBlocksVertical+1; i++)
    {
        for(int j=1; j<numBlocksHorizantal+1; j++)
        {
            spaceKey=mazeGrid[i][j];
            factory[spaceKey]->displaySpace(indexToCoord(j), indexToCoord(i), mazeScene);
            if(spaceKey=='s')
            {
                xStart=j;
                yStart=i;
            }
        }
    }
    Cursor *animatedCursor = new Cursor(xStart, yStart);
    this->visibleCursor = new AnimatorCursor(animatedCursor);
    this->solutionFound = false;
    this->setPos(indexToCoord(xStart), indexToCoord(yStart));


}

void Board::dijkstra()
{
    Cursor *firstCursor = new Cursor(this->visibleCursor->animatedCursor);
    PathFinderData emptyData;
    int vectorXSize = this->numBlocksVertical+2;
    int vectorYSize = this->numBlocksHorizantal+2;
    int vectorZSize = 16; //total combinations of unlocked colors with 4 colors
    std::vector<std::vector<std::vector<PathFinderData>>> pathsTravelled(vectorXSize, std::vector<std::vector<PathFinderData>>(vectorYSize, std::vector<PathFinderData>(vectorZSize)));
    for(int i=0; i<vectorXSize; i++)
    {
        for(int j=0; j<vectorYSize; j++)
        {
            for(int k=0; k<vectorZSize; k++)
            {
                pathsTravelled[i][j][k] = emptyData;
            }
        }
    }
    std::queue<Cursor*> pathsQueue;
    pathsQueue.push(firstCursor);

    int startXIndex = firstCursor->xIndex;
    int startYIndex = firstCursor->yIndex;
    int startBitLock = firstCursor->bitLock;

    int flashIntervals = 1000;

    while(!this->solutionFound)//while(!this->solutionFound)
    {
        dijkstraTimerInternalFunction(pathsQueue, pathsTravelled);
        QTime dieTime= QTime::currentTime().addMSecs(flashIntervals);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    }
    dijkstraTimerInternalFunction(pathsQueue, pathsTravelled);
    QTime dieTime= QTime::currentTime().addMSecs(flashIntervals);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    findFinalPath(pathsTravelled, solutionXIndex, solutionYIndex, solutionBitLock, startXIndex, startYIndex, startBitLock, flashIntervals);

}

void Board::dijkstraTimerInternalFunction(std::queue<Board::Cursor *>& pathsQueue, std::vector<std::vector<std::vector<Board::PathFinderData> > >& pathsTravelled)
{
    int iMax = pathsQueue.size();
    for(int i=0; i<iMax; i++)
    {
        Cursor * currentCursor = pathsQueue.front();

        pathsQueue.pop();

        int xCurrent = currentCursor->xIndex;
        int yCurrent = currentCursor->yIndex;
        int currentBitLock = currentCursor->bitLock;
        int deltaX=0;
        int deltaY=0;

        deltaX=1;
        deltaY=0;
        int xDestination = xCurrent+deltaX;
        int yDestination = yCurrent+deltaY;
        if(factory[mazeGrid[yDestination][xDestination]]->moveMentAllowed(xCurrent, yCurrent, xDestination, yDestination, currentCursor, this) && !pathsTravelled[xDestination][yDestination][currentBitLock].travelled)
        {
            Cursor * nextCursor = new Cursor(currentCursor);
            moveTo(deltaX, deltaY, nextCursor);
            PathFinderData addPathFinderData(nextCursor->xIndex, nextCursor->yIndex, nextCursor->bitLock, xCurrent, yCurrent, currentBitLock, true);
            if(!pathsTravelled[nextCursor->xIndex][nextCursor->yIndex][nextCursor->bitLock].travelled)
            {

                pathsTravelled[nextCursor->xIndex][nextCursor->yIndex][nextCursor->bitLock] = addPathFinderData;
                pathsQueue.push(nextCursor);
            }
            else
            {
                delete nextCursor;
            }
        }
        deltaX=-1;
        deltaY=0;
        xDestination = xCurrent+deltaX;
        yDestination = yCurrent+deltaY;
        if(factory[mazeGrid[yDestination][xDestination]]->moveMentAllowed(xCurrent, yCurrent, xDestination, yDestination, currentCursor, this) && !pathsTravelled[xDestination][yDestination][currentBitLock].travelled)
        {
            Cursor * nextCursor = new Cursor(currentCursor);
            moveTo(deltaX, deltaY, nextCursor);
            PathFinderData addPathFinderData(nextCursor->xIndex, nextCursor->yIndex, nextCursor->bitLock, xCurrent, yCurrent, currentBitLock, true);
            if(!pathsTravelled[nextCursor->xIndex][nextCursor->yIndex][nextCursor->bitLock].travelled)
            {

                pathsTravelled[nextCursor->xIndex][nextCursor->yIndex][nextCursor->bitLock] = addPathFinderData;
                pathsQueue.push(nextCursor);
            }
            else
            {
                delete nextCursor;
            }
        }
        deltaX=0;
        deltaY=1;
        xDestination = xCurrent+deltaX;
        yDestination = yCurrent+deltaY;
        if(factory[mazeGrid[yDestination][xDestination]]->moveMentAllowed(xCurrent, yCurrent, xDestination, yDestination, currentCursor, this) && !pathsTravelled[xDestination][yDestination][currentBitLock].travelled)
        {
            Cursor * nextCursor = new Cursor(currentCursor);
            moveTo(deltaX, deltaY, nextCursor);
            PathFinderData addPathFinderData(nextCursor->xIndex, nextCursor->yIndex, nextCursor->bitLock, xCurrent, yCurrent, currentBitLock, true);
            if(!pathsTravelled[nextCursor->xIndex][nextCursor->yIndex][nextCursor->bitLock].travelled)
            {

                pathsTravelled[nextCursor->xIndex][nextCursor->yIndex][nextCursor->bitLock] = addPathFinderData;
                pathsQueue.push(nextCursor);
            }
            else
            {
                delete nextCursor;
            }
        }
        deltaX=0;
        deltaY=-1;
        xDestination = xCurrent+deltaX;
        yDestination = yCurrent+deltaY;
        if(factory[mazeGrid[yDestination][xDestination]]->moveMentAllowed(xCurrent, yCurrent, xDestination, yDestination, currentCursor, this) && !pathsTravelled[xDestination][yDestination][currentBitLock].travelled)
        {
            Cursor * nextCursor = new Cursor(currentCursor);
            moveTo(deltaX, deltaY, nextCursor);
            PathFinderData addPathFinderData(nextCursor->xIndex, nextCursor->yIndex, nextCursor->bitLock, xCurrent, yCurrent, currentBitLock, true);
            if(!pathsTravelled[nextCursor->xIndex][nextCursor->yIndex][nextCursor->bitLock].travelled)
            {

                pathsTravelled[nextCursor->xIndex][nextCursor->yIndex][nextCursor->bitLock] = addPathFinderData;
                pathsQueue.push(nextCursor);
            }
            else
            {
                delete nextCursor;
            }
        }

        lightSquare(xCurrent, yCurrent, currentCursor->bitLockToColor(), this);
        delete currentCursor;
    }

}

void Board::findFinalPath(std::vector<std::vector<std::vector<Board::PathFinderData> > > &pathsTravelled,int xIndex, int yIndex, int currentBitLock, int startXIndex, int startYIndex, int startBitLock, int flashInterval)
{
    if(xIndex!=startXIndex || yIndex!=startYIndex || currentBitLock!=startBitLock)
    {
        int lastXindex = pathsTravelled[xIndex][yIndex][currentBitLock].lastXIndex;
        int lastYindex = pathsTravelled[xIndex][yIndex][currentBitLock].lastYIndex;
        int lastBitLock = pathsTravelled[xIndex][yIndex][currentBitLock].lastBitLock;
        findFinalPath(pathsTravelled, lastXindex, lastYindex, lastBitLock, startXIndex, startYIndex, startBitLock, flashInterval);
    }

    lightSquare(xIndex, yIndex, Qt::red, this);
    QTime dieTime= QTime::currentTime().addMSecs(flashInterval);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);


}

bool Board::moveTo(int deltaX, int deltaY, Board::Cursor *gameCursor)
{
    int xCurrent = gameCursor->xIndex;
    int yCurrent = gameCursor->yIndex;

    int xDestination = xCurrent+deltaX;
    int yDestination = yCurrent+deltaY;

    if(factory[mazeGrid[yDestination][xDestination]]->moveToSpace(xCurrent, yCurrent, xDestination, yDestination, gameCursor, this))
    {
        gameCursor->xIndex = xDestination;
        gameCursor->yIndex = yDestination;
        return true;

    }
    return false;

}



Board::Cursor::Cursor(int startXIndex, int startYIndex)
{
    this->xIndex = startXIndex;
    this->yIndex = startYIndex;
}

Board::Cursor::Cursor(Board::Cursor *copy)
{
    this->xIndex = copy->xIndex;
    this->yIndex = copy->yIndex;
    this->bitLock = copy->bitLock;

}

QColor Board::Cursor::bitLockToColor()
{
    return QColor(bitLock*200/4%256, bitLock*200/16, 200-bitLock*200/16);
}

void Board::Cursor::unlockColor(char color)
{
    if(color=='b')
    {
        this->bitLock |= 1;
    }
    if(color=='r')
    {
        this->bitLock |= 2;
    }
    if(color=='y')
    {
        this->bitLock |= 4;
    }
    if(color=='g')
    {
        this->bitLock |= 8;
    }
}

bool Board::Cursor::colorUnlocked(char color)
{
    if(color=='b')
    {
        return (this->bitLock & 1) == 1;
    }
    if(color=='r')
    {
        return (this->bitLock & 2) == 2;
    }
    if(color=='y')
    {
        return (this->bitLock & 4) == 4;
    }
    if(color=='g')
    {
        return (this->bitLock & 8) == 8;
    }
    return false;
}
void Board::Space::playSoundEmptySpace(Board *mazeData)
{
    mazeData->soundEffect = new QMediaPlayer();
    mazeData->soundEffect->setMedia(QUrl("qrc:/sounds/MoveToFreeSpace.mp3"));
    mazeData->soundEffect->play();
}

void Board::Space::playSoundFullSpace(Board *mazeData)
{
    mazeData->soundEffect = new QMediaPlayer();
    mazeData->soundEffect->setMedia(QUrl("qrc:/sounds/MoveToBlockedSpace.mp3"));
    mazeData->soundEffect->play();
}

Board::Space::Space()
{
    this->id="0";
}

Board::Space::~Space()
{

}

void Board::EmptySpace::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, whiteBrush);

}

bool Board::EmptySpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    return true;
}

bool Board::EmptySpace::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCurso, Board *mazeData)
{
    return true;
}

void Board::EmptySpace::playSound(Board *mazeData)
{
    playSoundEmptySpace(mazeData);
}


void Board::FullSpace::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush darkGrayBrush(Qt::darkGray);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, Board::blockSize, blockSize, blackPen, darkGrayBrush);

}

bool Board::FullSpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{

    return false;
}

bool Board::FullSpace::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCurso, Board *mazeData)
{
    return false;
}

void Board::FullSpace::playSound(Board *mazeData)
{
    playSoundFullSpace(mazeData);
}

void Board::StartSpace::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush cyanBrush(Qt::cyan);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, cyanBrush);

}

bool Board::StartSpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    return true;
}

bool Board::StartSpace::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCurso, Board *mazeData)
{
    return true;
}

void Board::StartSpace::playSound(Board *mazeData)
{
    playSoundEmptySpace(mazeData);
}

void Board::FinishSpace::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush blackBrush(Qt::black);
    QBrush whiteBrush(Qt::white);

    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize/2, blockSize/2, blackPen, blackBrush);
    rectangle = mazeBoard->addRect(xCoord+blockSize/2, yCoord+blockSize/2, blockSize/2, blockSize/2, blackPen, blackBrush);

    rectangle = mazeBoard->addRect(xCoord+blockSize/2, yCoord, blockSize/2, blockSize/2, blackPen, whiteBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord+blockSize/2, blockSize/2, blockSize/2, blackPen, whiteBrush);


}

bool Board::FinishSpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    mazeData->solutionFound=true;
    mazeData->solutionXIndex=xDestination;
    mazeData->solutionYIndex=yDestination;
    mazeData->solutionBitLock=gameCursor->bitLock;
    return true;
}

bool Board::FinishSpace::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCurso, Board *mazeData)
{
    return true;
}

void Board::FinishSpace::playSound(Board *mazeData)
{
    mazeData->soundEffect = new QMediaPlayer();
    mazeData->soundEffect->setMedia(QUrl("qrc:/sounds/MoveToFinishedSpace.mp3"));
    mazeData->soundEffect->play();
}

void Board::AcceleratorSpace::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    QBrush blackBrush(Qt::black);
    QPen bluePen(Qt::blue);
    bluePen.setWidth(3);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, whiteBrush);
    rectangle = mazeBoard->addRect(xCoord+blockSize/4, yCoord+blockSize/4, blockSize/2, blockSize/2, bluePen, blackBrush);

}

bool Board::AcceleratorSpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    int deltaX=xDestination-xCurrent;
    int deltaY=yDestination-yCurrent;
    while(mazeData->factory[mazeData->mazeGrid[yDestination][xDestination]]->moveMentAllowed(xCurrent, yCurrent, xDestination, yDestination, gameCursor, mazeData))
    {
        xCurrent = xDestination;
        yCurrent = yDestination;
        xDestination += deltaX;
        yDestination += deltaY;
    }
    gameCursor->xIndex = xCurrent;
    gameCursor->yIndex = yCurrent;

    return false;
}

bool Board::AcceleratorSpace::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCurso, Board *mazeData)
{
    return true;
}

void Board::AcceleratorSpace::playSound(Board *mazeData)
{
    mazeData->soundEffect = new QMediaPlayer();
    mazeData->soundEffect->setMedia(QUrl("qrc:/sounds/MoveToAcceleratorSpace.mp3"));
    mazeData->soundEffect->play();
}



void Board::BlueKey::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    QBrush blueBrush(Qt::blue);
    QPen whitePen(Qt::white);
    whitePen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, whiteBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize/2, blockSize/2, whitePen, blueBrush);
    rectangle = mazeBoard->addRect(xCoord+blockSize/2, yCoord, blockSize/2, blockSize/2, whitePen, blueBrush);
    rectangle = mazeBoard->addRect(xCoord+blockSize/2, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, blueBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, blueBrush);
}

bool Board::BlueKey::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    gameCursor->unlockColor('b');
    return true;
}

bool Board::BlueKey::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    return true;
}

void Board::BlueKey::playSound(Board *mazeData)
{
    playSoundEmptySpace(mazeData);
}

void Board::BlueBlock::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, blueBrush);

}

bool Board::BlueBlock::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    return gameCursor->colorUnlocked('b');
}

bool Board::BlueBlock::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    return gameCursor->colorUnlocked('b');
}

void Board::BlueBlock::playSound(Board *mazeData)
{

}

void Board::RedKey::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    QBrush redBrush(Qt::red);
    QPen whitePen(Qt::white);
    whitePen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, whiteBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize/2, blockSize/2, whitePen, redBrush);
    rectangle = mazeBoard->addRect(xCoord+blockSize/2, yCoord, blockSize/2, blockSize/2, whitePen, redBrush);
    rectangle = mazeBoard->addRect(xCoord+blockSize/2, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, redBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, redBrush);

}

bool Board::RedKey::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    gameCursor->unlockColor('r');
    return true;
}

bool Board::RedKey::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    return true;
}

void Board::RedKey::playSound(Board *mazeData)
{
    playSoundEmptySpace(mazeData);
}

void Board::RedBlock::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, redBrush);

}

bool Board::RedBlock::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    return gameCursor->colorUnlocked('r');
}

bool Board::RedBlock::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    return gameCursor->colorUnlocked('r');
}

void Board::RedBlock::playSound(Board *mazeData)
{

}

void Board::YellowKey::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    QBrush yellowBrush(Qt::yellow);
    QPen whitePen(Qt::white);
    whitePen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, whiteBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize/2, blockSize/2, whitePen, yellowBrush);
    rectangle = mazeBoard->addRect(xCoord+blockSize/2, yCoord, blockSize/2, blockSize/2, whitePen, yellowBrush);
    rectangle = mazeBoard->addRect(xCoord+blockSize/2, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, yellowBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, yellowBrush);

}

bool Board::YellowKey::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    gameCursor->unlockColor('y');
    return true;
}

bool Board::YellowKey::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCurso, Board *mazeData)
{
    return true;
}

void Board::YellowKey::playSound(Board *mazeData)
{
    playSoundEmptySpace(mazeData);
}

void Board::YellowBlock::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush yellowBrush(Qt::yellow);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, yellowBrush);

}

bool Board::YellowBlock::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    return gameCursor->colorUnlocked('y');
}

bool Board::YellowBlock::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    return gameCursor->colorUnlocked('y');
}

void Board::YellowBlock::playSound(Board *mazeData)
{

}

void Board::GreenKey::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    QBrush greenBrush(Qt::yellow);
    QPen whitePen(Qt::white);
    whitePen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, whiteBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize/2, blockSize/2, whitePen, greenBrush);
    rectangle = mazeBoard->addRect(xCoord+blockSize/2, yCoord, blockSize/2, blockSize/2, whitePen, greenBrush);
    rectangle = mazeBoard->addRect(xCoord+blockSize/2, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, greenBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, greenBrush);

}

bool Board::GreenKey::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    gameCursor->unlockColor('g');
    return true;
}

bool Board::GreenKey::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    return true;
}

void Board::GreenKey::playSound(Board *mazeData)
{
    playSoundEmptySpace(mazeData);
}

void Board::GreenBlock::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush greenBrush(Qt::green);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, greenBrush);

}

bool Board::GreenBlock::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    return gameCursor->colorUnlocked('g');
}

bool Board::GreenBlock::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)
{
    return gameCursor->colorUnlocked('g');
}

void Board::GreenBlock::playSound(Board *mazeData)
{

}

void Board::keyPressEvent(QKeyEvent *event)
{
    QGraphicsItem::keyPressEvent(event);

    int deltaX=0;
    int deltaY=0;
    int currentX = this->visibleCursor->animatedCursor->xIndex;
    int currentY = this->visibleCursor->animatedCursor->yIndex;

    if(event->key() == Qt::Key_Left)
    {
        deltaX=-1;
    }
    if(event->key() == Qt::Key_Right)
    {
        deltaX=1;
        this->lightSquare(5, 5, Qt::green, this);
    }
    if(event->key() == Qt::Key_Up)
    {
        deltaY=-1;
    }
    if(event->key() == Qt::Key_Down)
    {
        deltaY=1;
    }
    if(event->key() == Qt::Key_A)
    {
        dijkstra();
        return;
    }
    if(event->key() == Qt::LeftButton)
    {
        dijkstra();
        return;
    }

    this->moveTo(deltaX, deltaY, this->visibleCursor->animatedCursor);
    int finalX = this->visibleCursor->animatedCursor->xIndex;
    int finalY = this->visibleCursor->animatedCursor->yIndex;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
    int distanceTravelled = std::max(abs(finalX-currentX), abs(finalY-currentY));
    if(distanceTravelled!=0)
    {
        animation->setDuration(250);
        animation->setStartValue(QPointF(indexToCoord(currentX),indexToCoord(currentY)));
        animation->setEndValue(QPointF(indexToCoord(currentX+deltaX), indexToCoord(currentY+deltaY)));

        animation->start();
        factory[mazeGrid[currentY+deltaY][currentX+deltaX]]->playSound(this);

    }
    if(distanceTravelled>1)
    {
        animation->setDuration(150*(distanceTravelled-2));
        animation->setStartValue(QPointF(indexToCoord(currentX+deltaX), indexToCoord(currentY+deltaY)));
        animation->setEndValue(QPointF(indexToCoord(finalX), indexToCoord(finalY)));

        animation->start();
    }


}

void Board::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    int xIndex = 10;//coordToIndex(event->pos().x());
    int yIndex = 10;//coordToIndex(event->pos().y());

    this->mazeGrid[yIndex][xIndex]='f';
    this->factory[this->mazeGrid[yIndex][xIndex]]->displaySpace(xIndex, yIndex, this->mazeScene);

}


void Board::lightSquare(int xIndex, int yIndex, QColor color, Board *mazeData)
{

    int fadeTime=400;
    LightUpSquare *square = new LightUpSquare(xIndex, yIndex, color);
    mazeData->mazeScene->addItem(square);
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    square->setGraphicsEffect(eff);
    QPropertyAnimation *fadeIn = new QPropertyAnimation(square,"opacity");
    fadeIn->setDuration(fadeTime);
    fadeIn->setStartValue(0);
    fadeIn->setEndValue(1);
    fadeIn->setEasingCurve(QEasingCurve::InBack);
    fadeIn->start(QPropertyAnimation::DeleteWhenStopped);

    QPropertyAnimation *fadeOut = new QPropertyAnimation(square,"opacity");
    fadeOut->setDuration(fadeTime);
    fadeOut->setStartValue(1);
    fadeOut->setEndValue(0);
    fadeOut->setEasingCurve(QEasingCurve::InBack);
    fadeOut->start(QPropertyAnimation::DeleteWhenStopped);

}

QRectF Board::boundingRect() const
{
    QRectF out(0, 0, blockSize, blockSize);
    return out;
}

Board::AnimatorCursor::AnimatorCursor(Board::Cursor *animatedCursor)
{
    this->animatedCursor = animatedCursor;
}

void Board::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
    QRectF recTopLeft = QRectF(blockSize/4, blockSize/4, blockSize/4, blockSize/4);
    QRectF recTopRight = QRectF(blockSize/2, blockSize/2, blockSize/4, blockSize/4);
    QRectF recBottomLeft = QRectF(blockSize/2, blockSize/4, blockSize/4, blockSize/4);
    QRectF recBottomRight = QRectF(blockSize/4, blockSize/2, blockSize/4, blockSize/4);

    QBrush grayBrush(Qt::gray);
    QBrush blueBrush(Qt::blue);
    QBrush redBrush(Qt::red);
    QBrush yellowBrush(Qt::yellow);
    QBrush greenBrush(Qt::green);

    QPen blackPen(Qt::black);
    painter->fillRect(recTopLeft, grayBrush);
    painter->fillRect(recTopRight, grayBrush);
    painter->fillRect(recBottomLeft, grayBrush);
    painter->fillRect(recBottomRight, grayBrush);
    if((this->visibleCursor->animatedCursor->bitLock & 1) == 1)
    {
        painter->fillRect(recTopLeft, blueBrush);

    }
    if((this->visibleCursor->animatedCursor->bitLock & 2) == 2)
    {
        painter->fillRect(recTopRight, redBrush);

    }
    if((this->visibleCursor->animatedCursor->bitLock & 4) == 4)
    {
        painter->fillRect(recBottomLeft, yellowBrush);

    }
    if((this->visibleCursor->animatedCursor->bitLock & 8) == 8)
    {
        painter->fillRect(recBottomRight, greenBrush);

    }

}

Board::LightUpSquare::LightUpSquare(int xIndex, int yIndex, QColor c)
{
    this->xIndex=xIndex;
    this->yIndex=yIndex;
    this->lightUpBrush = QBrush(c);
    this->setOpacity(0);
}

QRectF Board::LightUpSquare::boundingRect() const
{
    QRectF out(indexToCoord(xIndex), indexToCoord(yIndex), blockSize, blockSize);
    return out;
}

void Board::LightUpSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
    QRectF rec = this->boundingRect();
    painter->fillRect(rec, this->lightUpBrush);


}
int Board::indexToCoord(int index)
{
    return (index-1)*blockSize;
}

int Board::coordToIndex(double coord)
{
    return (coord/blockSize)+1;//FINSIH
}

Board::PathFinderData::PathFinderData()
{
    this->currentXIndex=0;
    this->currentYIndex=0;
    this->lastXIndex=0;
    this->lastYIndex=0;
    this->currentBitLock=0;
    this->lastBitLock=0;
    this->travelled=false;

}

Board::PathFinderData::PathFinderData(int currentXIndex, int CurrentYIndex, int currentBitLock, int lastXIndex, int lastYIndex,  int lastBitLock, bool travelled)
{
    this->currentXIndex=currentXIndex;
    this->currentYIndex=CurrentYIndex;
    this->currentBitLock=currentBitLock;
    this->lastXIndex=lastXIndex;
    this->lastYIndex=lastYIndex;
    this->lastBitLock=lastBitLock;
    this->travelled=travelled;

}


void Board::dijkstraTimerFunction(std::queue<Board::Cursor *> &pathsQueue, std::vector<std::vector<std::vector<Board::PathFinderData> > > &pathsTravelled, Board* mazeData)
{
    int iMax = pathsQueue.size();
    for(int i=0; i<iMax; i++)
    {
        Cursor * currentCursor = pathsQueue.front();
        Cursor * nextCursor =new Cursor(currentCursor);

        pathsQueue.pop();

        int xCurrent = currentCursor->xIndex;
        int yCurrent = currentCursor->yIndex;
        int currentBitLock = currentCursor->bitLock;
        int deltaX=0;
        int deltaY=0;

        deltaX=1;
        deltaY=0;
        int xDestination = xCurrent+deltaX;
        int yDestination = yCurrent+deltaY;
        if(mazeData->factory[mazeData->mazeGrid[yDestination][xDestination]]->moveMentAllowed(xCurrent, yCurrent, xDestination, yDestination, currentCursor, mazeData) && !pathsTravelled[xDestination][yDestination][currentBitLock].travelled)
        {
            Cursor * nextCursor = new Cursor(currentCursor);
            mazeData->moveTo(deltaX, deltaY, nextCursor);
            PathFinderData addPathFinderData(nextCursor->xIndex, nextCursor->yIndex, nextCursor->bitLock, xCurrent, yCurrent, currentBitLock, true);
            pathsTravelled[nextCursor->xIndex][nextCursor->yIndex][nextCursor->bitLock] = addPathFinderData;
            pathsQueue.push(nextCursor);
        }
        deltaX=-1;
        deltaY=0;
        xDestination = xCurrent+deltaX;
        yDestination = yCurrent+deltaY;
        if(mazeData->factory[mazeData->mazeGrid[yDestination][xDestination]]->moveMentAllowed(xCurrent, yCurrent, xDestination, yDestination, currentCursor, mazeData) && !pathsTravelled[xDestination][yDestination][currentBitLock].travelled)
        {
            Cursor * nextCursor = new Cursor(currentCursor);
            mazeData->moveTo(deltaX, deltaY, nextCursor);
            PathFinderData addPathFinderData(nextCursor->xIndex, nextCursor->yIndex, nextCursor->bitLock, xCurrent, yCurrent, currentBitLock, true);
            pathsTravelled[nextCursor->xIndex][nextCursor->yIndex][nextCursor->bitLock] = addPathFinderData;
            pathsQueue.push(nextCursor);
        }
        deltaX=0;
        deltaY=1;
        xDestination = xCurrent+deltaX;
        yDestination = yCurrent+deltaY;
        if(mazeData->factory[mazeData->mazeGrid[yDestination][xDestination]]->moveMentAllowed(xCurrent, yCurrent, xDestination, yDestination, currentCursor, mazeData) && !pathsTravelled[xDestination][yDestination][currentBitLock].travelled)
        {
            Cursor * nextCursor = new Cursor(currentCursor);
            mazeData->moveTo(deltaX, deltaY, nextCursor);
            PathFinderData addPathFinderData(nextCursor->xIndex, nextCursor->yIndex, nextCursor->bitLock, xCurrent, yCurrent, currentBitLock, true);
            pathsTravelled[nextCursor->xIndex][nextCursor->yIndex][nextCursor->bitLock] = addPathFinderData;
            pathsQueue.push(nextCursor);
        }
        deltaX=0;
        deltaY=-1;
        xDestination = xCurrent+deltaX;
        yDestination = yCurrent+deltaY;
        if(mazeData->factory[mazeData->mazeGrid[yDestination][xDestination]]->moveMentAllowed(xCurrent, yCurrent, xDestination, yDestination, currentCursor, mazeData) && !pathsTravelled[xDestination][yDestination][currentBitLock].travelled)
        {
            Cursor * nextCursor = new Cursor(currentCursor);
            mazeData->moveTo(deltaX, deltaY, nextCursor);
            PathFinderData addPathFinderData(nextCursor->xIndex, nextCursor->yIndex, nextCursor->bitLock, xCurrent, yCurrent, currentBitLock, true);
            pathsTravelled[nextCursor->xIndex][nextCursor->yIndex][nextCursor->bitLock] = addPathFinderData;
            pathsQueue.push(nextCursor);
        }

        mazeData->lightSquare(xCurrent, yCurrent, Qt::green, mazeData);
        delete currentCursor;
    }

}
