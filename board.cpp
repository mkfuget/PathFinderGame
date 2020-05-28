#include "board.h"


Board::Board(int volume)
{
    this->volume=volume;

    this->numBlocksVertical = 20;
    this->numBlocksHorizantal = 20;
    std::unique_ptr<Space> factoryFullSpace(new FullSpace);
    std::unique_ptr<Space> factoryEmptySpace(new EmptySpace);
    std::unique_ptr<Space> factoryStartSpace(new StartSpace);
    std::unique_ptr<Space> factoryFinishSpace(new FinishSpace);
    std::unique_ptr<Space> factoryAcceleratorSpace(new AcceleratorSpace);
    std::unique_ptr<Space> factoryBlueKey(new BlueKey);
    std::unique_ptr<Space> factoryBlueBlock(new BlueBlock);
    std::unique_ptr<Space> factoryRedKey(new RedKey);
    std::unique_ptr<Space> factoryRedBlock(new RedBlock);
    std::unique_ptr<Space> factoryYellowKey(new YellowKey);
    std::unique_ptr<Space> factoryYellowBlock(new YellowBlock);
    std::unique_ptr<Space> factoryGreenKey(new GreenKey);
    std::unique_ptr<Space> factoryGreenBlock(new GreenBlock);

    factory['f'] = std::move(factoryFullSpace);
    factory['e'] = std::move(factoryEmptySpace);
    factory['s'] = std::move(factoryStartSpace);
    factory['x'] = std::move(factoryFinishSpace);
    factory['a'] = std::move(factoryAcceleratorSpace);
    factory['b'] = std::move(factoryBlueKey);
    factory['B'] = std::move(factoryBlueBlock);
    factory['r'] = std::move(factoryRedKey);
    factory['R'] = std::move(factoryRedBlock);
    factory['y'] = std::move(factoryYellowKey);
    factory['Y'] = std::move(factoryYellowBlock);
    factory['g'] = std::move(factoryGreenKey);
    factory['G'] = std::move(factoryGreenBlock);

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
        }
    }
    this->customBlock='f';
    this->inEditMode = true;
    this->soundEffect = new QMediaPlayer();
    this->soundEffect->setVolume(volume);
    //this->visibleCursor = new a
    this->displayBoard();
    this->addItem(this->visibleCursor);
    this->visibleCursor->setFlag(QGraphicsItem::ItemIsFocusable);
    this->visibleCursor->setFocus();



}

Board::Board(char c)
{
    this->numBlocksVertical = 1;
    std::unique_ptr<Space> factoryFinishSpace(new FinishSpace);
    std::unique_ptr<Space> factoryAcceleratorSpace(new AcceleratorSpace);
    std::unique_ptr<Space> factoryBlueKey(new BlueKey);
    std::unique_ptr<Space> factoryBlueBlock(new BlueBlock);

    factory['x'] = std::move(factoryFinishSpace);
    factory['a'] = std::move(factoryAcceleratorSpace);
    factory['b'] = std::move(factoryBlueKey);
    factory['B'] = std::move(factoryBlueBlock);

    factory[c]->displaySpace(indexToCoord(0), indexToCoord(0), this);
}

Board::~Board()
{
    std::unordered_map<char, Space*>::iterator mapDeleter;
    delete soundEffect;
    delete visibleCursor;
}

