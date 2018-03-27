#include <common/terminal.h>


#define VID_MEM 0x0b8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

using namespace mykernel::common;

uint8_t _X=0;
uint8_t _Y=0;
uint8_t _COLOR=0x0F;
const char hex[] = {"0123456789ABCEF"};


void mykernel::common::TsetPos(uint8_t x, uint8_t y)
{
    _X=x;
    _Y=y;
}
void mykernel::common::TsetColor(vga_color f,vga_color b)
{
    _COLOR=b<<4|f;
}

void mykernel::common::TputHex(uint8_t in)
{
    TputC(hex[((in>>4)%16)]);
    TputC(hex[(in%16)]);
}
void mykernel::common::TputHex(uint16_t in)
{
    TputC(hex[((in>>12)%16)]);
    TputC(hex[((in>>8)%16)]);
    TputC(hex[((in>>4)%16)]);
    TputC(hex[(in%16)]);
}
void mykernel::common::TputHex(uint32_t in)
{
    TputC(hex[((in>>28)%16)]);
    TputC(hex[((in>>24)%16)]);
    TputC(hex[((in>>20)%16)]);
    TputC(hex[((in>>16)%16)]);
    TputC(hex[((in>>12)%16)]);
    TputC(hex[((in>>8)%16)]);
    TputC(hex[((in>>4)%16)]);
    TputC(hex[(in%16)]);
}
void mykernel::common::TputHex(uint64_t in)
{
    TputC(hex[((in>>60)%16)]);
    TputC(hex[((in>>56)%16)]);
    TputC(hex[((in>>52)%16)]);
    TputC(hex[((in>>48)%16)]);
    TputC(hex[((in>>44)%16)]);
    TputC(hex[((in>>40)%16)]);
    TputC(hex[((in>>36)%16)]);
    TputC(hex[((in>>32)%16)]);
    TputC(hex[((in>>28)%16)]);
    TputC(hex[((in>>24)%16)]);
    TputC(hex[((in>>20)%16)]);
    TputC(hex[((in>>16)%16)]);
    TputC(hex[((in>>12)%16)]);
    TputC(hex[((in>>8)%16)]);
    TputC(hex[((in>>4)%16)]);
    TputC(hex[(in%16)]);
}
void mykernel::common::TputC(char c)
{
    if(_X<0)
        _X=0;
    if(_Y<0)
        _Y=0;
    if(_X>=VGA_WIDTH)
    {
        _Y++;
        _X=0;
    }
    if(_Y>=VGA_HEIGHT)
    {
        for(int i = 0; i < VGA_WIDTH*VGA_HEIGHT*2; i+=2)
        {
            if(i>=(VGA_HEIGHT-_Y))
            {
                *((char *)(VID_MEM + i)) = ' ';
            }
            else
            {
                *((char *)(VID_MEM + i)) = *((char *)(VID_MEM + i - _Y*VGA_HEIGHT));
            }
        }
        _Y=VGA_HEIGHT;
    }
    if(c == '\n')
    {
        _X=0;
        _Y++;
        if(_Y>=VGA_HEIGHT)
        {
            for(int y = 0; y < VGA_HEIGHT; y++)
            {
                for(int x = 0; x <VGA_WIDTH; x++)
                {
                    if(y>=VGA_HEIGHT-(_Y-VGA_HEIGHT)-1)
                    {
                        *((uint16_t *)(VID_MEM) + (x + y * VGA_WIDTH)) = 0x0F00 | ' ';
                    }
                    else
                    {
                        *((uint16_t *)(VID_MEM) + (x + y * VGA_WIDTH)) = (*((uint16_t *)(VID_MEM) + (x + (y + 1) * VGA_WIDTH)));
                    }
                }
            }
            _Y=VGA_HEIGHT-1;
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
void mykernel::common::TputS(const char* str)
{
    while(*str != '\0')
    {
        TputC(str[0]);
        str++;
    }
}
void mykernel::common::TgetPos(uint8_t*x, uint8_t *y)
{
    *x = _X;
    *y = _Y;
}
char mykernel::common::TgetChar(uint8_t x, uint8_t y)
{
    return (*(((uint16_t*)VID_MEM)+(x + y * VGA_WIDTH)))&0xFF;
}
char mykernel::common::TgetCol(uint8_t x, uint8_t y)
{
    return ((*(((uint16_t*)VID_MEM)+(x + y * VGA_WIDTH)))>>8)&0xFF;
}
void mykernel::common::TswCol(uint8_t x,uint8_t y)
{
    char c = TgetChar(x,y);
    char color = TgetCol(x,y);
    *(((uint16_t*)VID_MEM)+(x + y * VGA_WIDTH)) = ((color>>4)&0xF) << 8 | (color&0xF) << 12 | c;
}

