#ifndef BOARD_H
#define BOARD_H
#pragma once
#include <QDialog>
#include <QtCore>
#include <QtWidgets>
#include <QTimer>
#include <string>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <QMediaPlayer>

class Board : public QGraphicsObject
{
    Q_OBJECT

public:
    static const int blockSize = 28;
    struct Cursor
    {
        int xIndex;
        int yIndex;
        int bitLock=0; // 1 unlocks blue, 2 for red, 4 for yellow, 8 for green
        Cursor(int startXIndex, int startYIndex);
        Cursor(Cursor *copy);
        QColor bitLockToColor();
        void unlockColor(char color);
        bool colorUnlocked(char color);
    };
    struct AnimatorCursor
    {
        Cursor *animatedCursor;
        qreal angle;
        qreal speed;
        AnimatorCursor(Cursor *animatedCursor);

    };
    struct LightUpSquare : public QGraphicsObject
    {
        int xIndex;
        int yIndex;
        QBrush lightUpBrush;
        LightUpSquare(int xIndex, int yIndex, QColor color);
        QRectF boundingRect() const;
        void paint(QPainter *painter,const QStyleOptionGraphicsItem *style, QWidget *widget);
    };

    //Each space has a specific type that inherits from the virtual base space struct, all space methods are called on a pointer to the base struct
    //This allows new spaces to be implemented just by adding the new struct and adding the that derived struct to the
    struct Space

    {
    protected:
        std::string id;
    public:
        virtual void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard)=0;
        virtual bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)=0;
        virtual bool moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData)=0;

        virtual void playSound(Board *mazeData)=0;
        void playSoundEmptySpace(Board *mazeData);
        void playSoundFullSpace(Board *mazeData);
        Space();
        virtual ~Space();
    };
    struct EmptySpace :public Space
    {
        void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard) override;
        bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        bool moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        void playSound(Board *mazeData) override;
    };
    struct FullSpace :public Space
    {
        void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard) override;
        bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        bool moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        void playSound(Board *mazeData) override;
    };
    struct StartSpace :public Space
    {
        void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard) override;
        bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        bool moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        void playSound(Board *mazeData) override;

    };
    struct FinishSpace :public Space
    {
        void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard) override;
        bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        bool moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        void playSound(Board *mazeData) override;
    };
    struct AcceleratorSpace :public Space
    {
        void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard) override;
        bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        bool moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        void playSound(Board *mazeData) override;
    };
    struct BlueKey :public Space
    {
        void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard) override;
        bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        bool moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        void playSound(Board *mazeData) override;
    };
    struct BlueBlock :public Space
    {
        void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard) override;
        bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        bool moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        void playSound(Board *mazeData) override;
    };
    struct RedKey :public Space
    {
        void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard) override;
        bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        bool moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        void playSound(Board *mazeData) override;
    };
    struct RedBlock :public Space
    {
        void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard) override;
        bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        bool moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        void playSound(Board *mazeData) override;
    };
    struct YellowKey :public Space
    {
        void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard) override;
        bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        bool moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCurso, Board *mazeData) override;
        void playSound(Board *mazeData) override;
    };
    struct YellowBlock :public Space
    {
        void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard) override;
        bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        bool moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        void playSound(Board *mazeData) override;
    };
    struct GreenKey :public Space
    {
        void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard) override;
        bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        bool moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        void playSound(Board *mazeData) override;
    };
    struct GreenBlock :public Space
    {
        void displaySpace(int xCoord, int yCoord, QGraphicsScene *mazeBoard) override;
        bool moveToSpace(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        bool moveMentAllowed(int xCurrent, int yCurrent, int xDestination, int yDestination, Board::Cursor *gameCursor, Board *mazeData) override;
        void playSound(Board *mazeData) override;
    };
    struct PathFinderData
    {
        int currentXIndex;
        int currentYIndex;
        int lastXIndex;
        int lastYIndex;
        int currentBitLock;
        int lastBitLock;
        bool travelled=false;
        PathFinderData();
        PathFinderData(int currentXIndex, int CurrentYIndex, int currentBitLock, int lastXIndex, int lastYIndex,  int lastBitLock, bool travelled);
    };
    Board(QGraphicsScene* mazeScene);
    ~Board() override;
    Board(std::string fileName, int numBlocksVertical, int numBlocksHorizantal, QGraphicsScene* mazeScene);
    void displayBoard();
    bool moveTo(int deltaX,int deltaY, Cursor *gameCursor);
    void keyPressEvent(QKeyEvent * event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;

    void dijkstra();
    void dijkstraTimerFunction(std::queue<Cursor*>& pathsQueue, std::vector<std::vector<std::vector<PathFinderData>>>& pathsTravelled, Board* mazeData);
    void dijkstraTimerInternalFunction(std::queue<Board::Cursor *>& pathsQueue, std::vector<std::vector<std::vector<Board::PathFinderData> > >& pathsTravelled);
    void findFinalPath(std::vector<std::vector<std::vector<PathFinderData>>>& pathsTravelled, int xIndex, int yIndex, int currentBitLock, int startXIndex, int startYIndex, int startBitLock, int flashInterval);


private:
    static int indexToCoord(int index);
    static int coordToIndex(double coord);
    int numBlocksVertical;
    int numBlocksHorizantal;
    bool solutionFound;
    int solutionXIndex;
    int solutionYIndex;
    int solutionBitLock;
    QRectF boundingRect() const;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *style, QWidget *widget);
    void lightSquare(int xIndex, int yIndex, QColor color, Board *mazeData);
    std::vector<std::vector<char>> mazeGrid;
    std::unordered_map<char, Space*> factory;
    AnimatorCursor *visibleCursor;
    QGraphicsScene *mazeScene;
    QMediaPlayer * soundEffect;


};

#endif // BOARD_H