Board::Board(std::string fileName, int numBlocksVertical, int numBlocksHorizantal, int volume)
{

    this->volume = volume;
    this->numBlocksVertical = numBlocksVertical;
    this->numBlocksHorizantal = numBlocksHorizantal;

    std::unique_ptr<Space> factoryFullSpace(new FullSpace);
    std::unique_ptr<Space> factoryEmptySpace(new EmptySpace);
    std::unique_ptr<Space> factoryStartSpace(new StartSpace);
    std::unique_ptr<Space> factoryFinishSpace(new FinishSpace);
    std::unique_ptr<Space> factoryAcceleratorSpace(new AcceleratorSpace);
    std::unique_ptr<Space> factoryBlueKey(new BlueKey);
    std::unique_ptr<Space> factoryBlueBlock(new BlueBlock);
    std::unique_ptr<Space> factoryRedKey(new RedKey);
    std::unique_ptr<Space> factoryRedBlock(new RedBlock);
    std::unique_ptr<Space> factoryYellowKey(new YellowKey);
    std::unique_ptr<Space> factoryYellowBlock(new YellowBlock);
    std::unique_ptr<Space> factoryGreenKey(new GreenKey);
    std::unique_ptr<Space> factoryGreenBlock(new GreenBlock);

    factory['f'] = std::move(factoryFullSpace);
    factory['e'] = std::move(factoryEmptySpace);
    factory['s'] = std::move(factoryStartSpace);
    factory['x'] = std::move(factoryFinishSpace);
    factory['a'] = std::move(factoryAcceleratorSpace);
    factory['b'] = std::move(factoryBlueKey);
    factory['B'] = std::move(factoryBlueBlock);
    factory['r'] = std::move(factoryRedKey);
    factory['R'] = std::move(factoryRedBlock);
    factory['y'] = std::move(factoryYellowKey);
    factory['Y'] = std::move(factoryYellowBlock);
    factory['g'] = std::move(factoryGreenKey);
    factory['G'] = std::move(factoryGreenBlock);

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
    this->inEditMode = false;
    this->customBlock='f';
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

void Board::setCustomBlock(char c)
{
    this->customBlock = c;
}

void Board::setToEditMode()
{
    this->inEditMode = true;
}

void Board::setToPlayMode()
{
    this->inEditMode = false;
}

void Board::displayBoard()
{
    char spaceKey;
    int xStart=10;
    int yStart=10;
    for(int i=1; i<numBlocksVertical+1; i++)
    {
        for(int j=1; j<numBlocksHorizantal+1; j++)
        {
            spaceKey=mazeGrid[i][j];
            factory[spaceKey]->displaySpace(indexToCoord(j), indexToCoord(i), this);
            if(spaceKey=='s')
            {
                xStart=j;
                yStart=i;
            }
            if(spaceKey=='x')
            {
                this->solutionXIndex=j;
                this->solutionYIndex=i;
            }
        }
    }
    Cursor *animatedCursor = new Cursor(xStart, yStart, this->solutionXIndex, this->solutionYIndex);
    this->visibleCursor = new AnimatorCursor(animatedCursor);
    this->solutionFound = false;this->addItem(this->visibleCursor);
    this->visibleCursor->setPos(indexToCoord(xStart), indexToCoord(yStart));
    this->visibleCursor->setFlag(QGraphicsItem::ItemIsFocusable);
    this->visibleCursor->setFocus();

}

void Board::dijkstra()
{
    Cursor firstCursor(this->visibleCursor->animatedCursor);
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
    std::priority_queue<Cursor> pathsQueue;
    pathsQueue.push(firstCursor);

    int startXIndex = firstCursor.xIndex;
    int startYIndex = firstCursor.yIndex;
    int startBitLock = firstCursor.bitLock;

    int flashIntervals = 400;

    while(!this->solutionFound)//while(!this->solutionFound)
    {
        dijkstraTimerInternalFunction(pathsQueue, pathsTravelled);
        this->delay(flashIntervals);

    }
    dijkstraTimerInternalFunction(pathsQueue, pathsTravelled);
    this->delay(flashIntervals);

    findFinalPath(pathsTravelled, solutionXIndex, solutionYIndex, solutionBitLock, startXIndex, startYIndex, startBitLock, flashIntervals);

}

void Board::dijkstraTimerInternalFunction(std::priority_queue<Cursor> &pathsQueue, std::vector<std::vector<std::vector<Board::PathFinderData> > >& pathsTravelled)
{
    int iMax = pathsQueue.size();
    for(int i=0; i<iMax; i++)
    {
        Cursor currentCursor = pathsQueue.top();

        pathsQueue.pop();

        int xCurrent = currentCursor.xIndex;
        int yCurrent = currentCursor.yIndex;
        int currentBitLock = currentCursor.bitLock;
        int deltaX=0;
        int deltaY=0;

        deltaX=1;
        deltaY=0;
        int xDestination = xCurrent+deltaX;
        int yDestination = yCurrent+deltaY;
        if(factory[mazeGrid[yDestination][xDestination]]->moveMentAllowed(xCurrent, yCurrent, xDestination, yDestination, currentCursor, this) && !pathsTravelled[xDestination][yDestination][currentBitLock].travelled)
        {
            Cursor nextCursor(currentCursor);
            moveTo(deltaX, deltaY, nextCursor);
            PathFinderData addPathFinderData(nextCursor.xIndex, nextCursor.yIndex, nextCursor.bitLock, xCurrent, yCurrent, currentBitLock, true);
            if(!pathsTravelled[nextCursor.xIndex][nextCursor.yIndex][nextCursor.bitLock].travelled)
            {

                pathsTravelled[nextCursor.xIndex][nextCursor.yIndex][nextCursor.bitLock] = addPathFinderData;
                pathsQueue.push(nextCursor);
            }
        }
        deltaX=-1;
        deltaY=0;
        xDestination = xCurrent+deltaX;
        yDestination = yCurrent+deltaY;
        if(factory[mazeGrid[yDestination][xDestination]]->moveMentAllowed(xCurrent, yCurrent, xDestination, yDestination, currentCursor, this) && !pathsTravelled[xDestination][yDestination][currentBitLock].travelled)
        {
            Cursor nextCursor(currentCursor);
            moveTo(deltaX, deltaY, nextCursor);
            PathFinderData addPathFinderData(nextCursor.xIndex, nextCursor.yIndex, nextCursor.bitLock, xCurrent, yCurrent, currentBitLock, true);
            if(!pathsTravelled[nextCursor.xIndex][nextCursor.yIndex][nextCursor.bitLock].travelled)
            {

                pathsTravelled[nextCursor.xIndex][nextCursor.yIndex][nextCursor.bitLock] = addPathFinderData;
                pathsQueue.push(nextCursor);
            }
        }
        deltaX=0;
        deltaY=1;
        xDestination = xCurrent+deltaX;
        yDestination = yCurrent+deltaY;
        if(factory[mazeGrid[yDestination][xDestination]]->moveMentAllowed(xCurrent, yCurrent, xDestination, yDestination, currentCursor, this) && !pathsTravelled[xDestination][yDestination][currentBitLock].travelled)
        {
            Cursor nextCursor(currentCursor);
            moveTo(deltaX, deltaY, nextCursor);
            PathFinderData addPathFinderData(nextCursor.xIndex, nextCursor.yIndex, nextCursor.bitLock, xCurrent, yCurrent, currentBitLock, true);
            if(!pathsTravelled[nextCursor.xIndex][nextCursor.yIndex][nextCursor.bitLock].travelled)
            {

                pathsTravelled[nextCursor.xIndex][nextCursor.yIndex][nextCursor.bitLock] = addPathFinderData;
                pathsQueue.push(nextCursor);
            }
        }
        deltaX=0;
        deltaY=-1;
        xDestination = xCurrent+deltaX;
        yDestination = yCurrent+deltaY;
        if(factory[mazeGrid[yDestination][xDestination]]->moveMentAllowed(xCurrent, yCurrent, xDestination, yDestination, currentCursor, this) && !pathsTravelled[xDestination][yDestination][currentBitLock].travelled)
        {
            Cursor nextCursor(currentCursor);
            moveTo(deltaX, deltaY, nextCursor);
            PathFinderData addPathFinderData(nextCursor.xIndex, nextCursor.yIndex, nextCursor.bitLock, xCurrent, yCurrent, currentBitLock, true);
            if(!pathsTravelled[nextCursor.xIndex][nextCursor.yIndex][nextCursor.bitLock].travelled)
            {

                pathsTravelled[nextCursor.xIndex][nextCursor.yIndex][nextCursor.bitLock] = addPathFinderData;
                pathsQueue.push(nextCursor);
            }
        }
        lightSquare(xCurrent, yCurrent, currentCursor.bitLockToColor(), this);
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

    lightSquare(xIndex, yIndex, Qt::magenta, this);
    this->delay(flashInterval);

}

void Board::exportCurrentLevel()
{
    std::ofstream myFile;
    myFile.open("outputLevel.txt");
    for(int i=1; i<numBlocksVertical+1; i++)
    {
        for(int j=1; j<numBlocksHorizantal+1; j++)
        {
            myFile << mazeGrid[i][j];
        }
    }
    myFile.close();
}

bool Board::moveTo(int deltaX, int deltaY, Board::Cursor &gameCursor)
{
    int xCurrent = gameCursor.xIndex;
    int yCurrent = gameCursor.yIndex;

    int xDestination = xCurrent+deltaX;
    int yDestination = yCurrent+deltaY;

    if(factory[mazeGrid[yDestination][xDestination]]->moveToSpace(xCurrent, yCurrent, xDestination, yDestination, gameCursor, this))
    {
        gameCursor.xIndex = xDestination;
        gameCursor.yIndex = yDestination;
        xCurrent = xDestination;
        yCurrent = yDestination;
        gameCursor.distanceTravelled++;
        return true;

    }
    return false;

}



Board::Cursor::Cursor()
{

}

Board::Cursor::Cursor(int startXIndex, int startYIndex, int xSolution, int ySolution)
{
    this->xIndex = startXIndex;
    this->yIndex = startYIndex;
    this->distanceTravelled=0;
    this->xSolution = xSolution;
    this->ySolution = ySolution;
}

Board::Cursor::Cursor(Board::Cursor *copy)
{
    this->xIndex = copy->xIndex;
    this->yIndex = copy->yIndex;
    this->bitLock = copy->bitLock;
    this->distanceTravelled = copy->distanceTravelled;
    this->xSolution = copy->xSolution;
    this->ySolution = copy->ySolution;
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

bool Board::Cursor::operator<(const Cursor &other) const
{
    if(other.pathFindingType == 'x')
    {
        double lOut = this->distanceTravelled + 0.4*(abs((this->xIndex)-(this->xSolution))+abs((this->yIndex)-this->ySolution));
        double rOut = other.distanceTravelled + 0.4*(abs((other.xIndex)-(other.xSolution))+abs((other.yIndex)-other.ySolution));

        return rOut < lOut;

    }
    else if(other.pathFindingType == 'z')
    {
        return other.distanceTravelled < this->distanceTravelled;

    }
    return true;
}
void Board::Space::playSoundEmptySpace(Board *mazeData)
{
    mazeData->soundEffect = new QMediaPlayer();
    mazeData->soundEffect->setVolume(mazeData->volume);

    mazeData->soundEffect->setMedia(QUrl("qrc:/sounds/MoveToFreeSpace.mp3"));
    mazeData->soundEffect->play();
}

void Board::Space::playSoundFullSpace(Board *mazeData)
{
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

void Board::EmptySpace::displaySpace(int xCoord, int yCoord, Board *mazeData)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, whiteBrush);

}

bool Board::EmptySpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return true;
}

bool Board::EmptySpace::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return true;
}

