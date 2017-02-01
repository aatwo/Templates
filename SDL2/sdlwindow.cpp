#include "sdlwindow.h"
#include "sdlapplication.h"


SDLWindow::SDLWindow()
{
    mRawSdlWindow = SDLApplication::Instance()->CreateRawSdlWindow();
    if( mRawSdlWindow )
        SDLApplication::Instance()->RegisterSdlWindow( this, mRawSdlWindow );
}

SDLWindow::~SDLWindow()
{
    if( mRawSdlWindow )
    {
        SDLApplication::Instance()->UnregisterSdlWindow( this, mRawSdlWindow );
        SDL_DestroyWindow( mRawSdlWindow );
    }
}

SDL_Window* SDLWindow::GetRawSdlWindow()
{
    return mRawSdlWindow;
}
