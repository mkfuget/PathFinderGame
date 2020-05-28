#include "animator.h"

Animator::CursorAnimator()
{

}

void Animator::buildBoard(QGraphicsScene *mazeBoard, Board mazeData)
{
    for(int i=0; i<mazeData.getNumBlocksVertical(); i++)
    {
        for(int j=0; j<mazeData.getNumBlocksVertical(); j++)
        {
            mazeData.getSpace(i, j)->displaySpace(i, j, mazeBoard);
        }
    }
}
