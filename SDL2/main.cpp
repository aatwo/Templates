#include <iostream>
#include "sdlapplication.h"
#include "mainwindow.h"
#include "logger.h"

#undef main

int main()
{
    SDLApplication application;

    if( !application.Init() )
    {
        std::cout << "Initialisation failed" << std::endl;
        return -1;
    }

    MainWindow mainWindow;
    if( !mainWindow.GetRawSdlWindow() )
    {
        LOG( "Unable to create the main window" );
        return -2;
    }

    return application.Exec();
}
