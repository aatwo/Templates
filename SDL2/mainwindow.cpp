#include "mainwindow.h"
#include <chrono>
#include <sstream>
#include <SDL2/SDL_image.h>


MainWindow::MainWindow()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    mImageSurface       = pri_LoadSurface( "Resources/helloWorld.png" );
    mBackgroundMusic    = Mix_LoadMUS( "Resources/music.wav" );
    mSoundEffect        = Mix_LoadWAV( "Resources/soundEffect.wav" );

    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsedS = end - start;
    std::string elapsedMsString;
    {
        std::stringstream ss;
        ss << elapsedS.count() * 1000.0;
        elapsedMsString = ss.str();
    }
    LOG_INFO( "Elapsed time to load wav files (ms)", elapsedMsString );

    SDL_Surface* windowSurface = SDL_GetWindowSurface( mRawSdlWindow );
    SDL_BlitSurface( mImageSurface, NULL, windowSurface, NULL );
    SDL_UpdateWindowSurface( mRawSdlWindow );
}

MainWindow::~MainWindow()
{
    if( mImageSurface )
        SDL_FreeSurface( mImageSurface );

    if( mBackgroundMusic )
        Mix_FreeMusic( mBackgroundMusic );

    if( mSoundEffect )
        Mix_FreeChunk( mSoundEffect );
}

void MainWindow::ResizeEvent( int newWidth, int newHeight )
{
    // TODO
}

void MainWindow::KeyDownEvent( SDL_KeyboardEvent* event )
{
    // TODO

    if( event->keysym.scancode == SDL_SCANCODE_Q )
    {
        if( !mBackgroundMusic )
            return;

        if( Mix_PlayingMusic() )
        {
            if( Mix_PausedMusic() )
            {
                Mix_ResumeMusic();
            }
            else
            {
                Mix_PauseMusic();
            }
        }
        else
        {
            Mix_PlayMusic( mBackgroundMusic, -1 );
        }
    }
    else if( event->keysym.scancode == SDL_SCANCODE_E )
    {
        // Play sound effect
        if( !mSoundEffect )
            return;

        Mix_PlayChannel( -1, mSoundEffect, 0 );
    }
}

void MainWindow::KeyUpEvent( SDL_KeyboardEvent* event )
{
    // TODO
}

void MainWindow::MouseButtonDownEvent( SDL_MouseButtonEvent* event )
{
    // TODO
}

void MainWindow::MouseButtonUpEvent( SDL_MouseButtonEvent* event )
{
    // TODO
}

void MainWindow::MouseMoveEvent( SDL_MouseMotionEvent* event )
{
    // TODO
}

void MainWindow::MouseWheelEvent( SDL_MouseWheelEvent* event )
{
    // TODO
}

void MainWindow::ControllerAddedEvent( int controllerID, SDL_ControllerDeviceEvent* event )
{
    // TODO
}

void MainWindow::ControllerRemovedEvent( int controllerID, SDL_ControllerDeviceEvent* event )
{
    // TODO
}

void MainWindow::ControllerAxisMotionEvent( int controllerID, SDL_ControllerAxisEvent* event )
{
    // TODO
}

void MainWindow::ControllerButtonDownEvent( int controllerID, SDL_ControllerButtonEvent* event )
{
    // TODO
}

void MainWindow::ControllerButtonUpEvent( int controllerID, SDL_ControllerButtonEvent* event )
{
    // TODO
}

SDL_Surface* MainWindow::pri_LoadSurface( std::string path )
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( !loadedSurface )
    {
        LOG_INFO( "Failed to load png", SDL_GetError() );
        return nullptr;
    }

    //Convert surface to screen format
    SDL_Surface* windowSurface = SDL_GetWindowSurface( mRawSdlWindow );
    if( windowSurface )
    {
        optimizedSurface = SDL_ConvertSurface( loadedSurface, windowSurface->format, NULL );
        if( !optimizedSurface )
        {
            LOG_INFO( "Failed to convert image", SDL_GetError() );
        }
    }
    else
    {
        LOG_INFO( "Unable to get window surface", SDL_GetError() );
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );

    return optimizedSurface;
}
