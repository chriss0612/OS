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
    uint8_t key = codetochar(dataport.Read());
    if(key)
        TputC(key);
    return esp;
}
uint8_t KeyboardDriver::codetochar(uint8_t in)
{
    switch(in)
    {
        case 0xFA: break;
        case 0x36: case 0x2A: shift=true;  break;
        case 0xAA: case 0xB6: shift=false; break;

        case 0x02: if(!shift) return'1'; return '!'; break;
        case 0x03: if(!shift) return'2'; return '"'; break;
        case 0x04: if(!shift) return'3'; return '§'; break;
        case 0x05: if(!shift) return'4'; return '$'; break;
        case 0x06: if(!shift) return'5'; return '%'; break;
        case 0x07: if(!shift) return'6'; return '&'; break;
        case 0x08: if(!shift) return'7'; return '/'; break;
        case 0x09: if(!shift) return'8'; return '('; break;
        case 0x0A: if(!shift) return'9'; return ')'; break;
        case 0x0B: if(!shift) return'0'; return '='; break;

        case 0x10: if(!shift) return'q'; return 'Q'; break;
        case 0x11: if(!shift) return'w'; return 'W'; break;
        case 0x12: if(!shift) return'e'; return 'E'; break;
        case 0x13: if(!shift) return'r'; return 'R'; break;
        case 0x14: if(!shift) return't'; return 'T'; break;
        case 0x15: if(!shift) return'z'; return 'Z'; break;
        case 0x16: if(!shift) return'u'; return 'U'; break;
        case 0x17: if(!shift) return'i'; return 'I'; break;
        case 0x18: if(!shift) return'o'; return 'O'; break;
        case 0x19: if(!shift) return'p'; return 'P'; break;

        case 0x1E: if(!shift) return'a'; return 'A'; break;
        case 0x1F: if(!shift) return's'; return 'S'; break;
        case 0x20: if(!shift) return'd'; return 'D'; break;
        case 0x21: if(!shift) return'f'; return 'F'; break;
        case 0x22: if(!shift) return'g'; return 'G'; break;
        case 0x23: if(!shift) return'h'; return 'H'; break;
        case 0x24: if(!shift) return'j'; return 'J'; break;
        case 0x25: if(!shift) return'k'; return 'K'; break;
        case 0x26: if(!shift) return'l'; return 'L'; break;

        case 0x2C: if(!shift) return'y'; return 'Y'; break;
        case 0x2D: if(!shift) return'x'; return 'X'; break;
        case 0x2E: if(!shift) return'c'; return 'C'; break;
        case 0x2F: if(!shift) return'v'; return 'V'; break;
        case 0x30: if(!shift) return'b'; return 'B'; break;
        case 0x31: if(!shift) return'n'; return 'N'; break;
        case 0x32: if(!shift) return'm'; return 'M'; break;
        case 0x33: if(!shift) return','; return ';'; break;
        case 0x34: if(!shift) return'.'; return ':'; break;
        case 0x35: if(!shift) return'-'; return '_'; break;

        case 0x1C: return '\n'; break;
        case 0x39: return ' '; break;
        break;
    default:
        if(in<0x80||!codetochar(in-0x80))
        {
            char* foo = (char *)"KEYBOARD 0x00\n";
            char* hex = (char *)"0123456789ABCDEF";
            foo[11] = hex[(in >> 4) & 0xF];
            foo[12] = hex[in & 0xF];
            TputS(foo);
        }
    }
    return 0;
}
