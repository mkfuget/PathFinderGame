#include "space.h"

Space::Space()
{
    this->id="0";
    this->blockSize=0;
}

Space::~Space()
{

}
void Space::setData(std::string id, int blockSize)
{
    this->id=id;
    this->blockSize=blockSize;
}

void EmptySpace::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize, this->blockSize, blackPen, whiteBrush);

}

bool EmptySpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor)
{
    return true;
}


void FullSpace::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush darkGrayBrush(Qt::darkGray);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize, this->blockSize, blackPen, darkGrayBrush);

}

bool FullSpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor)
{
    return false;
}

void StartSpace::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush cyanBrush(Qt::cyan);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize, this->blockSize, blackPen, cyanBrush);

}

bool StartSpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor)
{
    return true;
}

void FinishSpace::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize/2, this->blockSize/2, blackPen, blackBrush);
    rectangle = mazeBoard->addRect(xCoord+this->blockSize/2, yCoord+this->blockSize/2, this->blockSize/2, this->blockSize/2, blackPen, blackBrush);


}

bool FinishSpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor)
{
    return true;
}

void AcceleratorSpace::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    QBrush blackBrush(Qt::black);
    QPen bluePen(Qt::blue);
    bluePen.setWidth(3);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize, this->blockSize, blackPen, whiteBrush);
    rectangle = mazeBoard->addRect(xCoord+this->blockSize/4, yCoord+this->blockSize/4, this->blockSize/2, this->blockSize/2, bluePen, blackBrush);

}

bool AcceleratorSpace::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor)
{
    int deltaX=xDestination-xCurrent;
    int deltaY=yDestination-yCurrent;
    gameCursor->updateLocation(deltaX, deltaY);
    while(gameCursor->moveTo(deltaX, deltaY))
    {

    }
    return false;
}


void BlueKey::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    QBrush blueBrush(Qt::blue);
    QPen whitePen(Qt::white);
    whitePen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize, this->blockSize, blackPen, whiteBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize/2, this->blockSize/2, whitePen, blueBrush);
    rectangle = mazeBoard->addRect(xCoord+this->blockSize/2, yCoord, this->blockSize/2, this->blockSize/2, whitePen, blueBrush);
    rectangle = mazeBoard->addRect(xCoord+this->blockSize/2, yCoord+this->blockSize/2, this->blockSize/2, this->blockSize/2, whitePen, blueBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord+this->blockSize/2, this->blockSize/2, this->blockSize/2, whitePen, blueBrush);
}

bool BlueKey::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor)
{
    gameCursor->unlockColor('b');
    return true;
}

void BlueBlock::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush cyanBrush(Qt::cyan);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize, this->blockSize, blackPen, cyanBrush);

}

bool BlueBlock::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor)
{
    return gameCursor->colorUnlocked('b');
}

void RedKey::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    QBrush redBrush(Qt::red);
    QPen whitePen(Qt::white);
    whitePen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize, this->blockSize, blackPen, whiteBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize/2, this->blockSize/2, whitePen, redBrush);
    rectangle = mazeBoard->addRect(xCoord+this->blockSize/2, yCoord, this->blockSize/2, this->blockSize/2, whitePen, redBrush);
    rectangle = mazeBoard->addRect(xCoord+this->blockSize/2, yCoord+this->blockSize/2, this->blockSize/2, this->blockSize/2, whitePen, redBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord+this->blockSize/2, this->blockSize/2, this->blockSize/2, whitePen, redBrush);

}

bool RedKey::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor)
{
    gameCursor->unlockColor('r');
    return true;
}

void RedBlock::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize, this->blockSize, blackPen, redBrush);

}

bool RedBlock::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor)
{
    return gameCursor->colorUnlocked('r');
}

void YellowKey::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    QBrush yellowBrush(Qt::yellow);
    QPen whitePen(Qt::white);
    whitePen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize, this->blockSize, blackPen, whiteBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize/2, this->blockSize/2, whitePen, yellowBrush);
    rectangle = mazeBoard->addRect(xCoord+this->blockSize/2, yCoord, this->blockSize/2, this->blockSize/2, whitePen, yellowBrush);
    rectangle = mazeBoard->addRect(xCoord+this->blockSize/2, yCoord+this->blockSize/2, this->blockSize/2, this->blockSize/2, whitePen, yellowBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord+this->blockSize/2, this->blockSize/2, this->blockSize/2, whitePen, yellowBrush);

}

bool YellowKey::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor)
{
    gameCursor->unlockColor('y');
    return true;
}

void YellowBlock::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush yellowBrush(Qt::yellow);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize, this->blockSize, blackPen, yellowBrush);

}

bool YellowBlock::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor)
{
    return gameCursor->colorUnlocked('y');
}

void GreenKey::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    QBrush greenBrush(Qt::yellow);
    QPen whitePen(Qt::white);
    whitePen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize, this->blockSize, blackPen, whiteBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize/2, this->blockSize/2, whitePen, greenBrush);
    rectangle = mazeBoard->addRect(xCoord+this->blockSize/2, yCoord, this->blockSize/2, this->blockSize/2, whitePen, greenBrush);
    rectangle = mazeBoard->addRect(xCoord+this->blockSize/2, yCoord+this->blockSize/2, this->blockSize/2, this->blockSize/2, whitePen, greenBrush);
    rectangle = mazeBoard->addRect(xCoord, yCoord+this->blockSize/2, this->blockSize/2, this->blockSize/2, whitePen, greenBrush);

}

bool GreenKey::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor)
{
    gameCursor->unlockColor('g');
    return true;
}

void GreenBlock::displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)
{
    QGraphicsRectItem * rectangle;
    QBrush greenBrush(Qt::green);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    rectangle = mazeBoard->addRect(xCoord, yCoord, this->blockSize, this->blockSize, blackPen, greenBrush);

}

bool GreenBlock::moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor)
{
    return gameCursor->colorUnlocked('g');
}
