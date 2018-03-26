#include <common/types.h>
#include <common/terminal.h>
#include <gdt.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/driver.h>

using namespace mykernel;
using namespace mykernel::common;
using namespace mykernel::hardwarecommunication;
using namespace mykernel::drivers;

extern "C" void kernelMain(void* multiboot_structure, uint16_t magicnumber)
{
    TputS("PreInit \n");
    GlobalDescriptorTable gdt;  //Constructing the Global Descriptor Table
    InterruptManager interrupts(0x20, &gdt);
    DriverManager drvMan;

    TputS("Init    \n");
    PrintKeyboard pkb;
    KeyboardDriver keyboard(&interrupts, &pkb);
    drvMan.AddDriver(&keyboard);
    MouseCursor mc;
    MouseDriver mouse(&interrupts, &mc);
    drvMan.AddDriver(&mouse);

    TputS("PostInit\n");
    drvMan.ResetAll();
    drvMan.ActivateAll();
    interrupts.Activate();      ///After inits
    ///TsetColor(VGA_COLOR_BLUE,VGA_COLOR_GREEN);
    TputS("Loop    \n");
    while(1)
    {

    }
}


typedef void (*constructor)();
extern "C" constructor* start_ctors;
extern "C" constructor* end_ctors;
extern "C" void callConstructors()
{
    TputS("hi \n");
    for(constructor *i = start_ctors;i!=end_ctors; i++)
    {
        (*i)();
    }
}
