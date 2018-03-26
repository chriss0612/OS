#include <drivers/mouse.h>
#include <common/terminal.h>

using namespace mykernel::drivers;
using namespace mykernel::common;

void MouseCursor::OnMouseMove(int8_t dx, int8_t dy)
{

    TswCol(x,y);
    x += dx;
    if(x >= 80)
        x = 79;
    if(x < 0)
        x = 0;
    y -= dy;
    if(y >= 25)
        y = 24;
    if(y < 0)
        y = 0;
    TswCol(x,y);
}
void MouseCursor::OnMouseButtonUp(int8_t i)
{

}
void MouseCursor::OnMouseButtonDown(int8_t i)
{
    TsetPos(x,y);
}
void MouseCursor::OnMouseActivate()
{
    x=40;
    y=12;
    TswCol(x,y);
}

MouseDriver::MouseDriver(mykernel::hardwarecommunication::InterruptManager *manager, MouseEventHandler *evHandler) : InterruptHandler(0x2C,manager), dataport(0x60), commandport(0x64)
{
    handler = evHandler;
    offset = 0;
    buttons = 0;
    commandport.Write(0xAB);
    commandport.Write(0x20);
    uint8_t status = dataport.Read() | 2;
    commandport.Write(0x60);
    dataport.Write(status);
    commandport.Write(0xD4);
    dataport.Write(0xF4);
    dataport.Read();
    handler->OnMouseActivate();
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
        if(handler == 0)
            return esp;
        offset = (offset + 1) % 3;
        if(buffer[1] || buffer[2])
        {
            handler->OnMouseMove(buffer[1],buffer[2]);
            buffer[1]=0;
            buffer[2]=0;
        }
        for(int i=0; i<3; i++)
            if((buttons & (1<<i)) != (buffer[0] & (1<<i)))
            {
                if((buttons & (1<<i)))
                {
                    handler->OnMouseButtonDown(i);
                }
                else
                {
                    handler->OnMouseButtonUp(i);
                }

            }
        buttons = buffer[0];
    }
    return esp;
}
