TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    global.cpp \
    logger.cpp \
    mainwindow.cpp \
    sdlapplication.cpp \
    sdleventdelegate.cpp \
    sdlwindow.cpp

HEADERS += \
    global.h \
    logger.h \
    mainwindow.h \
    sdlapplication.h \
    sdleventdelegate.h \
    sdlwindow.h

# SDL
win32: LIBS += -L$$PWD/../SDL_MSVC/SDL2-2.0.4/lib/x64/ -lSDL2
INCLUDEPATH += $$PWD/../SDL_MSVC/SDL2-2.0.4/include
DEPENDPATH += $$PWD/../SDL_MSVC/SDL2-2.0.4/include

# SDL Image
win32: LIBS += -L$$PWD/../SDL_Image/SDL2_image-2.0.1/lib/x64/ -lSDL2_image
INCLUDEPATH += $$PWD/../SDL_Image/SDL2_image-2.0.1/include
DEPENDPATH += $$PWD/../SDL_Image/SDL2_image-2.0.1/include

# SDL Mixer
win32: LIBS += -L$$PWD/../SDL_Mixer/SDL2_mixer-2.0.1/lib/x64/ -lSDL2_mixer
INCLUDEPATH += $$PWD/../SDL_Mixer/SDL2_mixer-2.0.1/include
DEPENDPATH += $$PWD/../SDL_Mixer/SDL2_mixer-2.0.1/include
