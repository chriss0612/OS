#ifndef __TERMINAL_H
#define __TERMINAL_H

#include "types.h"

enum vga_color {
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

void TsetPos(uint8_t, uint8_t);
void TsetColor(vga_color b,vga_color f);
void TputC(char);
void TputS(const char*);
void TgetPos(uint8_t*x,uint8_t *y);
char TgetChar(uint8_t x,uint8_t y);
char TgetCol(uint8_t x,uint8_t y);
void TswCol(uint8_t x,uint8_t y);
#endif
