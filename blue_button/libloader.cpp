#include "libloader.h"
#include "QMessageBox"
#include "mainwindow.h"

//Класс загрузки внешней библиотеки ftMscLib, предоставленной разработчиками контроллера

LibLoader::LibLoader() //подгружаем динамическую библиотеку
{
    lib = new QLibrary("ftMscLib");

    ftxGetLibVersion = (FTXGETLIBVERSION)lib->resolve("ftxGetLibVersion");
    ftxGetLibVersionStr = (FTXGETLIBVERSIONSTR)lib->resolve("ftxGetLibVersionStr");
    ftxInitLib = (FTXINITLIB)lib->resolve("ftxInitLib");
    ftxOpenComDevice = (FTXOPENCOMDEVICE)lib->resolve("ftxOpenComDevice");
    ftxStartTransferArea = (FTXSTARTTRANSFERAREA)lib->resolve("ftxStartTransferArea");
    setFtMotorConfig = (SETFTMOTORCONFIG)lib->resolve("SetFtMotorConfig");
    setOutPwmValues = (SETOUTPWMVALUES)lib->resolve("SetOutPwmValues");
    ftxStopTransferArea = (FXTSTOPTRANSFERAREA)lib->resolve("ftxStopTransferArea");
    ftxCloseDevice = (FXTCLOSEDEVICE)lib->resolve("ftxCloseDevice");
    ftxCloseLib = (FXTCLOSELIB)lib->resolve("ftxCloseLib");
    getComStatus = (GETCOMSTATUS)lib->resolve("GetComStatus");
    enumComPorts = (ENUMCOMPORTS)lib->resolve("EnumComPorts");
    getAvailableComPorts = (GETAVAILABLECOMPORTS)lib->resolve("GetAvailableComPorts");
}

LibLoader::~LibLoader()
{

}
