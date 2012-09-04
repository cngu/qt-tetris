#ifndef TETROMINOJ_H
#define TETROMINOJ_H

#include "Tetromino.h"

class TetrominoJ : public Tetromino
{
public:
    TetrominoJ();
    TetrominoJ *clone() const;

    void rotateCounterClockwise();
    void rotateClockwise();
};

#endif // TETROMINOJ_H
