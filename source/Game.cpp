#include "Game.h"
#include <QApplication>
#include <stdexcept>
#include <QDebug>

using std::domain_error;

Game::Game(VCQueue<Message *> *q) :
    level(0), msDropDelay(2000), linesCleared(0), eventQueue(q)
{
}

Game::~Game()
{
    delete t;
}

int Game::getLevel() const {
    return level;
}

QTimer *Game::getTimer() const {
    return t;
}

void Game::reset() {
    linesCleared = 0;
    syncLevelLines();
}

void Game::increaseLinesCleared(int l) {
    linesCleared += l;
    syncLevelLines();
}

void Game::syncLevelLinesHelper(int properLevel, int newDelay) {
    if (level != properLevel) {
        level = properLevel;
        msDropDelay = newDelay;
        qDebug() << "Level: " << level;
    }
}

void Game::syncLevelLines() {
    if (linesCleared < 5) {
        syncLevelLinesHelper(0, Game::LEVEL0_DELAY);
    } else if (linesCleared < 10) {
        syncLevelLinesHelper(1, Game::LEVEL1_DELAY);
    } else if (linesCleared < 15) {
        syncLevelLinesHelper(2, Game::LEVEL2_DELAY);
    } else if (linesCleared < 20) {
        syncLevelLinesHelper(3, Game::LEVEL3_DELAY);
    } else if (linesCleared < 25) {
        syncLevelLinesHelper(4, Game::LEVEL4_DELAY);
    } else if (linesCleared < 30) {
        syncLevelLinesHelper(5, Game::LEVEL5_DELAY);
    } else if (linesCleared < 35) {
        syncLevelLinesHelper(6, Game::LEVEL6_DELAY);
    } else if (linesCleared < 40) {
        syncLevelLinesHelper(7, Game::LEVEL7_DELAY);
    } else if (linesCleared < 45) {
        syncLevelLinesHelper(8, Game::LEVEL8_DELAY);
    } else {
        syncLevelLinesHelper(9, Game::LEVEL9_DELAY);
    }
}

void Game::drop() {
    static int c = 0;
    eventQueue->lock();
    eventQueue->push(new Message(Message::GRAVITY));
    qDebug() << "GRAVITY " << c;
    c++;
    eventQueue->unlock();
}

void Game::syncTimer() {
    t->setInterval(msDropDelay);
    t->start();
}

void Game::run() {
    t = new QTimer;
    t->setSingleShot(false);
    t->setInterval(msDropDelay);
    QObject::connect(t, SIGNAL(timeout()), this, SLOT(drop()), Qt::DirectConnection);
    QObject::connect(t, SIGNAL(timeout()), this, SLOT(syncTimer()), Qt::DirectConnection);
    t->start();
    exec();
}
