#ifndef CURSOR_H
#define CURSOR_H
#pragma once
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <unordered_map>
#include "space.h"
class Space;
class Cursor: public QGraphicsRectItem
{
private:
    int xIndex;
    int yIndex;
    int blockSize;
    std::vector<std::vector<char>> mazeGrid;
    std::unordered_map<char, Space*> factory;
    bool blueUnlocked=false;
    bool redUnlocked=false;
    bool greenUnlocked=false;
    bool yellowUnlocked=false;

public:
    Cursor();
    Cursor(int startXIndex, int startYIndex, int blockSize, std::vector<std::vector<char>> mazeGrid, std::unordered_map<char, Space*> factory);
    bool moveTo(int xdestination,int yDestination);
    void keyPressEvent(QKeyEvent * event);
    void updateLocation(int deltaX, int deltaY);
    void unlockColor(char color);
    bool colorUnlocked(char color);
    int indexToCoord(int index);
};

#endif // CURSOR_H
