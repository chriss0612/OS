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
    if(_X>=VGA_WIDTH)
    {
        _Y++;
        _X=0;
    }
    if(_Y>=VGA_HEIGHT)
    {
        _Y=0;
    }
    if(c == '\n')
    {
        _X=0;
        _Y++;
        if(_Y>=VGA_HEIGHT)
        {
            _Y=0;
        }
        return;
    }
    else if(c == '\r')
    {
        _X=0;
        return;
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
char TgetChar(uint8_t x,uint8_t y)
{
    return (*(((uint16_t*)VID_MEM)+(x + y * VGA_WIDTH)))&0xFF;
}
char TgetCol(uint8_t x,uint8_t y)
{
    return ((*(((uint16_t*)VID_MEM)+(x + y * VGA_WIDTH)))>>8)&0xFF;
}
void TswCol(uint8_t x,uint8_t y)
{
    char c = TgetChar(x,y);
    char color = TgetCol(x,y);
    *(((uint16_t*)VID_MEM)+(x + y * VGA_WIDTH)) = ((color>>4)&0xF) << 8 | (color&0xF) << 12 | c;
}

