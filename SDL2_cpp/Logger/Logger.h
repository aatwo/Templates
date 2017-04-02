#ifndef _LOGGER_H_
#define _LOGGER_H_


#include <string>
#include <iostream>


class Logger {

	public:

												Logger();

		void 									log( std::string message );

		std::string								mLog;


}; // Logger


#endif // _LOGGER_H_