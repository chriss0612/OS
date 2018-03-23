#include "terminal.h"


#define VID_MEM 0x0b8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

uint8_t _X=0;
uint8_t _Y=0;
uint8_t _COLOR=0x0F;

void TsetPos(uint8_t x, uint8_t y)
{
    _X=x;
    _Y=y;
}
void TsetColor(vga_color b,vga_color f)
{
    _COLOR=f<<4|b;
}
void TputC(char c)
{
    if(c == '\n')
    {
        _X=0;
        _Y++;
        return;
    }
    else if(c == '\r')
    {
        _X=0;
        return;
    }

    if(_X>=VGA_WIDTH)
    {
        _Y++;
        _X=0;
    }
    if(_Y>=VGA_HEIGHT)
    {
        _Y=0;
    }
    *(((uint16_t*)VID_MEM)+(_X + _Y * VGA_WIDTH)) = _COLOR<<8 | c;
    _X++;
}
void TputS(const char* str)
{
    while(*str != '\0')
    {
        TputC(*str);
        str++;
    }
}
void TgetPos(uint8_t*x,uint8_t *y)
{
    *x = _X;
    *y = _Y;
}

