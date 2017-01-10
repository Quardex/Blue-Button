#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QApplication>
#include <deque>
#include <QObject>
#include <QHash>
#include <QList>
#include <QThread>
#include <ostream>
#include <qDebug>

struct Button {
    QString name;
    int code;
    int controller;
    int motor;
    bool direction;
    int speed;
    friend std::ostream& operator << ( std::ostream& s, Button& my )
    {
        qDebug() << "speed= " << my.speed << " code= " << my.code << endl;
    }
};

class Controller
{
private:
    std::deque<Button> buttons;
    QHash<int, QList<Button> > memory;
    int getMemorySpeed(Button button, bool pressed);


public:
    std::deque<Button>& getButtons();
    QString getFileCodeFromButton(int index);
    Button getButtonFromFileCode(QString fileCode);
    void exec(int key, bool pressed);
};

struct Sleeper : private QThread
{
    static void msleep(unsigned long msecs) { QThread::msleep(msecs); }
};

#endif // CONTROLLER_H