void Board::EmptySpace::playSound(Board *mazeData)
{
    playSoundEmptySpace(mazeData);
}


void Board::FullSpace::displaySpace(int xCoord, int yCoord, Board *mazeData)
{
    QGraphicsRectItem * rectangle;
    QBrush darkGrayBrush(Qt::darkGray);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeData->addRect(xCoord, yCoord, Board::blockSize, blockSize, blackPen, darkGrayBrush);

}

bool Board::FullSpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{

    return false;
}

bool Board::FullSpace::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return false;
}

void Board::FullSpace::playSound(Board *mazeData)
{
    playSoundFullSpace(mazeData);
}

void Board::StartSpace::displaySpace(int xCoord, int yCoord, Board *mazeData)
{
    QGraphicsRectItem * rectangle;
    QBrush cyanBrush(Qt::cyan);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, cyanBrush);

}

bool Board::StartSpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return true;
}

bool Board::StartSpace::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return true;
}

void Board::StartSpace::playSound(Board *mazeData)
{
    playSoundEmptySpace(mazeData);
}

void Board::FinishSpace::displaySpace(int xCoord, int yCoord, Board *mazeData)
{
    QGraphicsRectItem * rectangle;
    QBrush blackBrush(Qt::black);
    QBrush whiteBrush(Qt::white);

    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize/2, blockSize/2, blackPen, blackBrush);
    rectangle = mazeData->addRect(xCoord+blockSize/2, yCoord+blockSize/2, blockSize/2, blockSize/2, blackPen, blackBrush);

    rectangle = mazeData->addRect(xCoord+blockSize/2, yCoord, blockSize/2, blockSize/2, blackPen, whiteBrush);
    rectangle = mazeData->addRect(xCoord, yCoord+blockSize/2, blockSize/2, blockSize/2, blackPen, whiteBrush);


}

