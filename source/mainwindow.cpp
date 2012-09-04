#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QPalette>
#include <QFrame>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>
#include <vector>
#include <stdexcept>

using std::vector;
using std::domain_error;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), viewQueue(new VCQueue<Message*>)
{
    ui->setupUi(this);

    // Set main window properties
    setFixedSize(400, 454);

    blankCellColor = QColor(26, 26, 26);

    // Initialize the interface and game board on the MainWindow
    initWindow();

    QObject::connect(ui->startButton, SIGNAL(clicked()), this, SLOT(reset()));
}

MainWindow::MainWindow(VCQueue<Message *> *q, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), viewQueue(q)
{
    ui->setupUi(this);

    // Set main window properties
    setFixedSize(400, 454);

    blankCellColor = QColor(26, 26, 26);

    // Initialize the interface and game board on the MainWindow
    initWindow();

    QObject::connect(ui->startButton, SIGNAL(clicked()), this, SLOT(reset()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Create and initialize widgets to form the interface.
 */
void MainWindow::initWindow() {
    setFocus();
    // Color background of game board Qt::black
    QPalette backgroundPalette = ui->background->palette();
    backgroundPalette.setColor(ui->background->backgroundRole(), Qt::black);
    ui->background->setPalette(backgroundPalette);

    // Assemble game board as grid of frames that can be colored
    QFrame *f;
    QPalette p;
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 10; j++) {
            f = new QFrame();
            p = f->palette();
            if (i == 0 || i == 1)
                p.setColor(f->backgroundRole(), blankCellColor);//QColor(Qt::white));
            else
                p.setColor(f->backgroundRole(), blankCellColor);
            f->setPalette(p);
            f->setAutoFillBackground(true);
            ui->board->addWidget(f, i, j);
        }
    }

    // Initialize "next-block" grid
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            f = new QFrame();
            p = f->palette();
            p.setColor(f->backgroundRole(), blankCellColor);
            f->setPalette(p);
            f->setAutoFillBackground(true);
            ui->nextBlockGrid->addWidget(f, i, j);
        }
    }

    ui->gameoverLabel->hide();

}

void MainWindow::draw(Tetromino *t) {
    int x, y;
    QWidget *cell;
    QPalette p;

    vector<Square> *squares = t->getAllSquares();
    vector<Square>::const_iterator i;
    for (i = squares->begin(); i != squares->end(); i++) {
        x = i->getX();
        y = i->getY();

        cell = ui->board->itemAtPosition(y,x)->widget();
        p = cell->palette();
        p.setColor(cell->backgroundRole(), *(t->getColor()));
        cell->setPalette(p);
        cell->setAutoFillBackground(true);
    }

    delete squares;
}

void MainWindow::erase(Tetromino *t) {
    int x, y;
    QWidget *cell;
    QPalette p;

    vector<Square> *squares = t->getAllSquares();
    vector<Square>::const_iterator i;
    for (i = squares->begin(); i != squares->end(); i++) {
        x = i->getX();
        y = i->getY();

        cell = ui->board->itemAtPosition(y,x)->widget();
        p = cell->palette();
        p.setColor(cell->backgroundRole(), blankCellColor);
        cell->setPalette(p);
        cell->setAutoFillBackground(true);
    }
    delete squares;
}

void MainWindow::swapLines(int l1, int l2) {
    QWidget *cell1, *cell2;
    QColor cellColor1, cellColor2;
    QPalette p1, p2;

    for (int i = 0; i < 10; i++) {
        cell1 = ui->board->itemAtPosition(l1, i)->widget();
        cell2 = ui->board->itemAtPosition(l2, i)->widget();
        cellColor1 = cell1->palette().background().color();
        cellColor2 = cell2->palette().background().color();
        p1 = cell1->palette();
        p2 = cell2->palette();

        p1.setColor(cell1->backgroundRole(), cellColor2);
        p2.setColor(cell2->backgroundRole(), cellColor1);

        cell1->setPalette(p1);
        cell2->setPalette(p2);
        cell1->setAutoFillBackground(true);
        cell2->setAutoFillBackground(true);
    }
}

void MainWindow::eraseLine(int line) {
    QWidget *cell;
    QPalette p;

    for (int i = 0; i < 10; i++) {
        cell = ui->board->itemAtPosition(line,i)->widget();
        p = cell->palette();
        p.setColor(cell->backgroundRole(), blankCellColor);
        cell->setPalette(p);
        cell->setAutoFillBackground(true);
    }
}

void MainWindow::collapse(int start) {
    while (start > 0) {
        swapLines(start, start-1);
        start--;
    }
}

