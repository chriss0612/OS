#ifndef __MYKERNEL__HARDWARECOMMUNICATIN__PORT_H
#define __MYKERNEL__HARDWARECOMMUNICATIN__PORT_H

#include <common/types.h>

namespace mykernel
{
namespace hardwarecommunication
{
class Port
{
protected:
    Port(mykernel::common::uint16_t portnumber); /// FIXME: Virtual as soon as memory management is implemented

    ~Port();
    mykernel::common::uint16_t portnumber;
};

class Port8Bit : public Port
{
public:
    Port8Bit(mykernel::common::uint16_t portnumber);
    ~Port8Bit();

    virtual mykernel::common::uint8_t Read();
    virtual void Write(mykernel::common::uint8_t data);

protected:
    static inline mykernel::common::uint8_t Read8(mykernel::common::uint16_t _port)
    {
        mykernel::common::uint8_t result;
        __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
        return result;
    }

    static inline void Write8(mykernel::common::uint16_t _port, mykernel::common::uint8_t _data)
    {
        __asm__ volatile("outb %0, %1" : : "a" (_data), "Nd" (_port));
    }
};



class Port8BitSlow : public Port8Bit
{
public:
    Port8BitSlow(mykernel::common::uint16_t portnumber);
    ~Port8BitSlow();

    virtual void Write(mykernel::common::uint8_t data);
protected:
    static inline void Write8Slow(mykernel::common::uint16_t _port, mykernel::common::uint8_t _data)
    {
        __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (_data), "Nd" (_port));
    }

};



class Port16Bit : public Port
{
public:
    Port16Bit(mykernel::common::uint16_t portnumber);
    ~Port16Bit();

    virtual mykernel::common::uint16_t Read();
    virtual void Write(mykernel::common::uint16_t data);

protected:
    static inline mykernel::common::uint16_t Read16(mykernel::common::uint16_t _port)
    {
        mykernel::common::uint16_t result;
        __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
        return result;
    }

    static inline void Write16(mykernel::common::uint16_t _port, mykernel::common::uint16_t _data)
    {
        __asm__ volatile("outw %0, %1" : : "a" (_data), "Nd" (_port));
    }
};



class Port32Bit : public Port
{
public:
    Port32Bit(mykernel::common::uint16_t portnumber);
    ~Port32Bit();

    virtual mykernel::common::uint32_t Read();
    virtual void Write(mykernel::common::uint32_t data);

protected:
    static inline mykernel::common::uint32_t Read32(mykernel::common::uint16_t _port)
    {
        mykernel::common::uint32_t result;
        __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
        return result;
    }

    static inline void Write32(mykernel::common::uint16_t _port, mykernel::common::uint32_t _data)
    {
        __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd" (_port));
    }
};
}
}
#endif // __PORT_H
