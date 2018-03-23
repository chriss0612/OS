#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "interrupts.h"
#include "port.h"


class KeyboardDriver : public InterruptHandler
{
    public:
        KeyboardDriver(InterruptManager *);
        ~KeyboardDriver();
        virtual uint32_t HandleInterrupt(uint32_t esp);

    private:
        Port8Bit dataport;
        Port8Bit commandport;
};

#endif // __KEYBOARD_H
