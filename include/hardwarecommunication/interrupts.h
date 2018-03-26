#ifndef __MYKERNEL__HARDWARECOMMUNICATIN__INTERRUPTMANAGER_H
#define __MYKERNEL__HARDWARECOMMUNICATIN__INTERRUPTMANAGER_H

#include <gdt.h>
#include <common/types.h>
#include <hardwarecommunication/port.h>

namespace mykernel
{
namespace hardwarecommunication
{

class InterruptManager;

class InterruptHandler
{
public:
    virtual mykernel::common::uint32_t HandleInterrupt(mykernel::common::uint32_t esp);

protected:
    mykernel::common::uint8_t interrupt;
    InterruptManager *interruptManager;

    InterruptHandler(mykernel::common::uint8_t interrupt, InterruptManager *interruptManager);
    ~InterruptHandler();
};

class InterruptManager
{
friend class InterruptHandler;
protected:
    struct GateDescriptor
    {
        mykernel::common::uint16_t handlerAddressLowBits;
        mykernel::common::uint16_t gdt_codeSegmentSelector;
        mykernel::common::uint8_t reserved;
        mykernel::common::uint8_t access;
        mykernel::common::uint16_t handlerAddressHighBits;
    } __attribute__((packed));

    static GateDescriptor interruptDescriptorTable[256];
    InterruptHandler *handlers[256];

    struct InterruptDescriptorTablePointer
    {
        mykernel::common::uint16_t size;
        mykernel::common::uint32_t base;
    } __attribute__((packed));

    mykernel::common::uint16_t hardwareInterruptOffset;
    static InterruptManager* ActiveInterruptManager;
    static void SetInterruptDescriptorTableEntry(mykernel::common::uint8_t interrupt,
            mykernel::common::uint16_t codeSegmentSelectorOffset, void (*handler)(),
            mykernel::common::uint8_t DescriptorPrivilegeLevel, mykernel::common::uint8_t DescriptorType);


    static void InterruptIgnore();

    static void HandleInterruptRequest0x00();
    static void HandleInterruptRequest0x01();
    static void HandleInterruptRequest0x02();
    static void HandleInterruptRequest0x03();
    static void HandleInterruptRequest0x04();
    static void HandleInterruptRequest0x05();
    static void HandleInterruptRequest0x06();
    static void HandleInterruptRequest0x07();
    static void HandleInterruptRequest0x08();
    static void HandleInterruptRequest0x09();
    static void HandleInterruptRequest0x0A();
    static void HandleInterruptRequest0x0B();
    static void HandleInterruptRequest0x0C();
    static void HandleInterruptRequest0x0D();
    static void HandleInterruptRequest0x0E();
    static void HandleInterruptRequest0x0F();
    static void HandleInterruptRequest0x31();

    static void HandleException0x00();
    static void HandleException0x01();
    static void HandleException0x02();
    static void HandleException0x03();
    static void HandleException0x04();
    static void HandleException0x05();
    static void HandleException0x06();
    static void HandleException0x07();
    static void HandleException0x08();
    static void HandleException0x09();
    static void HandleException0x0A();
    static void HandleException0x0B();
    static void HandleException0x0C();
    static void HandleException0x0D();
    static void HandleException0x0E();
    static void HandleException0x0F();
    static void HandleException0x10();
    static void HandleException0x11();
    static void HandleException0x12();
    static void HandleException0x13();

    static mykernel::common::uint32_t HandleInterrupt(mykernel::common::uint8_t interrupt, mykernel::common::uint32_t esp);
    mykernel::common::uint32_t DoHandleInterrupt(mykernel::common::uint8_t interrupt, mykernel::common::uint32_t esp);

    Port8BitSlow programmableInterruptControllerMasterCommandPort;
    Port8BitSlow programmableInterruptControllerMasterDataPort;
    Port8BitSlow programmableInterruptControllerSlaveCommandPort;
    Port8BitSlow programmableInterruptControllerSlaveDataPort;

public:
    InterruptManager(mykernel::common::uint16_t hardwareInterruptOffset, GlobalDescriptorTable* globalDescriptorTable);
    ~InterruptManager();
    mykernel::common::uint16_t HardwareInterruptOffset();
    void Activate();
    void Deactivate();
};
}
}
#endif
