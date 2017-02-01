#ifndef SDLAPPLICATION_H
#define SDLAPPLICATION_H


#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include "global.h"
#include "sdlwindow.h"


class SDLApplication
{
    public:

                                                SDLApplication();
                                                ~SDLApplication();

        static SDLApplication*                  Instance();

        bool                                    Init();
        int                                     Exec();
        void                                    CleanUp();
        SDL_Window*                             CreateRawSdlWindow();
        void                                    RegisterSdlWindow( SDLWindow* window, SDL_Window* rawWindow );
        void                                    UnregisterSdlWindow( SDLWindow* window, SDL_Window* rawWindow );


    private:

        bool                                    pri_InitSDL();
        void                                    pri_CleanUpSDL();
        bool                                    pri_GetWindowPairForId( Uint32 windowID, SDL_Window*& rawWindow_OUT, SDLWindow*& window_OUT );
        void                                    pri_ProcessSdlEventQueue();
        void                                    pri_Quit();

        void                                    pri_HandleWindowEvent( SDL_WindowEvent* event );
        void                                    pri_HandleKeyboardEvent( SDL_KeyboardEvent* event );
        void                                    pri_HandleMouseButtonEvent( SDL_MouseButtonEvent* event );
        void                                    pri_HandleMouseMotionEvent( SDL_MouseMotionEvent* event );
        void                                    pri_HandleMouseWheelEvent( SDL_MouseWheelEvent* event );

        void                                    pri_HandleControllerAdded( SDL_ControllerDeviceEvent* event );
        void                                    pri_HandleControllerRemoved( SDL_ControllerDeviceEvent* event );
        void                                    pri_HandleControllerAxisMotion( SDL_ControllerAxisEvent* event );
        void                                    pri_HandleControllerButtonDown( SDL_ControllerButtonEvent* event );


        bool                                    mApplicationRunning;
        std::map<int, SDL_GameController*>      mControllerIdToControllerMap;
        std::map<SDL_Window*, SDLWindow*>       mRawWindowToWrapperMap;
        std::vector<SDL_Window*>                mSdlWindows;
        SDL_Window*                             mFocusedRawWindow;
        SDLWindow*                              mFocusedWindow;
        static SDLApplication*                  sInstance;



}; // SDLApplication


#endif // SDLAPPLICATION_H
