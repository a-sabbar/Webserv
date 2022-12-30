#ifndef PARSE_HPP
# define PARSE_HPP

# include <iostream>
# include <string>

// this calss is the one to parse all data and store it
// so all parsing tools will be defind in this class

class parse
{
	private:
		std::string file;
		// Here we will add a vector a servers;
	public:
		// Constructors
		parse();
		parse(const parse &copy);
		
		// Destructor
		~parse();
		
		// Operators
		parse & operator=(const parse &assign);
		void readFile();
		
};

#endif