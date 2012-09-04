#include "BlockGenerator.h"
#include "time.h"
#include "TetrominoI.h"
#include "TetrominoJ.h"
#include "TetrominoL.h"
#include "TetrominoO.h"
#include "TetrominoS.h"
#include "TetrominoT.h"
#include "TetrominoZ.h"
#include <stdexcept>
#include <cstdlib>

using std::logic_error;

BlockGenerator::BlockGenerator()
{
    srand(time(0));
}

Tetromino *BlockGenerator::next() {
    Tetromino *t;
    int block = random(BlockGenerator::NUM_BLOCKS);
    switch (block) {
    case BlockGenerator::BLOCK_I:
        t = new TetrominoI();
        break;
    case BlockGenerator::BLOCK_J:
        t = new TetrominoJ();
        break;
    case BlockGenerator::BLOCK_L:
        t = new TetrominoL();
        break;
    case BlockGenerator::BLOCK_O:
        t = new TetrominoO();
        break;
    case BlockGenerator::BLOCK_S:
        t = new TetrominoS();
        break;
    case BlockGenerator::BLOCK_T:
        t = new TetrominoT();
        break;
    case BlockGenerator::BLOCK_Z:
        t = new TetrominoZ();
        break;
    default:
        throw logic_error("BlockGenerator.cpp -> BlockGenerator::next : Random number out of range.");
    }
    return t;
}

int BlockGenerator::random(int max) {
    return rand() % max;
}
