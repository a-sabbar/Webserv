/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:40:30 by zait-sli          #+#    #+#             */
/*   Updated: 2023/03/12 12:37:18 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Webserv.hpp"
#include "parse.hpp"
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
	   
#define iteratorServer std::vector<serv_d> ::iterator
class client_d
{
	public:
		int 			acceptFd;
		int 			socketFd;
		bool 			endRead;
		std::string 	request;
		char 			buffer[500000];
		unsigned long 	lenRead;
		unsigned long 	lenCont;
		std::string 	Respons;
		size_t			ResponsLength;
		bool			Con;		// 0 close, 1 keep allive
		long long int 	lastRead;
		ssize_t 		sendLen;
		bool 			endSend;
};

class serv_d
{
	public:
		std::vector<int>																sock;
		int 																			backlog;
		std::string 																	root;
		std::string 																	host;
		std::string 																	listen;
		std::vector<std::string> 														listens;
		std::vector<serv_d> 															DuplicatePort;
		size_t 																			max_body_size;
		std::vector<std::string>														server_name;
		std::vector<class Location>														Loc;
		std::vector<std::string> 														errorPage;
		std::map<std::string,std::string> 												pageErrorpageError;
		std::map<std::string, std::map<std::string, std::vector<std::string> > >		locations;
	
		serv_d();
		~serv_d();
		serv_d &operator=(const serv_d &assign);
};

#endif
