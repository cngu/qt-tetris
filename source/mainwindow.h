#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QEvent>
#include <QColor>
#include "Tetromino.h"
#include "VCQueue.h"
#include "Message.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    VCQueue<Message*> *viewQueue;
    QColor blankCellColor;

    void initWindow();
    void eraseLine(int line);
    void swapLines(int l1, int l2);
    void collapse(int start);

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(VCQueue<Message*> *q, QWidget *parent = 0);
    ~MainWindow();
    bool checkCollision(Tetromino *t) const;
    bool checkCollision(Tetromino *t, Message *direction) const;

public slots:
    void draw(Tetromino *t);
    void erase(Tetromino *t);
    void reset();
    int clearLines();
    void clearBoard();
    void toggleGameOver(bool go);

protected:
    void keyPressEvent(QKeyEvent* e);
};

#endif // MAINWINDOW_H
