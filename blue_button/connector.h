#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QApplication>
#include <deque>
#include <windows.h>

class Connector
{

private:
    bool found;
    bool connected;
    bool started;
    std::deque<QString> ports;

public:
    HANDLE fthdl;
    Connector();
    bool searchCom();
    bool openCom(char* comPortName);
    bool closeCom();
    bool startTA();
    bool stopTA();
    bool getFound() const {return found;}
    bool getConnected() const {return connected;}
    bool getStarted() const {return started;}
    const std::deque<QString>& getPorts() const {return ports;}
};

#endif // CONNECTOR_H
