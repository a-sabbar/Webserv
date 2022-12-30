#include "server.hpp"

// Constructors
server::server()
{
	std::cout << "\e[0;33mDefault Constructor called of server\e[0m" << std::endl;
}

server::server(const server &copy)
{
	(void) copy;
	std::cout << "\e[0;33mCopy Constructor called of server\e[0m" << std::endl;
}


// Destructor
server::~server()
{
	std::cout << "\e[0;31mDestructor called of server\e[0m" << std::endl;
}


// Operators
server & server::operator=(const server &assign)
{
	(void) assign;
	return *this;
}

