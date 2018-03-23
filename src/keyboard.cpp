#include "Keyboard.h"
#include "terminal.h"


KeyboardDriver::KeyboardDriver(InterruptManager *manager) : InterruptHandler(0x21,manager), dataport(0x60), commandport(0x64)
{
    while(commandport.Read() & 0x1)
        dataport.Read();
    commandport.Write(0xAE);
    commandport.Write(0x20);
    uint8_t status = (dataport.Read() | 1) & ~0x10;
    commandport.Write(0x60);
    dataport.Write(status);
    dataport.Write(0xF4);
}
KeyboardDriver::~KeyboardDriver()
{

}
uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();
    if(key<=0x80)
    {

        switch(key)
        {   case 0x02: TputC('1'); break;
            case 0x03: TputC('2'); break;
            case 0x04: TputC('3'); break;
            case 0x05: TputC('4'); break;
            case 0x06: TputC('5'); break;
            case 0x07: TputC('6'); break;
            case 0x08: TputC('7'); break;
            case 0x09: TputC('8'); break;
            case 0x0A: TputC('9'); break;
            case 0x0B: TputC('0'); break;

            case 0x10: TputC('q'); break;
            case 0x11: TputC('w'); break;
            case 0x12: TputC('e'); break;
            case 0x13: TputC('r'); break;
            case 0x14: TputC('t'); break;
            case 0x15: TputC('z'); break;
            case 0x16: TputC('u'); break;
            case 0x17: TputC('i'); break;
            case 0x18: TputC('o'); break;
            case 0x19: TputC('p'); break;

            case 0x1E: TputC('a'); break;
            case 0x1F: TputC('s'); break;
            case 0x20: TputC('d'); break;
            case 0x21: TputC('f'); break;
            case 0x22: TputC('g'); break;
            case 0x23: TputC('h'); break;
            case 0x24: TputC('j'); break;
            case 0x25: TputC('k'); break;
            case 0x26: TputC('l'); break;

            case 0x2C: TputC('y'); break;
            case 0x2D: TputC('x'); break;
            case 0x2E: TputC('c'); break;
            case 0x2F: TputC('v'); break;
            case 0x30: TputC('b'); break;
            case 0x31: TputC('n'); break;
            case 0x32: TputC('m'); break;
            case 0x33: TputC(','); break;
            case 0x34: TputC('.'); break;
            case 0x35: TputC('-'); break;

            case 0x1C: TputC('\n'); break;
            case 0x39: TputC(' '); break;
            break;
        default:
            char *foo = (char *)"KEY STROKE 0x00 End\n";
            char *hex = (char *)"0123456789ABCD";
            foo[13] = hex[(key>>4)&0xF];
            foo[14] = hex[key&0xF];
            TputS(foo);
        }
    }
    return esp;
}
