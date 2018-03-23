#include "mouse.h"
#include "terminal.h"


MouseDriver::MouseDriver(InterruptManager *manager) : InterruptHandler(0x2C,manager), dataport(0x60), commandport(0x64)
{
    offset = 0;
    buttons = 0;
    x=40;
    y=12;
    TswCol(x,y);
    commandport.Write(0xAB);
    commandport.Write(0x20);
    uint8_t status = dataport.Read() | 2;
    commandport.Write(0x60);
    dataport.Write(status);
    commandport.Write(0xD4);
    dataport.Write(0xF4);
    dataport.Read();
}
MouseDriver::~MouseDriver()
{

}
uint32_t MouseDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t status = commandport.Read();

    if(status & 0x20)
    {
        buffer[offset] = dataport.Read();
        offset = (offset + 1)%3;
        if(offset == 0)
        {
            TswCol(x,y);
            x+=buffer[1];
            y-=buffer[2];
            if(x<0) x=0;
            if(y<0) y=0;
            if(x>79) x=79;
            if(y>20) x=20;
            TswCol(x,y);
        }
    }
    return esp;
}

