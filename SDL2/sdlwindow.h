#ifndef SDLWINDOW_H
#define SDLWINDOW_H


#include <SDL2/SDL.h>
#include "sdleventdelegate.h"


class SDLWindow : public SDLEventDelegate
{
    public:

                                                SDLWindow();
                                                ~SDLWindow();

        SDL_Window*                             GetRawSdlWindow();


    protected:

        SDL_Window*                             mRawSdlWindow;


};


#endif // SDLWINDOW_H
