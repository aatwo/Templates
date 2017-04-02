#include "HelloWorld.h"
#include "Logger/Logger.h"

int main( int argc, char* argv[] ) {


	Logger logger;

	HelloWorld one( "one" );
	HelloWorld two( "two" );
	HelloWorld three( "three" );
	HelloWorld four( "four" );
	HelloWorld five( "five" );

	one.print();
	two.print();
	three.print();
	four.print();
	five.print();

	logger.log( "Finished" );

	return 0;
}