#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "includes/stb_image.h"
#include <SDL_image.h>

void initPNG()
{
    IMG_Init(IMG_INIT_PNG);
}

void quitPNG()
{
    IMG_Quit();
}

SDL_Surface* loadPNG(const char* path)
{
    /*SDL_Surface* loaded = IMG_Load(path);
    if(loaded != NULL)
    {
        SDL_Surface* converted = SDL_DisplayFormatAlpha(loaded);
        SDL_FreeSurface(loaded);
        if(converted != NULL)
        {
            return converted;
        }
    }*/
    printf("PNG loading failed for \"%s\".\n", path);
    return NULL;
}


GLuint loadRGBTexture(unsigned char* path)
{
    int sw = 0, sh = 0, sc = 0;
    unsigned char* sourceData = stbi_load(path, &sw, &sh, &sc, 3);
    
    if (!sourceData) {
        fprintf(stderr, "Failed to load texture: %s\n", path);
        return 0;
    }

    // Convert the image data to include an alpha channel
    unsigned char* dataWithAlpha = (unsigned char*)malloc(sw * sh * 4); // 4 bytes per pixel (RGBA)
    if (!dataWithAlpha) {
        fprintf(stderr, "Failed to allocate memory for alpha texture\n");
        stbi_image_free(sourceData);
        return 0;
    }

    // Pink color to make transparent (255, 0, 255)
    const unsigned char pink[3] = {255, 0, 255};

    // Iterate over each pixel and modify the alpha channel
    for (int y = 0; y < sh; ++y) {
        for (int x = 0; x < sw; ++x) {
            int index = (y * sw + x) * 3; // 3 bytes per pixel
            unsigned char r = sourceData[index];
            unsigned char g = sourceData[index + 1];
            unsigned char b = sourceData[index + 2];
            
            int alphaIndex = (y * sw + x) * 4; // 4 bytes per pixel (RGBA)
            dataWithAlpha[alphaIndex] = r;
            dataWithAlpha[alphaIndex + 1] = g;
            dataWithAlpha[alphaIndex + 2] = b;
            
            // Set alpha to 0 if the color is pink
            if (r == pink[0] && g == pink[1] && b == pink[2]) {
                dataWithAlpha[alphaIndex + 3] = 0; // Fully transparent
            } else {
                dataWithAlpha[alphaIndex + 3] = 255; // Fully opaque
            }
        }
    }

    stbi_image_free(sourceData);

    // Generate and bind the texture
    GLuint t = 0;
    glGenTextures(1, &t);
    glBindTexture(GL_TEXTURE_2D, t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    // Upload the texture with alpha channel
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sw, sh, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataWithAlpha);

    free(dataWithAlpha);
    return t;
}

void deleteRGBTexture(GLuint texture)
{
    glDeleteTextures(1, &texture);
}

void drawTexQuad(float posX, float posY, float sizeX, float sizeY, float z,
					float texX1, float texY1, float texX2, float texY2)
{
    glTexCoord2f(texX1, texY2);
    glVertex3f(posX, posY, z);
    glTexCoord2f(texX2, texY2);
    glVertex3f(posX + sizeX - 1, posY, z);
    glTexCoord2f(texX2, texY1);
    glVertex3f(posX + sizeX - 1, posY + sizeY - 1, z);
    glTexCoord2f(texX1, texY1);
    glVertex3f(posX, posY + sizeY - 1, z);
}