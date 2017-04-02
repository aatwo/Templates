#ifndef _HELLO_WORLD_H_
#define _HELLO_WORLD_H_


#include <string>
#include <iostream>


class HelloWorld {

	public:

												HelloWorld( std::string message );

		void 									print(){ std::cout << mMessage << "\n\n"; };


	private:

		std::string								mMessage;
		


}; // HelloWorld


#endif // _HELLO_WORLD_H_