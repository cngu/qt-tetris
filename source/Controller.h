#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QThread>
#include <QKeyEvent>
#include "mainwindow.h"
#include "VCQueue.h"
#include "Tetromino.h"
#include "Controller.h"
#include "Message.h"
#include "Game.h"
#include "BlockGenerator.h"

class Controller : public QThread
{
    Q_OBJECT
private:
    MainWindow *view;
    VCQueue<Message*> *updateQueue;
    Tetromino *currentBlock;
    Game *g;
    BlockGenerator generator;

public:
    Controller(MainWindow *ui, VCQueue<Message*> *q);

protected:
    void run();
    void handleSpawn();
    void handleGravity();
    void handleGameOver();
    void handleReset();
    void handleLeftArrow();
    void handleRightArrow();
    void handleUpArrow();
    void handleDownArrow();
    void handleZKey();
    void handleXKey();
    void handleSpaceKey();
};

#endif // CONTROLLER_H
