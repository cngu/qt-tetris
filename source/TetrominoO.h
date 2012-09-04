#ifndef TETROMINOO_H
#define TETROMINOO_H

#include "Tetromino.h"

class TetrominoO : public Tetromino
{
public:
    TetrominoO();
    TetrominoO *clone() const;

    void rotateCounterClockwise();
    void rotateClockwise();
};

#endif // TETROMINOO_H