bool Board::FinishSpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    mazeData->solutionFound=true;
    mazeData->solutionXIndex=xDestination;
    mazeData->solutionYIndex=yDestination;
    mazeData->solutionBitLock=gameCursor.bitLock;
    return true;
}

bool Board::FinishSpace::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return true;
}

void Board::FinishSpace::playSound(Board *mazeData)
{
    mazeData->soundEffect = new QMediaPlayer();
    mazeData->soundEffect->setVolume(mazeData->volume);
    mazeData->soundEffect->setMedia(QUrl("qrc:/sounds/MoveToFinishedSpace.mp3"));
    mazeData->soundEffect->play();
}

void Board::AcceleratorSpace::displaySpace(int xCoord, int yCoord, Board *mazeData)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    QBrush blackBrush(Qt::black);
    QPen bluePen(Qt::blue);
    bluePen.setWidth(3);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, whiteBrush);
    rectangle = mazeData->addRect(xCoord+blockSize/4, yCoord+blockSize/4, blockSize/2, blockSize/2, bluePen, blackBrush);

}

bool Board::AcceleratorSpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    if(xCurrent == xDestination && yCurrent == yDestination)
    {
        return false;
    }
    int deltaX=xDestination-xCurrent;
    int deltaY=yDestination-yCurrent;
    while(mazeData->factory[mazeData->mazeGrid[yDestination][xDestination]]->moveMentAllowed(xCurrent, yCurrent, xDestination, yDestination, gameCursor, mazeData))
    {
        xCurrent = xDestination;
        yCurrent = yDestination;
        xDestination += deltaX;
        yDestination += deltaY;
    }
    gameCursor.xIndex = xCurrent;
    gameCursor.yIndex = yCurrent;
    mazeData->factory[mazeData->mazeGrid[yCurrent][xCurrent]]->moveToSpace(xCurrent, yCurrent, xCurrent, yCurrent, gameCursor, mazeData);
    return false;
}

