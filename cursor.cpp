#include "cursor.h"

#include <QDebug>
Cursor::Cursor()
{

}

Cursor::Cursor(int startXIndex, int startYIndex, int blockSize, std::vector<std::vector<char> > mazeGrid, std::unordered_map<char, Space *> factory)
{
    this->xIndex=startXIndex;
    this->yIndex=startYIndex;
    this->blockSize=blockSize;
    this->mazeGrid=mazeGrid;
    this->factory=factory;
}

bool Cursor::moveTo(int deltaX, int deltaY)
{
    int xDestination = this->xIndex+deltaX;
    int yDestination = this->yIndex+deltaY;

    //test if movement leaves boundaries
    int maxXIndex = this->mazeGrid.size()-1;
    int maxYIndex = this->mazeGrid[0].size()-1;
    if(xDestination<0 || xDestination>maxXIndex || yDestination<0 || yDestination>maxYIndex)
    {
        return false;
    }
    char spaceKey=this->mazeGrid[yDestination][xDestination];
    if(this->factory[spaceKey]->moveToSpace(this->xIndex, this->yIndex, xDestination, yDestination, this))
    {
        this->updateLocation(deltaX, deltaY);
        return true;
    }
    else
    {
        return false;
    }
}
void Cursor::updateLocation(int deltaX, int deltaY)
{
    int deltaXCoord=indexToCoord(deltaX);
    int deltaYCoord=indexToCoord(deltaY);
    setPos(x() +deltaXCoord, y()+deltaYCoord);
    this->xIndex += deltaX;
    this->yIndex += deltaY;

}
void Cursor::unlockColor(char color)
{
    if(color=='b')
    {
        this->blueUnlocked=true;
    }
    if(color=='r')
    {
        this->redUnlocked=true;
    }
    if(color=='y')
    {
        this->yellowUnlocked=true;
    }
    if(color=='g')
    {
        this->greenUnlocked=true;
    }
}

bool Cursor::colorUnlocked(char color)
{
    if(color=='b')
    {
        return this->blueUnlocked;
    }
    if(color=='r')
    {
        return this->redUnlocked;
    }
    if(color=='y')
    {
        return this->yellowUnlocked;
    }
    if(color=='g')
    {
        return this->greenUnlocked;
    }

}

void Cursor::keyPressEvent(QKeyEvent *event)
{
    int deltaX=0;
    int deltaY=0;
    if(event->key() == Qt::Key_Left)
    {
        deltaX=-1;
    }
    if(event->key() == Qt::Key_Right)
    {
        deltaX=1;
    }
    if(event->key() == Qt::Key_Up)
    {
        deltaY=-1;
    }
    if(event->key() == Qt::Key_Down)
    {
        deltaY=1;
    }
    this->moveTo(deltaX, deltaY);

}
int Cursor::indexToCoord(int index)
{
    return index*this->blockSize;
}
