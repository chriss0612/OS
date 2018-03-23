#include "types.h"
#include "terminal.h"
#include "gdt.h"
#include "interrupts.h"


extern "C" void kernelMain(void* multiboot_structure, uint16_t magicnumber)
{
    GlobalDescriptorTable gdt;  //Constructing the Global Descriptor Table
    InterruptManager interrupts(0x20, &gdt);

    interrupts.Activate();      ///After inits
    TputS("Hello World! --myKernel\n");
    TputC('>');
    while(1)
    {

    }
}


typedef void (*constructor)();
extern "C" constructor* start_ctors;
extern "C" constructor* end_ctors;
extern "C" void callConstructors()
{
    for(constructor *i = start_ctors;i!=end_ctors; i++)
    {
        (*i)();
    }
}
