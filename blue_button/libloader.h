#ifndef LIBLOADER_H
#define LIBLOADER_H
#include "qDebug"
#include "QLibrary"
#include <windows.h>

typedef DWORD (*FTXGETLIBVERSION)();
typedef DWORD (*FTXGETLIBVERSIONSTR)(LPSTR,DWORD);
typedef DWORD (*FTXINITLIB)();
typedef DWORD (*FTXSTARTTRANSFERAREA)(HANDLE);
typedef DWORD (*SETFTMOTORCONFIG)(HANDLE,int,int,bool);
typedef DWORD (*SETOUTPWMVALUES)(HANDLE,int,int,int);
typedef DWORD (*FXTSTOPTRANSFERAREA)(HANDLE);
typedef DWORD (*FXTCLOSEDEVICE)(HANDLE);
typedef DWORD (*FXTCLOSELIB)();
typedef DWORD (*GETCOMSTATUS)(HANDLE);
typedef DWORD (*ENUMCOMPORTS)(DWORD,LPSTR,DWORD);
typedef DWORD (*GETAVAILABLECOMPORTS)(int);
typedef HANDLE (*FTXOPENCOMDEVICE)(char *, DWORD, DWORD *);

enum MotorIdx {MOTOR_1 = 0, MOTOR_2, MOTOR_3, MOTOR_4};
enum PwmOut {OUT1 = 0, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7, OUT8};

class LibLoader
{

public:
    QLibrary *lib;
    LibLoader();
    ~LibLoader();

    bool loaded() const {return lib->load();}

    FTXGETLIBVERSION ftxGetLibVersion;
    FTXGETLIBVERSIONSTR ftxGetLibVersionStr;
    FTXINITLIB ftxInitLib;
    FTXOPENCOMDEVICE ftxOpenComDevice;
    FTXSTARTTRANSFERAREA ftxStartTransferArea;
    SETFTMOTORCONFIG setFtMotorConfig;
    SETOUTPWMVALUES setOutPwmValues;
    FXTSTOPTRANSFERAREA ftxStopTransferArea;
    FXTCLOSEDEVICE ftxCloseDevice;
    FXTCLOSELIB ftxCloseLib;
    GETCOMSTATUS getComStatus;
    GETAVAILABLECOMPORTS getAvailableComPorts;
    ENUMCOMPORTS enumComPorts;
};

#endif // LIBLOADER_H
