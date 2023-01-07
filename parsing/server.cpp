/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:40:26 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/07 10:44:27 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

// Constructors
server::server()
{
}

server::server(const server &copy)
{
	(void) copy;
}


// Destructor
server::~server()
{
}


// Operators
server & server::operator=(const server &assign)
{
	(void) assign;
	return *this;
}
