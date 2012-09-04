#include <QtGui/QApplication>
#include "mainwindow.h"
#include "TetrominoI.h"
#include "Tetromino.h"
#include "Controller.h"
#include "VCQueue.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    VCQueue<Message*> *msgQueue = new VCQueue<Message*>;
    MainWindow w(msgQueue);
    Controller *controllerThread = new Controller(&w, msgQueue);

    w.show();
    controllerThread->start();

    int resultCode = a.exec();

    controllerThread->exit(0);

    delete controllerThread;
    delete msgQueue;

    return resultCode;
}
