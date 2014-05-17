
#include "GpioDriver.h"


GpioPin_t::GpioPin_t( Port_t port, Pin_t pin )
{
    m_Port  = (GPIO_TypeDef*)port; 
    m_Pin   = pin;

    //TODO: Enable appropriate peripheral
}

GpioPin_t::~GpioPin_t()
{

}

void GpioPin_t::InitPin( PinMode_t pinMode, OutType_t outType, PullType_t pullType )
{
    GPIO_InitTypeDef gpioInitStruct;

    gpioInitStruct.GPIO_Mode  = (GPIOMode_TypeDef)pinMode;
    gpioInitStruct.GPIO_OType = (GPIOOType_TypeDef)outType;
    gpioInitStruct.GPIO_Speed =  GPIO_Speed_100MHz;
    gpioInitStruct.GPIO_PuPd  = (GPIOPuPd_TypeDef)pullType;
    gpioInitStruct.GPIO_Pin   = m_Pin;

    GPIO_Init( m_Port, &gpioInitStruct );
}

void GpioPin_t::MakeOutOd( void )
{
    InitPin(MODE_OUT, OUT_OD, PULL_NO);
}

void GpioPin_t::MakeOut( void )
{
    InitPin(MODE_OUT, OUT_PP, PULL_NO);
}

void GpioPin_t::MakeInNonPull( void )
{  
    MakeOut();
}

void GpioPin_t::MakeInPullUp( void )
{
    InitPin(MODE_IN, OUT_PP, PULL_UP);
}

void GpioPin_t::MakeInPullDown( void )
{
    InitPin(MODE_IN, OUT_PP, PULL_DOWN);
}

void GpioPin_t::Set( void )
{
    GPIO_SetBits( m_Port, m_Pin );
}

void GpioPin_t::Clear( void )
{
    GPIO_ResetBits( m_Port, m_Pin );
}

uint8_t GpioPin_t::Read( void )
{
    return GPIO_ReadInputDataBit( m_Port, m_Pin);
}

