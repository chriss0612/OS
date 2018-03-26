#ifndef __DRIVERS_KEYBOARD_H
#define __DRIVERS_KEYBOARD_H

#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>



namespace mykernel
{
namespace drivers
{

enum KeyCode
{
    KEY_1 = 0x02,
    KEY_2 = 0x03,
    KEY_3 = 0x04,
    KEY_4 = 0x05,
    KEY_5 = 0x06,
    KEY_6 = 0x07,
    KEY_7 = 0x08,
    KEY_8 = 0x09,
    KEY_9 = 0x0A,
    KEY_0 = 0x0B,

    KEY_Q = 0x10,
    KEY_W = 0x11,
    KEY_E = 0x12,
    KEY_R = 0x13,
    KEY_T = 0x14,
    KEY_Z = 0x15,
    KEY_U = 0x16,
    KEY_I = 0x17,
    KEY_O = 0x18,
    KEY_P = 0x19,

    KEY_A = 0x1E,
    KEY_S = 0x1F,
    KEY_D = 0x20,
    KEY_F = 0x21,
    KEY_G = 0x22,
    KEY_H = 0x23,
    KEY_J = 0x24,
    KEY_K = 0x25,
    KEY_L = 0x26,

    KEY_Y = 0x2C,
    KEY_X = 0x2D,
    KEY_C = 0x2E,
    KEY_V = 0x2F,
    KEY_B = 0x30,
    KEY_N = 0x31,
    KEY_M = 0x32,
    KEY_COMMA = 0x33,
    KEY_DOT = 0x34,
    KEY_MINUS = 0x35,

    KEY_RETURN = 0x1C,
    KEY_SPACE = 0x39
};


class KeyboardEventHandler
{
public:
    virtual void OnKeyDown(char);
    virtual void OnKeyUp(char);
};

class PrintKeyboard : public KeyboardEventHandler
{
public:
    virtual void OnKeyDown(char);
    virtual void OnKeyUp(char);
};


class KeyboardDriver : public mykernel::hardwarecommunication::InterruptHandler, public Driver
{
    public:
        KeyboardDriver(mykernel::hardwarecommunication::InterruptManager *, KeyboardEventHandler *);
        ~KeyboardDriver();
        virtual mykernel::common::uint32_t HandleInterrupt(mykernel::common::uint32_t esp);

    private:
        KeyboardEventHandler *handler;
        mykernel::hardwarecommunication::Port8Bit dataport;
        mykernel::hardwarecommunication::Port8Bit commandport;
        bool shift = false;
        mykernel::common::uint8_t codetochar(mykernel::common::uint8_t);
};
}
}
#endif // __KEYBOARD_H
