#include "sdlapplication.h"
#include <cassert>
#include "logger.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


SDLApplication* SDLApplication::sInstance = nullptr;


SDLApplication::SDLApplication()
{
    assert( !sInstance ); // There can only be one...

    sInstance           = this;
    mApplicationRunning = true;
    mFocusedRawWindow   = nullptr;
    mFocusedWindow      = nullptr;
}

SDLApplication::~SDLApplication()
{
    CleanUp();
}

SDLApplication* SDLApplication::Instance()
{
    return sInstance;
}

bool SDLApplication::Init()
{
    if( !Logger::Init() )
        return false;

    if( !pri_InitSDL() )
        return false;

    return true;
}

int SDLApplication::Exec()
{
    while( mApplicationRunning )
    {
        pri_ProcessSdlEventQueue();
    }

    return 0;
}

void SDLApplication::CleanUp()
{
    pri_CleanUpSDL();
    Logger::CleanUp();
}

SDL_Window* SDLApplication::CreateRawSdlWindow()
{
    int initialScreenWidth  = 640;
    int initialScreenHeight = 480;

    SDL_Window* window = SDL_CreateWindow( global::applicationName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, initialScreenWidth, initialScreenHeight, SDL_WINDOW_SHOWN );

    if( window )
        mSdlWindows.push_back( window );
    else
        LOG_INFO( "Unable to create SDL window", SDL_GetError() );

    return window;
}

void SDLApplication::RegisterSdlWindow( SDLWindow* window, SDL_Window* rawWindow )
{
    mRawWindowToWrapperMap.insert( std::make_pair( rawWindow, window ) );
}

void SDLApplication::UnregisterSdlWindow( SDLWindow* window, SDL_Window* rawWindow )
{
    (void)( window );

    for( auto it = mSdlWindows.begin(); it != mSdlWindows.end(); ++it )
    {
        if( *it != rawWindow )
            continue;

        mSdlWindows.erase( it );
        break;
    }

    if( mFocusedRawWindow == rawWindow )
    {
        mFocusedWindow      = nullptr;
        mFocusedRawWindow   = nullptr;
    }
}

bool SDLApplication::pri_InitSDL()
{
    LOG( "Initialising SDL" );

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        LOG_INFO( "Unable to initialise SDL", SDL_GetError() );
        return false;
    }

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        LOG_INFO( "Unable to initialise SDL image", IMG_GetError() );
        return false;
    }

     //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        LOG_INFO( "Unable to initialise SDL mixer", Mix_GetError() );
        return false;
    }

    return true;
}

void SDLApplication::pri_CleanUpSDL()
{
    LOG( "Cleaning up SDL" );

    for( SDL_Window* window : mSdlWindows )
        SDL_DestroyWindow( window );

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool SDLApplication::pri_GetWindowPairForId( Uint32 windowID, SDL_Window*& rawWindow_OUT, SDLWindow*& window_OUT )
{
    window_OUT      = nullptr;
    rawWindow_OUT   = SDL_GetWindowFromID( windowID );

    if( !rawWindow_OUT )
        return false;

    window_OUT = mRawWindowToWrapperMap[ rawWindow_OUT ];
    return ( window_OUT != nullptr );
}

void SDLApplication::pri_ProcessSdlEventQueue()
{
    SDL_Event event;
    while( SDL_PollEvent( &event ) != 0 )
    {

        switch( event.type )
        {

            case SDL_QUIT:
            {
                pri_Quit();
                break;
            }

            case SDL_KEYDOWN:
            case SDL_KEYUP:
            {
                pri_HandleKeyboardEvent( &event.key );
                break;
            }

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                pri_HandleMouseButtonEvent( &event.button );
                break;
            }

            case SDL_MOUSEMOTION:
            {
                pri_HandleMouseMotionEvent( &event.motion );
                break;
            }

            case SDL_MOUSEWHEEL:
            {
                pri_HandleMouseWheelEvent( &event.wheel );
                break;
            }

            case SDL_WINDOWEVENT:
            {
                pri_HandleWindowEvent( &event.window );
                break;
            }

            case SDL_CONTROLLERDEVICEADDED:
            {
                pri_HandleControllerAdded( &event.cdevice );
                break;
            }

            case SDL_CONTROLLERDEVICEREMOVED:
            {
                pri_HandleControllerRemoved( &event.cdevice );
                break;
            }

            case SDL_CONTROLLERAXISMOTION:
            {
                pri_HandleControllerAxisMotion( &event.caxis );
                break;
            }

            case SDL_CONTROLLERBUTTONDOWN:
            case SDL_CONTROLLERBUTTONUP:
            {
                pri_HandleControllerButtonDown( &event.cbutton );
                break;
            }


            // TODO - handle other event types...
        }
    }
}

void SDLApplication::pri_Quit()
{
    mApplicationRunning = false;
}

