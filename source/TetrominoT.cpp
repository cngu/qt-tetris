#include "TetrominoT.h"
#include <QColor>
#include <stdexcept>

using std::runtime_error;

TetrominoT::TetrominoT()
{
    // default spawning location
    setSquare(1, 4, 0);
    setSquare(2, 3, 1);
    setSquare(3, 4, 1);
    setSquare(4, 5, 1);
    orientation = Tetromino::ORIENTATION_UP;
    setColor(new QColor(160,32,240));    // purple
}

TetrominoT *TetrominoT::clone() const {
    return new TetrominoT(*this);
}

void TetrominoT::rotateCounterClockwise() {
    int o = getOrientation();
    switch(o) {
        case Tetromino::ORIENTATION_UP:
            moveSquare(1, -1, 1);
            moveSquare(2, 1, 1);
            moveSquare(3, 0, 0);
            moveSquare(4, -1, -1);
            orientation = Tetromino::ORIENTATION_LEFT;
            break;
        case Tetromino::ORIENTATION_RIGHT:
            moveSquare(1, -1, -1);
            moveSquare(2, -1, 1);
            moveSquare(3, 0, 0);
            moveSquare(4, 1, -1);
            orientation = Tetromino::ORIENTATION_UP;
            break;
        case Tetromino::ORIENTATION_DOWN:
            moveSquare(1, 1, -1);
            moveSquare(2, -1, -1);
            moveSquare(3, 0, 0);
            moveSquare(4, 1, 1);
            orientation = Tetromino::ORIENTATION_RIGHT;
            break;
        case Tetromino::ORIENTATION_LEFT:
            moveSquare(1, 1, 1);
            moveSquare(2, 1, -1);
            moveSquare(3, 0, 0);
            moveSquare(4, -1, 1);
            orientation = Tetromino::ORIENTATION_DOWN;
            break;
        default:
            throw runtime_error("TetrominoT.cpp -> TetrominoT::rotateLeft : Invalid orientation state.");
    }
}

void TetrominoT::rotateClockwise() {
    int o = getOrientation();
    switch(o) {
        case Tetromino::ORIENTATION_UP:
            moveSquare(1, 1, 1);
            moveSquare(2, 1, -1);
            moveSquare(3, 0, 0);
            moveSquare(4, -1, 1);
            orientation = Tetromino::ORIENTATION_RIGHT;
            break;
        case Tetromino::ORIENTATION_RIGHT:
            moveSquare(1, -1, 1);
            moveSquare(2, 1, 1);
            moveSquare(3, 0, 0);
            moveSquare(4, -1, -1);
            orientation = Tetromino::ORIENTATION_DOWN;
            break;
        case Tetromino::ORIENTATION_DOWN:
            moveSquare(1, -1, -1);
            moveSquare(2, -1, 1);
            moveSquare(3, 0, 0);
            moveSquare(4, 1, -1);
            orientation = Tetromino::ORIENTATION_LEFT;
            break;
        case Tetromino::ORIENTATION_LEFT:
            moveSquare(1, 1, -1);
            moveSquare(2, -1, -1);
            moveSquare(3, 0, 0);
            moveSquare(4, 1, 1);
            orientation = Tetromino::ORIENTATION_UP;
            break;
        default:
            throw runtime_error("TetrominoT.cpp -> TetrominoT::rotateRight : Invalid orientation state.");
    }
}
