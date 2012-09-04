#include "Tetromino.h"
#include <stdexcept>

using std::domain_error;
using std::vector;

int Square::getX() const {
    return x;
}

int Square::getY() const {
    return y;
}

void Square::setX(int newX) {
    x = newX;
}

void Square::setY(int newY) {
    y = newY;
}

Tetromino::~Tetromino() {
    delete color;
}

const Square &Tetromino::getSquare(int s) const {
    switch(s) {
    case 1:
        return s1;
    case 2:
        return s2;
    case 3:
        return s3;
    case 4:
        return s4;
    default:
        throw domain_error("Tetromino.cpp -> Tetromino::getSquare : Invalid square number.");
    }
}

void Tetromino::setSquare(int s, int x, int y) {
    switch(s) {
    case 1:
        s1.setX(x);
        s1.setY(y);
        break;
    case 2:
        s2.setX(x);
        s2.setY(y);
        break;
    case 3:
        s3.setX(x);
        s3.setY(y);
        break;
    case 4:
        s4.setX(x);
        s4.setY(y);
        break;
    default:
        throw domain_error("Tetromino.cpp -> Tetromino::setSquare : Invalid square number.");
    }
}

vector<Square>* Tetromino::getAllSquares() const {
    vector<Square> *squares = new vector<Square>();
    for (int i = 1; i <= 4; i++) {
        squares->push_back(getSquare(i));
    }
    return squares;
}


void Tetromino::moveSquare(int s, int x, int y) {
    setSquare(s, getSquare(s).getX() + x, getSquare(s).getY() + y);
}

void Tetromino::move(int x, int y) {
    for (int i = 1; i <= 4; i++) {
        moveSquare(i, x, y);
    }
}

int Tetromino::getOrientation() {
    return orientation;
}

void Tetromino::setOrientation(int o) {
    if ( (o != Tetromino::ORIENTATION_UP) &&
         (o != Tetromino::ORIENTATION_RIGHT) &&
         (o != Tetromino::ORIENTATION_DOWN) &&
         (o != Tetromino::ORIENTATION_LEFT) )
    {
        throw domain_error("Tetromino.cpp -> Tetromino::setOrientation : "
                           "Invalid orientation. See Tetromino.cpp for valid orientations.");
    }

    orientation = o;
}

bool Tetromino::outOfBounds() {
    vector<Square> *squares = getAllSquares();
    vector<Square>::const_iterator i;
    for (i = squares->begin(); i != squares->end(); i++) {
        if (i->getX() < 0 || i->getX() > 9)
            return true;
        if (i->getY() < 0 || i->getY() > 21)
            return true;
    }
    return false;
}

const QColor *Tetromino::getColor() const {
    return color;
}

void Tetromino::setColor(QColor *c) {
    color = c;
}
