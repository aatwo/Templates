#ifndef LOGGER_H
#define LOGGER_H


#include <string>


class Logger
{
    public:


        static bool                             Init();
        static void                             AddLog( std::string entry, std::string filename, int line );
        static void                             AddLog( std::string entry, std::string info, std::string filename, int line );
        static void                             AddLog( std::string entry, int value, std::string filename, int line );
        static void                             ClearLogs();
        static void                             CleanUp();


    private:

                                                Logger();

        bool                                    pri_Init();
        void                                    pri_AddLog( std::string entry, std::string filename, int line );
        void                                    pri_AddLog( std::string entry, std::string info, std::string filename, int line );
        void                                    pri_AddLog( std::string entry, int value, std::string filename, int line );
        void                                    pri_CleanUp();
        void                                    pri_GenerateLogTimestamp( std::string& timestamp_OUT );
        void                                    pri_GenerateEntrySeparator( std::string& separator_OUT );
        void                                    pri_GenerateFileInfo( std::string& fileInfo_OUT, std::string& file, int line );


        static Logger*                          sInstance;
        std::string                             mFilename;


};


#define LOG( entry ) Logger::AddLog( entry, __FILE__, __LINE__ )
#define LOG_INFO( entry, info ) Logger::AddLog( entry, info, __FILE__, __LINE__ )
#define LOG_VALUE( entry, value ) Logger::AddLog( entry, value, __FILE__, __LINE__ )



#endif // LOGGER_H
