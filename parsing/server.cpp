/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:40:26 by zait-sli          #+#    #+#             */
/*   Updated: 2023/02/16 18:43:57 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

// Constructors
serv_d::serv_d() : backlog(SOMAXCONN)
{
}




// void serv_d::set_sock(int sock)
// {
// 	this->sock = sock;
// }


void serv_d::set_backlog(int backlog)
{
	this->backlog =backlog;
}


void serv_d::set_listening(int listening)
{
	this->listen = listening;
}


void serv_d::set_connection(int connection)
{
	this->connection = connection;
}



void serv_d::set_root(std::string root)
{
	this->root = root;
}


void serv_d::set_host(std::string host)
{
	this->host =host;
}


void serv_d::set_listen(std::string listen)
{
	this->listen = listen;
}




void serv_d::set_max_body_size(size_t max_body_size)
{
	this->max_body_size = max_body_size;
}


void serv_d::set_server_name(std::string server_name)
{
	this->server_name = server_name;
}


// void serv_d::set_address(struct sockaddr_in address)
// {
// 	this->address = address;
// }




// // Destructor
serv_d::~serv_d()
{
}


// Operators
serv_d & serv_d::operator=(const serv_d &assign)
{
	(void) assign;
	return *this;
}