int MainWindow::clearLines() {
    QWidget *cell;
    QColor cellColor;
    int linesCleared = 0;
    bool cleared;

    for (int row = 21; row >= 0; row--) {
        cleared = true;
        for (int col = 0; (col < 10) && cleared; col++) {
            cell = ui->board->itemAtPosition(row,col)->widget();
            cellColor = cell->palette().background().color();
            if (cellColor == blankCellColor)
                cleared = false;
        }
        if (cleared) {
            eraseLine(row);
            collapse(row);
            row++;
            linesCleared++;
        }
    }

    return linesCleared;
}

void MainWindow::clearBoard() {
    for (int i = 0; i < 22; i++) {
        eraseLine(i);
    }
}

// used to check collisions when no movement occurs i.e. spawning a new tetromino
bool MainWindow::checkCollision(Tetromino *t) const {
    int x, y;
    bool collision = false;
    QWidget *cell;
    QColor cellColor;

    if (t->outOfBounds()) {
        collision = true;
    }

    vector<Square> *squares = t->getAllSquares();
    vector<Square>::const_iterator i;
    for (i = squares->begin(); i != squares->end() && !collision; i++) {
        x = i->getX();
        y = i->getY();
        cell = ui->board->itemAtPosition(y,x)->widget();
        cellColor = cell->palette().background().color();

        //qDebug() << "Square: " << i-squares->begin() << cellColor;
        if (cellColor != blankCellColor) {
            collision = true;
        //    qDebug() << "Collision: " << collision;
        }
    }
    delete squares;
    return collision;
}

// direction should only be Message::KEY_DOWN, Message::KEY_LEFT, or MESSAGE::KEY_RIGHT
bool MainWindow::checkCollision(Tetromino *t, Message *direction) const {
    int x, y, copyX, copyY;
    bool collision = false;
    QWidget *copyCell;
    QColor copyCellColor;

    Tetromino *copy = t->clone();
    switch (direction->message) {
    case Message::KEY_LEFT:
        copy->move(-1, 0);
        break;
    case Message::KEY_RIGHT:
        copy->move(1, 0);
        break;
    case Message::KEY_DOWN:
        copy->move(0, 1);
        break;
    default:
        throw domain_error("MainWindow::checkCollision : Invalid Collision message");
    }

    if (copy->outOfBounds()) {
        collision = true;
    }

    vector<Square> *squares, *copySquares = copy->getAllSquares();
    vector<Square>::const_iterator i, j;
    for (i = copySquares->begin(); i != copySquares->end() && !collision; i++) {
        copyX = i->getX();
        copyY = i->getY();
        copyCell = ui->board->itemAtPosition(copyY,copyX)->widget();
        copyCellColor = copyCell->palette().background().color();

        bool overlap = false;
        squares = t->getAllSquares();
        for (j = squares->begin(); j != squares->end() && !overlap; j++) {
            x = j->getX();
            y = j->getY();
            if (copyX == x && copyY == y) {
                overlap = true;
            }
        }
        delete squares;

        //qDebug() << "Square: " << i-copySquares->begin() << copyCellColor;
        if ((copyCellColor != blankCellColor) && !overlap) {
            collision = true;
        //    qDebug() << "Collision: " << collision << " Overlap: " << overlap;
        }
    }
    delete copySquares;
    return collision;
}

void MainWindow::keyPressEvent(QKeyEvent* e) {
    Message *m = NULL;
    if (e->key() == Qt::Key_Right)
        m = new Message(Message::KEY_RIGHT);
    else if (e->key() == Qt::Key_Left)
        m = new Message(Message::KEY_LEFT);
    else if (e->key() == Qt::Key_Down)
        m = new Message(Message::KEY_DOWN);
    else if (e->key() == Qt::Key_Up)
        m = new Message(Message::KEY_UP);
    else if (e->key() == Qt::Key_Z)
        m = new Message(Message::KEY_Z);
    else if (e->key() == Qt::Key_X)
        m = new Message(Message::KEY_X);
    else if (e->key() == Qt::Key_Space)
        m = new Message(Message::KEY_SPACE);

    if (m != NULL) {
        viewQueue->lock();
        viewQueue->push(m);
        viewQueue->unlock();
    }
}

void MainWindow::reset() {
    toggleGameOver(false);
    viewQueue->lock();
    viewQueue->push(new Message(Message::RESET));
    viewQueue->unlock();
}

void MainWindow::toggleGameOver(bool go) {
    if (go) {
        qDebug() << "TRUE TOGGLE";
        ui->gameoverLabel->show();
    }
    else {
        qDebug() << "False TOGGLE";
        ui->gameoverLabel->hide();
    }
}