bool Board::AcceleratorSpace::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return true;
}

void Board::AcceleratorSpace::playSound(Board *mazeData)
{
    mazeData->soundEffect = new QMediaPlayer();
    mazeData->soundEffect->setVolume(mazeData->volume);
    mazeData->soundEffect->setMedia(QUrl("qrc:/sounds/MoveToAcceleratorSpace.mp3"));
    mazeData->soundEffect->play();
}



void Board::BlueKey::displaySpace(int xCoord, int yCoord, Board *mazeData)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    QBrush blueBrush(Qt::blue);
    QPen whitePen(Qt::white);
    whitePen.setWidth(1);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, whiteBrush);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize/2, blockSize/2, whitePen, blueBrush);
    rectangle = mazeData->addRect(xCoord+blockSize/2, yCoord, blockSize/2, blockSize/2, whitePen, blueBrush);
    rectangle = mazeData->addRect(xCoord+blockSize/2, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, blueBrush);
    rectangle = mazeData->addRect(xCoord, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, blueBrush);
}

bool Board::BlueKey::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    gameCursor.unlockColor('b');
    return true;
}

bool Board::BlueKey::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return true;
}

void Board::BlueKey::playSound(Board *mazeData)
{
    playSoundEmptySpace(mazeData);
}

void Board::BlueBlock::displaySpace(int xCoord, int yCoord, Board *mazeData)
{
    QGraphicsRectItem * rectangle;
    QBrush blueBrush(Qt::blue);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, blueBrush);

}

bool Board::BlueBlock::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return gameCursor.colorUnlocked('b');
}

bool Board::BlueBlock::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return gameCursor.colorUnlocked('b');
}

void Board::BlueBlock::playSound(Board *mazeData)
{

}

void Board::RedKey::displaySpace(int xCoord, int yCoord, Board *mazeData)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    QBrush redBrush(Qt::red);
    QPen whitePen(Qt::white);
    whitePen.setWidth(1);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, whiteBrush);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize/2, blockSize/2, whitePen, redBrush);
    rectangle = mazeData->addRect(xCoord+blockSize/2, yCoord, blockSize/2, blockSize/2, whitePen, redBrush);
    rectangle = mazeData->addRect(xCoord+blockSize/2, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, redBrush);
    rectangle = mazeData->addRect(xCoord, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, redBrush);

}

bool Board::RedKey::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    gameCursor.unlockColor('r');
    return true;
}

bool Board::RedKey::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return true;
}

void Board::RedKey::playSound(Board *mazeData)
{
    playSoundEmptySpace(mazeData);
}

void Board::RedBlock::displaySpace(int xCoord, int yCoord, Board *mazeData)
{
    QGraphicsRectItem * rectangle;
    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, redBrush);

}

bool Board::RedBlock::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return gameCursor.colorUnlocked('r');
}

bool Board::RedBlock::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return gameCursor.colorUnlocked('r');
}

