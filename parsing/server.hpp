/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:40:30 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/27 15:25:10 by asabbar          ###   ########.fr       */
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

class client_d
{
public:
	int acceptFd;
	int socketFd;
	bool endSend;
	bool isAccept;
	bool endRead;
	std::string request;
	char buffer[500000];
	unsigned long lenRead;
	unsigned long lenCont;
};

class serv_d
{
public:
	int sock;
	int backlog;
	bool is_accept;
	int listening;
	int connection;
	std::string root;
	std::string host;
	std::string listen;
	size_t max_body_size;
	std::string server_name;
	struct sockaddr_in address;
	std::map<std::string, std::map<std::string, std::vector<std::string> > > locations;

	serv_d();
	void set_sock(int sock);
	void set_backlog(int backlog);
	void set_listening(int listening);
	void set_connection(int connection);
	void set_root(std::string root);
	void set_host(std::string host);
	void set_listen(std::string listen);
	void set_max_body_size(size_t max_body_size);
	void set_server_name(std::string server_name);
	void set_address(struct sockaddr_in address);
	~serv_d();
	serv_d &operator=(const serv_d &assign);
};

#endif
