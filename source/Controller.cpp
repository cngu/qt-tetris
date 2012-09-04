#include <QDebug>
#include <QString>
#include <QMetaObject>
#include "Controller.h"

Controller::Controller(MainWindow *ui, VCQueue<Message *> *q) :
    view(ui), updateQueue(q), currentBlock(NULL)
{

}

void Controller::handleSpawn() {
    QString s = "Handle Spawn - ";
    if (currentBlock != NULL) {
        delete currentBlock;
    }
    currentBlock = generator.next();
    if (view->checkCollision(currentBlock)) {
        s += "Collision";
        updateQueue->lock();
        // why does flush here clear the below push as well?
        updateQueue->push(new Message(Message::GAMEOVER));
        updateQueue->unlock();
    } else {
        s += "No Collision";
        QMetaObject::invokeMethod(view, "draw", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
    }
    qDebug() << s;
}

void Controller::handleGravity() {
    if (currentBlock == NULL)
        return;

    Message *m = new Message(Message::KEY_DOWN);
    if (view->checkCollision(currentBlock, m)) {
        int linesCleared;
        QMetaObject::invokeMethod(view, "clearLines", Qt::BlockingQueuedConnection, Q_RETURN_ARG(int, linesCleared));
        g->increaseLinesCleared(linesCleared);
        updateQueue->lock();
        updateQueue->push(new Message(Message::SPAWN));
        updateQueue->unlock();
    }
    else {
        QMetaObject::invokeMethod(view, "erase", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
        currentBlock->move(0, 1);
        QMetaObject::invokeMethod(view, "draw", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
    }
}

void Controller::handleGameOver() {
    QMetaObject::invokeMethod(view, "toggleGameOver", Qt::BlockingQueuedConnection, Q_ARG(bool, true));
    currentBlock = NULL;
}

void Controller::handleReset() {
    QMetaObject::invokeMethod(view, "clearBoard", Qt::BlockingQueuedConnection);
    g->reset();
    updateQueue->lock();
    updateQueue->push(new Message(Message::SPAWN));
    updateQueue->unlock();
}

void Controller::handleLeftArrow() {
    if (currentBlock == NULL)
        return;

    Message *m = new Message(Message::KEY_LEFT);
    if ( !(view->checkCollision(currentBlock, m)) ) {
        QMetaObject::invokeMethod(view, "erase", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
        currentBlock->move(-1, 0);
        QMetaObject::invokeMethod(view, "draw", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
    }
}

void Controller::handleRightArrow() {
    if (currentBlock == NULL)
        return;

    Message *m = new Message(Message::KEY_RIGHT);
    if ( !(view->checkCollision(currentBlock, m)) ) {
        QMetaObject::invokeMethod(view, "erase", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
        currentBlock->move(1, 0);
        QMetaObject::invokeMethod(view, "draw", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
    }
}

void Controller::handleUpArrow() {
    handleXKey();
}

void Controller::handleDownArrow() {
    if (currentBlock == NULL)
        return;

    Message *m = new Message(Message::KEY_DOWN);
    if ( !(view->checkCollision(currentBlock, m)) ) {
        QMetaObject::invokeMethod(view, "erase", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
        currentBlock->move(0, 1);
        QMetaObject::invokeMethod(view, "draw", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
    }
}

void Controller::handleZKey() {
    if (currentBlock == NULL)
        return;

    QMetaObject::invokeMethod(view, "erase", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
    currentBlock->rotateCounterClockwise();
    if (view->checkCollision(currentBlock)) {
        currentBlock->move(-1, 0);
        if (view->checkCollision(currentBlock)) {
            currentBlock->move(2, 0);
            if (view->checkCollision(currentBlock)) {
                currentBlock->move(-1, 0);
                currentBlock->rotateClockwise();
                QMetaObject::invokeMethod(view, "draw", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
            }
            QMetaObject::invokeMethod(view, "draw", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
        }
        QMetaObject::invokeMethod(view, "draw", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
    }
    QMetaObject::invokeMethod(view, "draw", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
}

void Controller::handleXKey() {
    if (currentBlock == NULL)
        return;

    QMetaObject::invokeMethod(view, "erase", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
    currentBlock->rotateClockwise();
    if (view->checkCollision(currentBlock)) {
        currentBlock->move(-1, 0);
        if (view->checkCollision(currentBlock)) {
            currentBlock->move(2, 0);
            if (view->checkCollision(currentBlock)) {
                currentBlock->move(-1, 0);
                currentBlock->rotateCounterClockwise();
                QMetaObject::invokeMethod(view, "draw", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
            }
            QMetaObject::invokeMethod(view, "draw", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
        }
        QMetaObject::invokeMethod(view, "draw", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
    }
    QMetaObject::invokeMethod(view, "draw", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
}

void Controller::handleSpaceKey() {
    if (currentBlock == NULL)
        return;

    Message *m = new Message(Message::KEY_DOWN);
    QMetaObject::invokeMethod(view, "erase", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));
    while ( !(view->checkCollision(currentBlock, m)) ) {
        currentBlock->move(0, 1);
    }
    QMetaObject::invokeMethod(view, "draw", Qt::BlockingQueuedConnection, Q_ARG(Tetromino *, currentBlock));

    int linesCleared;
    QMetaObject::invokeMethod(view, "clearLines", Qt::BlockingQueuedConnection, Q_RETURN_ARG(int, linesCleared));
    g->increaseLinesCleared(linesCleared);
    updateQueue->lock();
    updateQueue->push(new Message(Message::SPAWN));
    updateQueue->unlock();
}

void Controller::run() {
    qRegisterMetaType<Tetromino*>("Tetromino*");
    g = new Game(updateQueue);
    g->start();

    updateQueue->lock();
    updateQueue->push(new Message(Message::SPAWN));
    updateQueue->unlock();

    while (true) {
        updateQueue->lock();
        if (!(updateQueue->empty())) {
            Message *m = updateQueue->front();
            updateQueue->unlock();
            int event = m->message;

            switch (event) {
            case Message::SPAWN:
                qDebug() << "SPAWN";
                handleSpawn();
                break;
            case Message::GRAVITY:
                handleGravity();
                break;
            case Message::GAMEOVER:
                qDebug() << "GAMEOVER";
                handleGameOver();
                break;
            case Message::RESET:
                qDebug() << "RESET";
                handleReset();
                break;
            case Message::KEY_LEFT:
                qDebug() << "LEFT";
                handleLeftArrow();
                break;
            case Message::KEY_RIGHT:
                qDebug() << "RIGHT";
                handleRightArrow();
                break;
            case Message::KEY_UP:
                qDebug() << "UP";
                handleUpArrow();
                break;
            case Message::KEY_DOWN:
                qDebug() << "DOWN";
                handleDownArrow();
                break;
            case Message::KEY_Z:
                qDebug() << "Z";
                handleZKey();
                break;
            case Message::KEY_X:
                qDebug() << "X";
                handleXKey();
                break;
            case Message::KEY_SPACE:
                qDebug() << "SPACE";
                handleSpaceKey();
                break;
            default:
                qDebug() << "UNKNOWN EVENT RECEIVED!";
                break;
            }

            delete m;
            updateQueue->lock();
            updateQueue->pop();
        }
        updateQueue->unlock();
    }

    g->exit(0);
}