void Board::RedBlock::playSound(Board *mazeData)
{

}

void Board::YellowKey::displaySpace(int xCoord, int yCoord, Board *mazeData)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    QBrush yellowBrush(Qt::yellow);
    QPen whitePen(Qt::white);
    whitePen.setWidth(1);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, whiteBrush);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize/2, blockSize/2, whitePen, yellowBrush);
    rectangle = mazeData->addRect(xCoord+blockSize/2, yCoord, blockSize/2, blockSize/2, whitePen, yellowBrush);
    rectangle = mazeData->addRect(xCoord+blockSize/2, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, yellowBrush);
    rectangle = mazeData->addRect(xCoord, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, yellowBrush);

}

bool Board::YellowKey::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    gameCursor.unlockColor('y');
    return true;
}

bool Board::YellowKey::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return true;
}

void Board::YellowKey::playSound(Board *mazeData)
{
    playSoundEmptySpace(mazeData);
}

void Board::YellowBlock::displaySpace(int xCoord, int yCoord, Board *mazeData)
{
    QGraphicsRectItem * rectangle;
    QBrush yellowBrush(Qt::yellow);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, yellowBrush);

}

bool Board::YellowBlock::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return gameCursor.colorUnlocked('y');
}

bool Board::YellowBlock::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return gameCursor.colorUnlocked('y');
}

void Board::YellowBlock::playSound(Board *mazeData)
{

}

void Board::GreenKey::displaySpace(int xCoord, int yCoord, Board *mazeData)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    QBrush greenBrush(Qt::green);
    QPen whitePen(Qt::white);
    whitePen.setWidth(1);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, whiteBrush);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize/2, blockSize/2, whitePen, greenBrush);
    rectangle = mazeData->addRect(xCoord+blockSize/2, yCoord, blockSize/2, blockSize/2, whitePen, greenBrush);
    rectangle = mazeData->addRect(xCoord+blockSize/2, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, greenBrush);
    rectangle = mazeData->addRect(xCoord, yCoord+blockSize/2, blockSize/2, blockSize/2, whitePen, greenBrush);

}

bool Board::GreenKey::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    gameCursor.unlockColor('g');
    return true;
}

bool Board::GreenKey::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return true;
}

void Board::GreenKey::playSound(Board *mazeData)
{
    playSoundEmptySpace(mazeData);
}

void Board::GreenBlock::displaySpace(int xCoord, int yCoord, Board *mazeData)
{
    QGraphicsRectItem * rectangle;
    QBrush greenBrush(Qt::green);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeData->addRect(xCoord, yCoord, blockSize, blockSize, blackPen, greenBrush);

}

bool Board::GreenBlock::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return gameCursor.colorUnlocked('g');
}

bool Board::GreenBlock::moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor &gameCursor, Board *mazeData)
{
    return gameCursor.colorUnlocked('g');
}

void Board::GreenBlock::playSound(Board *mazeData)
{

}

