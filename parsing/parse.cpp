/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:40:23 by zait-sli          #+#    #+#             */
/*   Updated: 2022/12/30 12:24:25 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

// Constructors
parse::parse()
{
	std::cout << "\e[0;33mDefault Constructor called of parse\e[0m" << std::endl;
}

parse::parse(const parse &copy)
{
	(void) copy;
	std::cout << "\e[0;33mCopy Constructor called of parse\e[0m" << std::endl;
}


void parse::remove_comments()
{
	int i = 0;
	while (this->value[i])
	{
		if (this->value[i] == '#')
		{
			int j = i;
			while (this->value[j] != '\n' && this->value[j] != '\0')
				j++;
			if(this->value[j] == '\0')
				return ;
			else
				this->value.erase (i , j - i );
			i = 0;
		}
		i++;
	}
}

// Destructor
parse::~parse()
{
	std::cout << "\e[0;31mDestructor called of parse\e[0m" << std::endl;
}


// Operators
parse & parse::operator=(const parse &assign)
{
	(void) assign;
	return *this;
}

void parse::readFile()
{

}
