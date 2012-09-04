#ifndef TETROMINOI_H
#define TETROMINOI_H

#include "Tetromino.h"

class TetrominoI : public Tetromino
{
public:
    TetrominoI();
    TetrominoI *clone() const;

    void rotateCounterClockwise();
    void rotateClockwise();
};

#endif // TETROMINOI_H
