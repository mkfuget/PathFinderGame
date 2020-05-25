#ifndef SPACE_H
#define SPACE_H


#pragma once
#include <QDialog>
#include <QtCore>
#include <QtWidgets>
#include <string>
#include "Cursor.h"
class Cursor;
class Space
{
protected:
    std::string id;
    int blockSize;
public:
    virtual void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)=0;
    virtual bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor)=0;
    void setData(std::string id, int bloackSize);
    Space();
    virtual ~Space();
};
class EmptySpace :public Space
{
    void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard);
    bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor);

};
class FullSpace :public Space
{
    void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard);
    bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor);
};
class StartSpace :public Space
{
    void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard);
    bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor);

};
class FinishSpace :public Space
{
    void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard);
    bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor);
};
class AcceleratorSpace :public Space
{
    void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard);
    bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor);
};
class BlueKey :public Space
{
    void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard);
    bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor);
};
class BlueBlock :public Space
{
    void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard);
    bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor);
};
class RedKey :public Space
{
    void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard);
    bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor);
};
class RedBlock :public Space
{
    void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard);
    bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor);
};
class YellowKey :public Space
{
    void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard);
    bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor);
};
class YellowBlock :public Space
{
    void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard);
    bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor);
};
class GreenKey :public Space
{
    void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard);
    bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor);
};
class GreenBlock :public Space
{
    void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard);
    bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Cursor *gameCursor);
};


#endif // SPACE_H
