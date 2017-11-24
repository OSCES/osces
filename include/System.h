#ifndef OSCES_FRAMEWORK_INTERFACE_H
#define OSCES_FRAMEWORK_INTERFACE_H


#include "DisplayInterface.h"
#include "KeyboardInterface.h"
#include "SysTimerInterface.h"

enum ApplicationStatus_t
{
    OSCES_APP_SUCCESS_STATUS = 0,
    OSCES_APP_FAILED_STATUS,
};

//enum FrameworkStatus_t
//{
//    OSCES_FRAMEWORK_INIT_SUCCESS = 0,
//    OSCES_FRAMEWORK_INIT_FAILED = 0,
//};

namespace Sys
{
    DisplayInterface*  getDisplay();
    KeyboardInterface* getKeyboard();
    SysTimerInterface* getSysTimer();

    bool applicationRunning();
};

//class OscesFrameworkInterface_t
//{
//public:
//    virtual DisplayInterface_t*  GetDisplay() = 0;
//    virtual KeyboardInterface_t* GetKeyboard() = 0;
//    virtual SysTimerInterface_t* GetSysTimer() = 0;
//    virtual bool        IsApplicationRun() = 0;
//
//};


#endif // OSCES_FRAMEWORK_INTERFACE_H
