/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:40:26 by zait-sli          #+#    #+#             */
/*   Updated: 2022/12/30 12:24:16 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
