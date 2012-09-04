#ifndef GAME_H
#define GAME_H

#include <QThread>
#include <QTimer>
#include "VCQueue.h"
#include "Message.h"

class Game : public QThread
{
    Q_OBJECT

public:
    static const int LEVEL0_DELAY = 2000;
    static const int LEVEL1_DELAY = 1900;
    static const int LEVEL2_DELAY = 1800;
    static const int LEVEL3_DELAY = 1600;
    static const int LEVEL4_DELAY = 1400;
    static const int LEVEL5_DELAY = 1150;
    static const int LEVEL6_DELAY = 900;
    static const int LEVEL7_DELAY = 650;
    static const int LEVEL8_DELAY = 450;
    static const int LEVEL9_DELAY = 250;

    Game(VCQueue<Message*> *q);
    ~Game();

    int getLevel() const;
    QTimer *getTimer() const;

    void increaseLinesCleared(int l);
    void reset();

public slots:
    void drop();
    void syncTimer();

protected:
    void run();

private:
    int level;
    int msDropDelay;    // milliseconds
    int linesCleared;

    QTimer *t;
    VCQueue<Message*> *eventQueue;

    void syncLevelLinesHelper(int properLevel, int newDelay);
    void syncLevelLines();
};

#endif // GAME_H