void Board::keyPressEvent(QKeyEvent *event)
{
    if(!this->inEditMode)
    {
        QGraphicsScene::keyPressEvent(event);
        this->processesRunning++;
        int deltaX=0;
        int deltaY=0;
        int currentX = this->visibleCursor->animatedCursor.xIndex;
        int currentY = this->visibleCursor->animatedCursor.yIndex;

        if(event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
        {
            deltaX=-1;
        }
        if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
        {
            deltaX=1;
        }
        if(event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
        {
            deltaY=-1;
        }
        if(event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
        {
            deltaY=1;
        }
        if(event->key() == Qt::Key_Z || event->key() == Qt::Key_X)//handles pathfinding algorithms
        {
            if(event->key() == Qt::Key_Z)
            {
                this->visibleCursor->animatedCursor.pathFindingType = 'z';
            }
            if(event->key() == Qt::Key_X)
            {
                this->visibleCursor->animatedCursor.pathFindingType = 'x';
            }
            if(pathFindingProcessRunning)
            {
                this->processesTerminated = true;
                this->pathFindingProcessRunning = true;
                return;

            }
            this->processesTerminated = false;
            this->pathFindingProcessRunning=true;
            this->solutionFound=false;
            dijkstra();
            this->processesRunning--;
            this->pathFindingProcessRunning=false;
            return;
        }
        if(event->key() == Qt::Key_R)
        {
            this->processesTerminated = true;
            this->displayBoard();
            this->processesRunning--;
            return;
        }
        if(event->key() == Qt::Key_N)
        {
            this->exportCurrentLevel();
            this->processesRunning--;
            return;
        }
        if(event->key() == Qt::Key_Q)
        {
            this->terminateProcesses();
            this->processesRunning--;
            return;
        }


        this->moveTo(deltaX, deltaY, this->visibleCursor->animatedCursor);
        int finalX = this->visibleCursor->animatedCursor.xIndex;
        int finalY = this->visibleCursor->animatedCursor.yIndex;
        QPropertyAnimation *animation = new QPropertyAnimation(this->visibleCursor, "pos");
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
            int travelTime = 150*(distanceTravelled-2);
            animation->setDuration(travelTime);
            animation->setStartValue(QPointF(indexToCoord(currentX+deltaX), indexToCoord(currentY+deltaY)));
            animation->setEndValue(QPointF(indexToCoord(finalX), indexToCoord(finalY)));

            animation->start();
            this->delay(travelTime);//queue up the arrivalk sound when the animation ends
            factory[mazeGrid[finalY][finalX]]->playSound(this);

        }
        this->processesRunning--;
    }

}

void Board::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int xIndex = coordToIndex(event->pos().x());

    int yIndex = coordToIndex(event->pos().y());

    QGraphicsScene::mousePressEvent(event);
    if(this->inEditMode)
    {
        int xIndex = coordToIndex(event->pos().x());
        int yIndex = coordToIndex(event->pos().y());
        if(xIndex>=1 &&xIndex<numBlocksVertical+1 && yIndex>=1 &&yIndex<numBlocksHorizantal+1 && this->mazeGrid[yIndex][xIndex]!=this->customBlock)
        {
            this->mazeGrid[yIndex][xIndex]=this->customBlock;
            this->factory[this->mazeGrid[yIndex][xIndex]]->displaySpace(indexToCoord(xIndex), indexToCoord(yIndex), this);
        }
    }
}

void Board::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if(this->inEditMode)
    {
        if(event->buttons() == Qt :: LeftButton)
        {
            QGraphicsScene::mousePressEvent(event);
            int xIndex = coordToIndex(event->scenePos().x());
            int yIndex = coordToIndex(event->scenePos().y());
            if(xIndex>=1 &&xIndex<numBlocksVertical+1 && yIndex>=1 && yIndex<numBlocksHorizantal+1 && this->mazeGrid[yIndex][xIndex]!=this->customBlock)
            {
                this->mazeGrid[yIndex][xIndex]=this->customBlock;
                this->factory[this->mazeGrid[yIndex][xIndex]]->displaySpace(indexToCoord(xIndex), indexToCoord(yIndex), this);
            }
        }
    }

}

void Board::setSoundEffectVolume(int volume)
{
    this->volume=volume;
}

void Board::terminateProcesses()
{
    this->processesTerminated = true;
}

void Board::delay(int time)
{
    if(!processesTerminated)
    {
        QTime dieTime= QTime::currentTime().addMSecs(time);
        while (QTime::currentTime() <dieTime)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }
}


void Board::lightSquare(int xIndex, int yIndex, QColor color, Board *mazeData)
{

    if(!this->processesTerminated)
    {
        int fadeTime=800;
        LightUpSquare *square = new LightUpSquare(xIndex, yIndex, color);
        mazeData->addItem(square);
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
}

QRectF Board::AnimatorCursor::boundingRect() const
{
    QRectF out(0, 0, blockSize, blockSize);
    return out;
}

Board::AnimatorCursor::AnimatorCursor()
{

}

Board::AnimatorCursor::AnimatorCursor(Board::Cursor animatedCursor)
{
    this->animatedCursor = animatedCursor;
}

void Board::AnimatorCursor::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
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
    if((this->animatedCursor.bitLock & 1) == 1)
    {
        painter->fillRect(recTopLeft, blueBrush);

    }
    if((this->animatedCursor.bitLock & 2) == 2)
    {
        painter->fillRect(recTopRight, redBrush);

    }
    if((this->animatedCursor.bitLock & 4) == 4)
    {
        painter->fillRect(recBottomLeft, yellowBrush);

    }
    if((this->animatedCursor.bitLock & 8) == 8)
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
    if(coord==0.0)//this means the selection is out of bounds
    {
        return -1;
    }
    return (coord/blockSize)+1;
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


