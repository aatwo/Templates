#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include "sdlwindow.h"
#include "logger.h"


class MainWindow : public SDLWindow
{
    public:

                                                MainWindow();
                                                ~MainWindow();

        virtual void                            ResizeEvent( int newWidth, int newHeight ) override;
        virtual void                            KeyDownEvent( SDL_KeyboardEvent* event ) override;
        virtual void                            KeyUpEvent( SDL_KeyboardEvent* event ) override;
        virtual void                            MouseButtonDownEvent( SDL_MouseButtonEvent* event ) override;
        virtual void                            MouseButtonUpEvent( SDL_MouseButtonEvent* event ) override;
        virtual void                            MouseMoveEvent( SDL_MouseMotionEvent* event ) override;
        virtual void                            MouseWheelEvent( SDL_MouseWheelEvent* event ) override;
        virtual void                            ControllerAddedEvent( int controllerID, SDL_ControllerDeviceEvent* event ) override;
        virtual void                            ControllerRemovedEvent( int controllerID, SDL_ControllerDeviceEvent* event ) override;
        virtual void                            ControllerAxisMotionEvent( int controllerID, SDL_ControllerAxisEvent* event ) override;
        virtual void                            ControllerButtonDownEvent( int controllerID, SDL_ControllerButtonEvent* event ) override;
        virtual void                            ControllerButtonUpEvent( int controllerID, SDL_ControllerButtonEvent* event ) override;



    private:

        SDL_Surface*                            pri_LoadSurface( std::string path );


        SDL_Surface*                            mImageSurface;
        Mix_Music*                              mBackgroundMusic;
        Mix_Chunk*                              mSoundEffect;


};


#endif // MAINWINDOW_H
