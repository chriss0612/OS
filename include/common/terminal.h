#ifndef __COMMON_TERMINAL_H
#define __COMMON_TERMINAL_H

#include <common/types.h>
namespace mykernel
{
namespace common
{
enum vga_color
{
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

void TsetPos(mykernel::common::uint8_t, mykernel::common::uint8_t);
void TsetColor(vga_color b,vga_color f);
void TputHex(mykernel::common::uint8_t);
void TputHex(mykernel::common::uint16_t);
void TputHex(mykernel::common::uint32_t);
void TputHex(mykernel::common::uint64_t);
void TputC(char);
void TputS(const char*);
void TgetPos(mykernel::common::uint8_t*x, mykernel::common::uint8_t *y);
char TgetChar(mykernel::common::uint8_t x, mykernel::common::uint8_t y);
char TgetCol(mykernel::common::uint8_t x, mykernel::common::uint8_t y);
void TswCol(mykernel::common::uint8_t x, mykernel::common::uint8_t y);


}
}
#endif
