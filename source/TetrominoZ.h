#ifndef TETROMINOZ_H
#define TETROMINOZ_H

#include "Tetromino.h"

class TetrominoZ : public Tetromino
{
public:
    TetrominoZ();
    TetrominoZ *clone() const;

    void rotateCounterClockwise();
    void rotateClockwise();
};

#endif // TETROMINOZ_H
