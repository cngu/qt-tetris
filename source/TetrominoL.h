#ifndef TETROMINOL_H
#define TETROMINOL_H

#include "Tetromino.h"

class TetrominoL : public Tetromino
{
public:
    TetrominoL();
    TetrominoL *clone() const;

    void rotateCounterClockwise();
    void rotateClockwise();
};

#endif // TETROMINOL_H
