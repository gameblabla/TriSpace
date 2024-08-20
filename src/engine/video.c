#include "video.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#define CHAD_API_IMPL
//#include "zbuffer.h"
#include "gltext.h"
#include "GL/gl.h"

SDL_Surface* screen, *text_surface;
TTF_Font * font;
//ZBuffer* frameBuffer = NULL;

mat4 mPerspective;
mat4 mOrtho;

mat4 ortho(float b, float t, float l, float r, float n, float f)
{ 
    mat4 matrix;
    matrix.d[0] = 2 / (r - l); 
    matrix.d[1] = 0; 
    matrix.d[2] = 0; 
    matrix.d[3] = 0; 
 
    matrix.d[4] = 0; 
    matrix.d[5] = 2 / (t - b); 
    matrix.d[6] = 0; 
    matrix.d[7] = 0; 
 
    matrix.d[8] = 0; 
    matrix.d[9] = 0; 
    matrix.d[10] = -2 / (f - n); 
    matrix.d[11] = 0; 
 
    matrix.d[12] = -(r + l) / (r - l); 
    matrix.d[13] = -(t + b) / (t - b); 
    matrix.d[14] = -(f + n) / (f - n); 
    matrix.d[15] = 1;
    
    return matrix;
}

void initVideo(vec4 clearColor, vec4 viewport, float fov, float near, float far)
{
	SDL_Init(SDL_INIT_VIDEO);
	
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 6 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	
    screen = SDL_SetVideoMode(WINX, WINY, 16, SDL_HWSURFACE | SDL_OPENGL);
    
	TTF_Init();
	font = TTF_OpenFont("font.ttf", 16);
	if (!font)
	{
		printf("FONT ERROR %s\n", SDL_GetError());
		exit(0);
	}
	
	SDL_ShowCursor(SDL_DISABLE);
    //Initialize TinyGL
	//frameBuffer = ZB_open(WINX, WINY, ZB_MODE_5R6G5B, 0);
	//glInit(frameBuffer);
	
	glShadeModel(GL_FLAT);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(clearColor.d[0], clearColor.d[1], clearColor.d[2], clearColor.d[3]);
	glClearDepth(1.0f);
    glViewport(viewport.d[0], viewport.d[1], viewport.d[2], viewport.d[3]);
	glTextSize(GL_TEXT_SIZE8x8);
	glEnable(GL_TEXTURE_2D);
	
	//Initialize projection matrices
    mPerspective = perspective(fov, viewport.d[2] / viewport.d[3], near, far);
	mOrtho = ortho(0, WINX, 0, WINY, -32, 0);
}

extern void Final_text();

void clearFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void flipFrame()
{
    SDL_GL_SwapBuffers( );
    

	//SDL_Flip(screen);
}

void quitVideo()
{
	//ZB_close(frameBuffer);
	//glClose();
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_FreeSurface(screen);
    SDL_Quit();
}

void setOrtho()
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(mOrtho.d);
	glMatrixMode(GL_MODELVIEW);
}

void setPerspective()
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(mPerspective.d);
	glMatrixMode(GL_MODELVIEW);
}

void drawFPS(uint16_t fps)
{
    char buffer[12];
	sprintf(buffer, "FPS: %i", fps);
	glDrawText(buffer, 2, 2, 0xFFFFFF);
}
