#include <stdint.h>

#define GL_TEXT_SIZE8x8 0
#define GL_TEXT_SIZE16x16 1

extern void glDrawText(const uint8_t *text, int x, int y, unsigned int p);
extern void glTextSize(int mode);
extern void glDeleteList(unsigned int list);;
extern void glPlotPixel(int x, int y, unsigned int pixel);