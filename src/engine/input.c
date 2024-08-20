#include "input.h"

bool keysLast[NUM_KEYS];
bool keys[NUM_KEYS];

bool handleInput()
{
    bool running = true;

    for(uint8_t i = 0; i < NUM_KEYS; i++)
    {
        keysLast[i] = keys[i];
    }

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            running = false;
        }
        else if(event.type != SDL_KEYDOWN && event.type != SDL_KEYUP)
        {
            continue;
        }

        bool state = false;
        if(event.type == SDL_KEYDOWN)
        {
            state = true;
        }
        switch(event.key.keysym.sym)
        {
            case SDLK_UP:
            {
                keys[B_UP] = state;
                break;
            }
            case SDLK_DOWN:
            {
                keys[B_DOWN] = state;
                break;
            }
            case SDLK_LEFT:
            {
                keys[B_LEFT] = state;
                break;
            }
            case SDLK_RIGHT:
            {
                keys[B_RIGHT] = state;
                break;
            }
            case SDLK_LCTRL:
            {
                keys[B_A] = state;
                break;
            }
            case SDLK_LALT:
            {
                keys[B_B] = state;
                break;
            }
            case SDLK_LSHIFT:
            {
                keys[B_X] = state;
                break;
            }
            case SDLK_SPACE:
            {
                keys[B_Y] = state;
                break;
            }
            case SDLK_TAB:
            {
                keys[B_TL] = state;
                break;
            }
            case SDLK_BACKSPACE:
            {
                keys[B_TR] = state;
                break;
            }
            case SDLK_w:
            {
                keys[B_MENU] = state;
                break;
            }
            case SDLK_o:
            {
                keys[B_SELECT] = state;
                break;
            }
            case SDLK_p:
            {
                keys[B_START] = state;
                break;
            }
            default:
            {
                break;
            }
        }
    }
    return running;
}

bool keyPressed(Key key)
{
    return keys[key];
}

bool keyUp(Key key)
{
    if(keysLast[key] == 1 && keys[key] == 0)
    {
        return 1;
    }
    return 0;
}