#ifndef TETROMINO_H
#define TETROMINO_H

#include <QPalette>
#include <QColor>
#include <vector>
#include <QDebug>

class Square {
public:
    int getX() const;
    int getY() const;
    void setX(int newX);
    void setY(int newY);
private:
    int x, y;
};

class Tetromino
{
private:
    Square s1, s2, s3, s4;
    QColor *color;

protected:
    int orientation;

public:
    // Make destructor pure virtual because we have no other candidates
    //virtual ~Tetromino() = 0;
    ~Tetromino();
    virtual Tetromino *clone() const = 0;

    static const int ORIENTATION_UP = 0;
    static const int ORIENTATION_RIGHT = 90;
    static const int ORIENTATION_DOWN = 180;
    static const int ORIENTATION_LEFT = 270;

    const Square& getSquare(int s) const;
    std::vector<Square>* getAllSquares() const;
    int getOrientation();
    const QColor* getColor() const;

    void move(int x, int y);
    virtual void rotateCounterClockwise() = 0;
    virtual void rotateClockwise() = 0;

    bool outOfBounds();

protected:
    void setSquare(int s, int x, int y);
    void moveSquare(int s, int x, int y);
    void setOrientation(int o);
    void setColor(QColor *c);
};

// Subclass dtors eventually call this one so we provide an empty declaration
//inline Tetromino::~Tetromino() {}

#endif // TETROMINO_H
