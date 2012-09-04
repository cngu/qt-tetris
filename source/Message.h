#ifndef MESSAGE_H
#define MESSAGE_H

class Message
{
public:
    Message(int msg);

    const int message;

    static const int SPAWN = 0;
    static const int GRAVITY = -1;
    static const int GAMEOVER = -2;
    static const int RESET = -3;

    static const int KEY_LEFT = 10;
    static const int KEY_RIGHT = 11;
    static const int KEY_UP = 12;
    static const int KEY_DOWN = 13;
    static const int KEY_Z = 14;
    static const int KEY_X = 15;
    static const int KEY_SPACE = 16;
};

#endif // MESSAGE_H
