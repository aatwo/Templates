#include "logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>


Logger* Logger::sInstance = nullptr;


bool Logger::Init()
{
    if( sInstance )
    {
        std::cout << "Logger already initialised..." << std::endl;
        return false;
    }

    sInstance = new Logger;
    bool ret = sInstance->pri_Init();

    if( !ret )
    {
        delete sInstance;
        sInstance = nullptr;
    }

    return ret;
}

void Logger::AddLog( std::string entry, std::string filename, int line )
{
    if( !sInstance )
    {
        std::cout << "Cannot add log entry as the logger has not been initialised yet..." << std::endl;
        return;
    }

    return sInstance->pri_AddLog( entry, filename, line );
}

void Logger::AddLog( std::string entry, std::string info, std::string filename, int line )
{
    if( !sInstance )
    {
        std::cout << "Cannot add log entry as the logger has not been initialised yet..." << std::endl;
        return;
    }

    return sInstance->pri_AddLog( entry, info, filename, line );
}

void Logger::AddLog( std::string entry, int value, std::string filename, int line )
{
    if( !sInstance )
    {
        std::cout << "Cannot add log entry as the logger has not been initialised yet..." << std::endl;
        return;
    }

    return sInstance->pri_AddLog( entry, value, filename, line );
}

void Logger::CleanUp()
{
    if( sInstance )
    {
        sInstance->pri_CleanUp();
        delete sInstance;
        sInstance = nullptr;
    }
}

Logger::Logger()
{
    sInstance = this;
}

bool Logger::pri_Init()
{
    // TODO - log to file
    return true;
}

void Logger::pri_AddLog( std::string entry, std::string filename, int line )
{
    std::string timestamp, entrySeparator, fileInfo;
    pri_GenerateLogTimestamp( timestamp );
    pri_GenerateEntrySeparator( entrySeparator );
    pri_GenerateFileInfo( fileInfo, filename, line );

    std::cout << timestamp << ": " << entry << " (" << fileInfo << ")" << entrySeparator;
}

void Logger::pri_AddLog( std::string entry, std::string info, std::string filename, int line )
{
    std::string timestamp, entrySeparator, fileInfo;
    pri_GenerateLogTimestamp( timestamp );
    pri_GenerateEntrySeparator( entrySeparator );
    pri_GenerateFileInfo( fileInfo, filename, line );

    std::cout << timestamp << ": " << entry << " - " << info << " (" << fileInfo << ")" << entrySeparator;
}

void Logger::pri_AddLog( std::string entry, int value, std::string filename, int line )
{
    std::string timestamp, entrySeparator, fileInfo;
    pri_GenerateLogTimestamp( timestamp );
    pri_GenerateEntrySeparator( entrySeparator );
    pri_GenerateFileInfo( fileInfo, filename, line );

    std::cout << timestamp << ": " << entry << " - " << value << " (" << fileInfo << ")" << entrySeparator;
}

void Logger::pri_CleanUp()
{
    // TODO - file cleanup
}

void Logger::pri_GenerateLogTimestamp( std::string& timestamp_OUT )
{
    auto currentTime = std::chrono::system_clock::now();
    auto convertedCurrentTime = std::chrono::system_clock::to_time_t( currentTime );

    std::stringstream ss;
    ss << std::put_time( std::localtime( &convertedCurrentTime ), "%X" );
    timestamp_OUT = ss.str();
}

void Logger::pri_GenerateEntrySeparator( std::string& separator_OUT )
{
#ifdef Q_OS_WIN
    separator_OUT = "\r\n";
#else
    separator_OUT = "\n";
#endif
}

void Logger::pri_GenerateFileInfo( std::string& fileInfo_OUT, std::string& file, int line )
{
    std::string lineString;
    {
        std::stringstream ss;
        ss << line;
        lineString = ss.str();
    }

    fileInfo_OUT = file + std::string( " at line " ) + lineString;
}
