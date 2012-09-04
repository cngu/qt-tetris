#include "TetrominoZ.h"
#include <stdexcept>

using std::runtime_error;

TetrominoZ::TetrominoZ()
{
    // default spawning location
    setSquare(1, 3, 0);
    setSquare(2, 4, 0);
    setSquare(3, 4, 1);
    setSquare(4, 5, 1);
    orientation = Tetromino::ORIENTATION_UP;
    setColor(new QColor(Qt::red));
}

TetrominoZ *TetrominoZ::clone() const {
    return new TetrominoZ(*this);
}

void TetrominoZ::rotateCounterClockwise() {
    int o = getOrientation();
    switch(o) {
        case Tetromino::ORIENTATION_UP:
            moveSquare(1, 0, 2);
            moveSquare(2, -1, 1);
            moveSquare(3, 0, 0);
            moveSquare(4, -1, -1);
            orientation = Tetromino::ORIENTATION_LEFT;
            break;
        case Tetromino::ORIENTATION_RIGHT:
            moveSquare(1, -2, 0);
            moveSquare(2, -1, -1);
            moveSquare(3, 0, 0);
            moveSquare(4, 1, -1);
            orientation = Tetromino::ORIENTATION_UP;
            break;
        case Tetromino::ORIENTATION_DOWN:
            moveSquare(1, 0, -2);
            moveSquare(2, 1, -1);
            moveSquare(3, 0, 0);
            moveSquare(4, 1, 1);
            orientation = Tetromino::ORIENTATION_RIGHT;
            break;
        case Tetromino::ORIENTATION_LEFT:
            moveSquare(1, 2, 0);
            moveSquare(2, 1, 1);
            moveSquare(3, 0, 0);
            moveSquare(4, -1, 1);
            orientation = Tetromino::ORIENTATION_DOWN;
            break;
        default:
            throw runtime_error("TetrominoZ.cpp -> TetrominoZ::rotateLeft : Invalid orientation state.");
    }
}

void TetrominoZ::rotateClockwise() {
    int o = getOrientation();
    switch(o) {
        case Tetromino::ORIENTATION_UP:
            moveSquare(1, 2, 0);
            moveSquare(2, 1, 1);
            moveSquare(3, 0, 0);
            moveSquare(4, -1, 1);
            orientation = Tetromino::ORIENTATION_RIGHT;
            break;
        case Tetromino::ORIENTATION_RIGHT:
            moveSquare(1, 0, 2);
            moveSquare(2, -1, 1);
            moveSquare(3, 0, 0);
            moveSquare(4, -1, -1);
            orientation = Tetromino::ORIENTATION_DOWN;
            break;
        case Tetromino::ORIENTATION_DOWN:
            moveSquare(1, -2, 0);
            moveSquare(2, -1, -1);
            moveSquare(3, 0, 0);
            moveSquare(4, 1, -1);
            orientation = Tetromino::ORIENTATION_LEFT;
            break;
        case Tetromino::ORIENTATION_LEFT:
            moveSquare(1, 0, -2);
            moveSquare(2, 1, -1);
            moveSquare(3, 0, 0);
            moveSquare(4, 1, 1);
            orientation = Tetromino::ORIENTATION_UP;
            break;
        default:
            throw runtime_error("TetrominoZ.cpp -> TetrominoZ::rotateRight : Invalid orientation state.");
    }
}
