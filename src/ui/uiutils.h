#ifndef _UI_UTILS_H
#define _UI_UTILS_H

#include "../engine/video.h"

//UI Base Height
#define UIBH 10
//UI Top Height
#define UITH 11
//UI Popup Height
#define UIPH 12
//UI Popup Top Height
#define UIPTH 13

//Macro for centering text
//X is the size of the text in characters
//X * 8 / 2 = X * 4
#define CENTER(X) ((WINX / 2) - ((X) * 4))

#define TEXT_WHITE  0xFFFFFF
#define TEXT_DKGREY 0x020202
#define TEXT_GREY   0x707070
#define TEXT_GREEN  0x00FF00

#include "gltext.h"

#endif