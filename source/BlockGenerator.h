#ifndef BLOCKGENERATOR_H
#define BLOCKGENERATOR_H

#include "Tetromino.h"

class BlockGenerator
{
public:
    static const int BLOCK_I = 0;
    static const int BLOCK_J = 1;
    static const int BLOCK_L = 2;
    static const int BLOCK_O = 3;
    static const int BLOCK_S = 4;
    static const int BLOCK_T = 5;
    static const int BLOCK_Z = 6;
    static const int NUM_BLOCKS = 7;

    BlockGenerator();
    Tetromino *next();

private:
    int random(int max);
};

#endif // BLOCKGENERATOR_H
