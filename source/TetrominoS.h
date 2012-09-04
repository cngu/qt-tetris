#ifndef TETROMINOS_H
#define TETROMINOS_H

#include "Tetromino.h"

class TetrominoS : public Tetromino
{
public:
    TetrominoS();
    TetrominoS *clone() const;

    void rotateCounterClockwise();
    void rotateClockwise();
};

#endif // TETROMINOS_H
