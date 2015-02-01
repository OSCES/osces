#include "OscesFramework.h"
#include "GpioDriver.h"
#include "Leds/leds.h"
#include "Buttons/Buttons.h"

#include "ClockManager/ClockManager.h"
#include "Drivers/InterruptManager.h"
#include "Drivers/DmaDriver.h"
#include <stdlib.h>

#include <intrinsics.h>
#include <stdio.h>
#include "SysTimerDriver.h"
#include "Kernel/ThreadPlatform.h"
#include "Kernel/Kernel.h"


//#define STANALONE

#ifdef STANALONE
extern void standalone_main( OscesFramework_t* pSystem );
#endif

Kernel_t m_Kernel;

OscesFramework_t::OscesFramework_t()
{
    m_IsApplicationRun = true;
}

SysTimerInterface_t* OscesFramework_t::GetSysTimer()
{
    return m_pSysTimer;
}

DisplayInterface_t* OscesFramework_t::GetDisplay()
{
    return m_pDisplay;
}

KeyboardInterface_t* OscesFramework_t::GetKeyboard()
{
    return m_pKeyboard;
}

ThreadInterface_t*  OscesFramework_t::CreateThread( uint32_t stackSize, ThreadRoutine_t fpThreadRoutine, void* pContext )
{
    ThreadPlatform_t* pThreadPlatform = new ThreadPlatform_t( &m_Kernel );

    uint32_t threadId = m_pScheduler->ThreadCreate( stackSize, fpThreadRoutine, pThreadPlatform, pContext );
  
    pThreadPlatform->SetId( threadId );
    
    return pThreadPlatform;
}

void  OscesFramework_t::DestroyThread( ThreadInterface_t* pThread )
{
    ThreadPlatform_t* pThreadPlatform = static_cast< ThreadPlatform_t* >( pThread ); //TODO: delete cast !!!
    
    uint32_t threadId = pThreadPlatform->GetId();
    
    m_pScheduler->ThreadDestroy( threadId );
 
    delete pThread;// pThreadPlatform;
}

void *operator new( size_t size )
{
    return malloc( size );
}
void operator delete(void *p)
{
    free( p );
}

uint8_t ProcessStack[ 512 ];




RCC_ClocksTypeDef freq;
OscesFramework_t  m_OscesFramework;



int main()
{  
    //__svc(SVC_00);
  
    //__svc( 0 );
  
    ClockManager_t &clockManager = ClockManager_t::GetInstance();   
    clockManager.SetSystemClock( SYSTEM_CLOCK_120MHz );
    
    m_OscesFramework.Init();
    m_Kernel.Init();
    
#ifdef STANALONE
    standalone_main( &m_OscesFramework );
#else
    osces_main( &m_OscesFramework );
#endif
   
    m_Kernel.DeInit();
    m_OscesFramework.DeInit();
    
    return 0;
}


bool OscesFramework_t::IsApplicationRun()
{
    return m_IsApplicationRun;
}

OscesFrameworkStatus_t OscesFramework_t::Init()
{
    OscesFrameworkStatus_t status = OSCES_FRAMEWORK_INIT_SUCCESS;

    DmaInit();
    
    __disable_interrupt();
    
    InterruptManager_t::Init();
    
    try
    { 
        m_pDisplay         = new DisplayPlatform_t;
        m_pKeyboard        = new KeyboardPlatform_t;
        m_pSysTimer        = new SysTimerPlatform_t;
        m_pScheduler       = new SchedulerPlatform_t();
    }
    catch(...)
    { 
    }
    
   // __enable_interrupt();
    
    //m_pSysTimer->Init();
    m_pKeyboard->Init();
    m_pDisplay->Init(400, 300);

    m_pDisplay->Clear();
    m_pDisplay->Flip();
    m_pDisplay->Clear();
    m_pDisplay->Flip();
    
    //m_pScheduler->Start( 10 );    
   
    __enable_interrupt();
    
    return status;
}


void OscesFramework_t::DeInit()
{
    delete m_pScheduler;
    delete m_pSysTimer;
    delete m_pKeyboard;
    delete m_pDisplay;
}
