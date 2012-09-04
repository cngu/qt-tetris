#include "TetrominoO.h"
#include <stdexcept>

using std::runtime_error;

TetrominoO::TetrominoO()
{
    // default spawning location
    setSquare(1, 4, 0);
    setSquare(2, 5, 0);
    setSquare(3, 4, 1);
    setSquare(4, 5, 1);
    orientation = Tetromino::ORIENTATION_UP;
    setColor(new QColor(Qt::yellow));
}

TetrominoO *TetrominoO::clone() const {
    return new TetrominoO(*this);
}

void TetrominoO::rotateCounterClockwise() {}

void TetrominoO::rotateClockwise() {}
