#ifndef TETROMINOT_H
#define TETROMINOT_H

#include "Tetromino.h"

class TetrominoT : public Tetromino
{
public:
    TetrominoT();
    TetrominoT *clone() const;

    void rotateCounterClockwise();
    void rotateClockwise();
};

#endif // TETROMINOT_H
