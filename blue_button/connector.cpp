
#include "connector.h"
#include "mainwindow.h"
#include <libloader.h>
#include "adds.h"

extern LibLoader libLoader;
extern boolean debug;

//Класс отвечает за подключение к контроллеру

Connector::Connector() { //устанавливаем флаги в начальные значения
    found = false;
    connected = false;
    started = false;
}

//поиск доступных портов
bool Connector::searchCom()
{
    ports.clear();
    char *portName = new char[256];
    for (int i=0;i<libLoader.getAvailableComPorts(0);i++) {
        libLoader.enumComPorts(i,portName,256);
        ports.push_back(QString::fromLocal8Bit(portName));
    }
    return found = ports.size()>0 || debug;
}

//подключение по определенному порту
bool Connector::openCom(char* comPortName) {
    DWORD errCode = FTLIB_ERR_SUCCESS;
    fthdl = libLoader.ftxOpenComDevice(comPortName, 38400, &errCode);
    if (errCode==FTLIB_ERR_SUCCESS || debug) connected = true;
    return connected;
}

//отключение открытого порта
bool Connector::closeCom() {
    if (libLoader.ftxCloseDevice(fthdl)==FTLIB_ERR_SUCCESS || debug) {
        started = false;
        connected = false;
    }
    return !connected;
}

//запуск протокола общения с контроллером (Transfer Area) [необходимо уже иметь подключение через порт]
bool Connector::startTA() {
    if (libLoader.ftxStartTransferArea(fthdl)==FTLIB_ERR_SUCCESS || debug) {
        started = true;
    }
    return started;
}

//остановка протокола общения с контроллером (Transfer Area) [необходимо уже иметь подключение через порт]
bool Connector::stopTA() {
    if (libLoader.ftxStopTransferArea(fthdl)==FTLIB_ERR_SUCCESS || debug) {
        started = false;
    }
    return !started;
}
