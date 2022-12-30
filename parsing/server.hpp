#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>

class server
{
	public:
		std::string server_name;
		std::string host;
		std::string listen; // momkin tkoun vector 
		size_t max_body_size; //always with B
		std::string root;
		//every variable above needs to be pasred and checked for errors before getting stored;

		// Constructors
		server();
		server(const server &copy);
		
		// Destructor
		~server();
		
		// Operators
		server & operator=(const server &assign);
		
};

#endif