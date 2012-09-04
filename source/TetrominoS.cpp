#include "TetrominoS.h"
#include <stdexcept>

using std::runtime_error;

TetrominoS::TetrominoS()
{
    // default spawning location
    setSquare(1, 4, 0);
    setSquare(2, 5, 0);
    setSquare(3, 3, 1);
    setSquare(4, 4, 1);
    orientation = Tetromino::ORIENTATION_UP;
    setColor(new QColor(Qt::green));
}

TetrominoS *TetrominoS::clone() const {
    return new TetrominoS(*this);
}

void TetrominoS::rotateCounterClockwise() {
    int o = getOrientation();
    switch(o) {
        case Tetromino::ORIENTATION_UP:
            moveSquare(1, -1, 1);
            moveSquare(2, -2, 0);
            moveSquare(3, 1, 1);
            moveSquare(4, 0, 0);
            orientation = Tetromino::ORIENTATION_LEFT;
            break;
        case Tetromino::ORIENTATION_RIGHT:
            moveSquare(1, -1, -1);
            moveSquare(2, 0, -2);
            moveSquare(3, -1, 1);
            moveSquare(4, 0, 0);
            orientation = Tetromino::ORIENTATION_UP;
            break;
        case Tetromino::ORIENTATION_DOWN:
            moveSquare(1, 1, -1);
            moveSquare(2, 2, 0);
            moveSquare(3, -1, -1);
            moveSquare(4, 0, 0);
            orientation = Tetromino::ORIENTATION_RIGHT;
            break;
        case Tetromino::ORIENTATION_LEFT:
            moveSquare(1, 1, 1);
            moveSquare(2, 0, 2);
            moveSquare(3, 1, -1);
            moveSquare(4, 0, 0);
            orientation = Tetromino::ORIENTATION_DOWN;
            break;
        default:
            throw runtime_error("TetrominoS.cpp -> TetrominoS::rotateLeft : Invalid orientation state.");
    }
}

void TetrominoS::rotateClockwise() {
    int o = getOrientation();
    switch(o) {
        case Tetromino::ORIENTATION_UP:
            moveSquare(1, 1, 1);
            moveSquare(2, 0, 2);
            moveSquare(3, 1, -1);
            moveSquare(4, 0, 0);
            orientation = Tetromino::ORIENTATION_RIGHT;
            break;
        case Tetromino::ORIENTATION_RIGHT:
            moveSquare(1, -1, 1);
            moveSquare(2, -2, 0);
            moveSquare(3, 1, 1);
            moveSquare(4, 0, 0);
            orientation = Tetromino::ORIENTATION_DOWN;
            break;
        case Tetromino::ORIENTATION_DOWN:
            moveSquare(1, -1, -1);
            moveSquare(2, 0, -2);
            moveSquare(3, -1, 1);
            moveSquare(4, 0, 0);
            orientation = Tetromino::ORIENTATION_LEFT;
            break;
        case Tetromino::ORIENTATION_LEFT:
            moveSquare(1, 1, -1);
            moveSquare(2, 2, 0);
            moveSquare(3, -1, -1);
            moveSquare(4, 0, 0);
            orientation = Tetromino::ORIENTATION_UP;
            break;
        default:
            throw runtime_error("TetrominoS.cpp -> TetrominoS::rotateRight : Invalid orientation state.");
    }
}