void SDLApplication::pri_HandleWindowEvent( SDL_WindowEvent* event )
{
    SDL_Window* rawWindow;
    SDLWindow* window;
    pri_GetWindowPairForId( event->windowID, rawWindow, window );

    if( !rawWindow )
        return;

    switch( event->event )
    {

        case SDL_WINDOWEVENT_FOCUS_GAINED:
        {
            mFocusedRawWindow   = rawWindow;
            mFocusedWindow      = mRawWindowToWrapperMap[ rawWindow ];

            if( mFocusedWindow )
                mFocusedWindow->FocusInEvent();

            break;
        }

        case SDL_WINDOWEVENT_FOCUS_LOST:
        {
            if( mFocusedRawWindow == rawWindow )
            {
                if( mFocusedWindow )
                    mFocusedWindow->FocusOutEvent();

                mFocusedWindow      = nullptr;
                mFocusedRawWindow   = nullptr;
            }

            break;
        }

        case SDL_WINDOWEVENT_SIZE_CHANGED:
        {
            if( window )
                window->ResizeEvent( event->data1, event->data2 );

            break;
        }

        case SDL_WINDOWEVENT_SHOWN:
        {
            if( window )
                window->ShowEvent();

            break;
        }

        case SDL_WINDOWEVENT_HIDDEN:
        {
            if( window )
                window->HideEvent();

            break;
        }

        case SDL_WINDOWEVENT_ENTER:
        {
            if( window )
                window->EnterEvent();

            break;
        }

        case SDL_WINDOWEVENT_LEAVE:
        {
            if( window )
                window->LeaveEvent();

            break;
        }

        case SDL_WINDOWEVENT_MOVED:
        {
            if( window )
                window->MoveEvent( event->data1, event->data2 );

            break;
        }

        case SDL_WINDOWEVENT_MINIMIZED:
        {
            if( window )
                window->MinimiseEvent();

            break;
        }

        case SDL_WINDOWEVENT_MAXIMIZED:
        {
            if( window )
                window->MaximiseEvent();

            break;
        }

        case SDL_WINDOWEVENT_RESTORED:
        {
            if( window )
                window->RestoreEvent();

            break;
        }

        default: {}

    }

}

void SDLApplication::pri_HandleKeyboardEvent( SDL_KeyboardEvent* event )
{
    SDL_Window* rawWindow;
    SDLWindow* window;

    if( !pri_GetWindowPairForId( event->windowID, rawWindow, window ) )
        return;

    switch( event->type )
    {
        case SDL_KEYDOWN:
        {
            window->KeyDownEvent( event );
            break;
        }

        case SDL_KEYUP:
        {
            window->KeyUpEvent( event );
            break;
        }

        default: {}
    }
}

void SDLApplication::pri_HandleMouseButtonEvent( SDL_MouseButtonEvent* event )
{
    SDL_Window* rawWindow;
    SDLWindow* window;

    if( !pri_GetWindowPairForId( event->windowID, rawWindow, window ) )
        return;

    switch( event->type )
    {
        case SDL_MOUSEBUTTONDOWN:
        {
            window->MouseButtonDownEvent( event );
            break;
        }

        case SDL_MOUSEBUTTONUP:
        {
            window->MouseButtonUpEvent( event );
            break;
        }

        default: {}
    }
}

void SDLApplication::pri_HandleMouseMotionEvent( SDL_MouseMotionEvent* event )
{
    SDL_Window* rawWindow;
    SDLWindow* window;

    if( !pri_GetWindowPairForId( event->windowID, rawWindow, window ) )
        return;

    window->MouseMoveEvent( event );
}

void SDLApplication::pri_HandleMouseWheelEvent( SDL_MouseWheelEvent* event )
{
    SDL_Window* rawWindow;
    SDLWindow* window;

    if( !pri_GetWindowPairForId( event->windowID, rawWindow, window ) )
        return;

    window->MouseWheelEvent( event );
}

void SDLApplication::pri_HandleControllerAdded( SDL_ControllerDeviceEvent* event )
{
    int controllerIndex = event->which;
    if( !SDL_IsGameController( controllerIndex ) )
        return;

    SDL_GameController* controller = SDL_GameControllerOpen( controllerIndex );
    if( !controller )
    {
        LOG_INFO( "Failed to open controller", SDL_GetError() );
        return;
    }

    SDL_Joystick* joystick = SDL_GameControllerGetJoystick( controller );
    if( !joystick )
    {
        LOG( "Unable to retrieve the joystick object for the controller" );
        return;
    }

    int controllerID = SDL_JoystickInstanceID( joystick );
    mControllerIdToControllerMap.insert( std::make_pair( controllerID, controller ) );

    if( mFocusedWindow )
        mFocusedWindow->ControllerAddedEvent( controllerID, event );

    LOG_VALUE( "Controller detected... ID", controllerID );
}

void SDLApplication::pri_HandleControllerRemoved( SDL_ControllerDeviceEvent* event )
{
    int controllerID = event->which;

    auto controllerIterator = mControllerIdToControllerMap.find( controllerID );

    if( controllerIterator == mControllerIdToControllerMap.end() )
        return;

    SDL_GameController* controller = controllerIterator->second;
    SDL_GameControllerClose( controller );

    if( mFocusedWindow )
        mFocusedWindow->ControllerRemovedEvent( controllerID, event );

    LOG_VALUE( "Controller disconnected... ID", controllerID );
}

void SDLApplication::pri_HandleControllerAxisMotion( SDL_ControllerAxisEvent* event )
{
    if( !mFocusedWindow )
        return;

    mFocusedWindow->ControllerAxisMotionEvent( event->which, event );
}

void SDLApplication::pri_HandleControllerButtonDown( SDL_ControllerButtonEvent* event )
{
    if( !mFocusedWindow )
        return;

    switch( event->type )
    {
        case SDL_CONTROLLERBUTTONDOWN:
        {
            mFocusedWindow->ControllerButtonDownEvent( event->which, event );
            break;
        }

        case SDL_CONTROLLERBUTTONUP:
        {
            mFocusedWindow->ControllerButtonUpEvent( event->which, event );
            break;
        }

        default: {}
    }
}
