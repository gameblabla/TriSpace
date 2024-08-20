#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL/SDL.h>
#include "font_drawing.h"
#include "font_menudata.h"

extern SDL_Surface* text_surface;

#define setPixel(buffer, x,y,c) *((uint16_t* restrict)buffer + ((x) + (y) * (text_surface->w * 2))) = c;

static void drawChar(uint16_t* restrict buffer, int32_t *x, int32_t *y, int32_t margin, char ch, uint32_t fc, uint32_t olc)
{
	int32_t i, j;
	uint8_t *charSprite;
	if (ch == '\n')
	{
		*x = margin;
		*y += 8;
	}
	else if(*y < text_surface->h-1)
	{
		charSprite = ch * 8 + n2DLib_font;
		// Draw charSprite as monochrome 8*8 image using given color
		for(i = 0; i < 8; i++)
		{
			for(j = 7; j >= 0; j--)
			{
				if((charSprite[i] >> j) & 1)
				{
					setPixel(buffer, *x + (7 - j), *y + i, fc)
				}
				/*else if(isOutlinePixel(charSprite, 7 - j, i))
				{
					setPixel(buffer, *x + (7 - j), *y + i, olc)
				}*/
			}
		}
		*x += 8;
	}
}

static void drawString(uint16_t* restrict buffer, int32_t *x, int32_t *y, int32_t _x, const char *str, uint32_t fc, uint32_t olc)
{
	unsigned long i, max = strlen(str) + 1;
	for(i = 0; i < max; i++)
		drawChar(buffer, x, y, _x, str[i], fc, olc);
}

void print_string(const char *s,const uint32_t fg_color, const uint32_t bg_color, int32_t x, int32_t y, uint16_t* restrict buffer) 
{
	drawString(buffer, &x, &y, 0, s, fg_color, bg_color);
}
