#include "TetrominoI.h"
#include <stdexcept>

using std::runtime_error;

TetrominoI::TetrominoI()
{
    // default spawning location
    setSquare(1, 3, 0);
    setSquare(2, 4, 0);
    setSquare(3, 5, 0);
    setSquare(4, 6, 0);
    orientation = Tetromino::ORIENTATION_UP;
    setColor(new QColor(Qt::cyan));
}

TetrominoI *TetrominoI::clone() const {
    return new TetrominoI(*this);
}

void TetrominoI::rotateCounterClockwise() {
    int o = getOrientation();
    switch(o) {
        case Tetromino::ORIENTATION_UP:
            moveSquare(1, 1, 2);
            moveSquare(2, 0, 1);
            moveSquare(3, -1, 0);
            moveSquare(4, -2, -1);
            orientation = Tetromino::ORIENTATION_LEFT;
            break;
        case Tetromino::ORIENTATION_RIGHT:
            moveSquare(1, -2, 1);
            moveSquare(2, -1, 0);
            moveSquare(3, 0, -1);
            moveSquare(4, 1, -2);
            orientation = Tetromino::ORIENTATION_UP;
            break;
        case Tetromino::ORIENTATION_DOWN:
            moveSquare(1, -1, -2);
            moveSquare(2, 0, -1);
            moveSquare(3, 1, 0);
            moveSquare(4, 2, 1);
            orientation = Tetromino::ORIENTATION_RIGHT;
            break;
        case Tetromino::ORIENTATION_LEFT:
            moveSquare(1, 2, -1);
            moveSquare(2, 1, 0);
            moveSquare(3, 0, 1);
            moveSquare(4, -1, 2);
            orientation = Tetromino::ORIENTATION_DOWN;
            break;
        default:
            throw runtime_error("TetrominoI.cpp -> TetrominoI::rotateLeft : Invalid orientation state.");
    }
}

void TetrominoI::rotateClockwise() {
    int o = getOrientation();
    switch(o) {
        case Tetromino::ORIENTATION_UP:
            moveSquare(1, 2, -1);
            moveSquare(2, 1, 0);
            moveSquare(3, 0, 1);
            moveSquare(4, -1, 2);
            orientation = Tetromino::ORIENTATION_RIGHT;
            break;
        case Tetromino::ORIENTATION_RIGHT:
            moveSquare(1, 1, 2);
            moveSquare(2, 0, 1);
            moveSquare(3, -1, 0);
            moveSquare(4, -2, -1);
            orientation = Tetromino::ORIENTATION_DOWN;
            break;
        case Tetromino::ORIENTATION_DOWN:
            moveSquare(1, -2, 1);
            moveSquare(2, -1, 0);
            moveSquare(3, 0, -1);
            moveSquare(4, 1, -2);
            orientation = Tetromino::ORIENTATION_LEFT;
            break;
        case Tetromino::ORIENTATION_LEFT:
            moveSquare(1, -1, -2);
            moveSquare(2, 0, -1);
            moveSquare(3, 1, 0);
            moveSquare(4, 2, 1);
            orientation = Tetromino::ORIENTATION_UP;
            break;
        default:
            throw runtime_error("TetrominoI.cpp -> TetrominoI::rotateRight : Invalid orientation state.");
    }
}
