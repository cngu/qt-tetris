#include "TetrominoL.h"
#include <QColor>
#include <stdexcept>

using std::runtime_error;

TetrominoL::TetrominoL()
{
    // default spawning location
    setSquare(1, 3, 0);
    setSquare(2, 3, 1);
    setSquare(3, 4, 1);
    setSquare(4, 5, 1);
    orientation = Tetromino::ORIENTATION_UP;
    setColor(new QColor(255, 127, 0));  // orange
}

TetrominoL *TetrominoL::clone() const {
    return new TetrominoL(*this);
}

void TetrominoL::rotateCounterClockwise() {
    int o = getOrientation();
    switch(o) {
        case Tetromino::ORIENTATION_UP:
            moveSquare(1, 0, 2);
            moveSquare(2, 1, 1);
            moveSquare(3, 0, 0);
            moveSquare(4, -1, -1);
            orientation = Tetromino::ORIENTATION_LEFT;
            break;
        case Tetromino::ORIENTATION_RIGHT:
            moveSquare(1, -2, 0);
            moveSquare(2, -1, 1);
            moveSquare(3, 0, 0);
            moveSquare(4, 1, -1);
            orientation = Tetromino::ORIENTATION_UP;
            break;
        case Tetromino::ORIENTATION_DOWN:
            moveSquare(1, 0, -2);
            moveSquare(2, -1, -1);
            moveSquare(3, 0, 0);
            moveSquare(4, 1, 1);
            orientation = Tetromino::ORIENTATION_RIGHT;
            break;
        case Tetromino::ORIENTATION_LEFT:
            moveSquare(1, 2, 0);
            moveSquare(2, 1, -1);
            moveSquare(3, 0, 0);
            moveSquare(4, -1, 1);
            orientation = Tetromino::ORIENTATION_DOWN;
            break;
        default:
            throw runtime_error("TetrominoL.cpp -> TetrominoL::rotateLeft : Invalid orientation state.");
    }
}

void TetrominoL::rotateClockwise() {
    int o = getOrientation();
    switch(o) {
        case Tetromino::ORIENTATION_UP:
            moveSquare(1, 2, 0);
            moveSquare(2, 1, -1);
            moveSquare(3, 0, 0);
            moveSquare(4, -1, 1);
            orientation = Tetromino::ORIENTATION_RIGHT;
            break;
        case Tetromino::ORIENTATION_RIGHT:
            moveSquare(1, 0, 2);
            moveSquare(2, 1, 1);
            moveSquare(3, 0, 0);
            moveSquare(4, -1, -1);
            orientation = Tetromino::ORIENTATION_DOWN;
            break;
        case Tetromino::ORIENTATION_DOWN:
            moveSquare(1, -2, 0);
            moveSquare(2, -1, 1);
            moveSquare(3, 0, 0);
            moveSquare(4, 1, -1);
            orientation = Tetromino::ORIENTATION_LEFT;
            break;
        case Tetromino::ORIENTATION_LEFT:
            moveSquare(1, 0, -2);
            moveSquare(2, -1, -1);
            moveSquare(3, 0, 0);
            moveSquare(4, 1, 1);
            orientation = Tetromino::ORIENTATION_UP;
            break;
        default:
            throw runtime_error("TetrominoL.cpp -> TetrominoL::rotateRight : Invalid orientation state.");
    }
}
