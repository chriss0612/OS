#ifndef __DRIVERS_MOUSE_H
#define __DRIVERS_MOUSE_H

#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>

namespace mykernel
{
namespace drivers
{

class MouseEventHandler
{
public:
    virtual void OnMouseMove(mykernel::common::int8_t, mykernel::common::int8_t) {}
    virtual void OnMouseButtonUp(mykernel::common::int8_t) {}
    virtual void OnMouseButtonDown(mykernel::common::int8_t) {}
    virtual void OnMouseActivate() {}
};

class MouseCursor : public MouseEventHandler
{
private:
    mykernel::common::int8_t x,y;
public:
    virtual void OnMouseMove(mykernel::common::int8_t, mykernel::common::int8_t);
    virtual void OnMouseButtonUp(mykernel::common::int8_t);
    virtual void OnMouseButtonDown(mykernel::common::int8_t);
    virtual void OnMouseActivate();
};

class MouseDriver : public mykernel::hardwarecommunication::InterruptHandler, public Driver
{
public:
    MouseDriver(mykernel::hardwarecommunication::InterruptManager *, MouseEventHandler *);
    ~MouseDriver();
    virtual mykernel::common::uint32_t HandleInterrupt(mykernel::common::uint32_t esp);

private:
    MouseEventHandler *handler;
    mykernel::hardwarecommunication::Port8Bit dataport;
    mykernel::hardwarecommunication::Port8Bit commandport;

    mykernel::common::uint8_t buffer[3];
    mykernel::common::uint8_t offset;
    mykernel::common::uint8_t buttons;
};
}
}
#endif // __Mouse_H
