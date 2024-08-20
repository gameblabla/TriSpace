#include <stdint.h>
#include "font_drawing.h"
#define GL_TEXT_SIZE8x8 0
#define GL_TEXT_SIZE16x16 1

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include "engine/video.h"
#include "font_drawing.h"
extern SDL_Surface* screen, *text_surface;

extern TTF_Font * font;

void glDrawText(const uint8_t *text, int x, int y, unsigned int p)
{
    SDL_Color color;
    // Check if the text pointer is NULL
    if (text == NULL || *text == '\0')
    {
        return;  // Text is NULL or empty
    }
    // Extract RGB components from the 0xXXYYZZ format
    color.r = (p >> 16) & 0xFF;  // Extract red component
    color.g = (p >> 8) & 0xFF;   // Extract green component
    color.b = p & 0xFF;          // Extract blue component
    

    SDL_Surface *sFont = TTF_RenderText_Blended(font, text, color);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, WINX, 0, WINY, -1, 1); 

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);

    // Draw the text
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 1); glVertex2f(x, WINY - y - sFont->h);  // Top-left corner
        glTexCoord2f(1, 1); glVertex2f(x + sFont->w, WINY - y - sFont->h);  // Top-right corner
        glTexCoord2f(1, 0); glVertex2f(x + sFont->w, WINY - y);  // Bottom-right corner
        glTexCoord2f(0, 0); glVertex2f(x, WINY - y);  // Bottom-left corner
    }
    glEnd();

    // Restore the OpenGL stat
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glDeleteTextures(1, &texture);
    SDL_FreeSurface(sFont);
}

void glTextSize(int mode) {
	TTF_CloseFont(font);
	switch(mode)
	{
		default:
			font = TTF_OpenFont("font.ttf", 8);
		break;
		case 1:
			font = TTF_OpenFont("font.ttf", 16);
		break;
	}
	
}

void glDeleteList(unsigned int list)
{
	glDeleteLists(list, 1);
}

void glPlotPixel(int x, int y, unsigned int pixel)
{
    // Set the pixel color
    glColor3ub((pixel >> 16) & 0xFF, (pixel >> 8) & 0xFF, pixel & 0xFF);
    
    // Draw the pixel as a point
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    
    // Ensure the commands are executed immediately
    glFlush();
}