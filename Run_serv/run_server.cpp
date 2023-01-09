/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:16:36 by asabbar           #+#    #+#             */
/*   Updated: 2023/01/09 17:39:00 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Webserv.hpp"

void testCnnection (int item)
{
	if(item < 0)
	{
		perror("KO :(\nFailed to connect    : ");
		exit(1);
	}
	return ;
}

void Accept(serv_d &Serv)
{
	struct sockaddr_in address = Serv.address;
	int addrlen = sizeof(address);
	Serv.new_socket = accept(Serv.sock, (sockaddr *)&address, (socklen_t *)&addrlen);
	bzero(Serv.buffer, sizeof(Serv.buffer));
	read(Serv.new_socket, Serv.buffer, sizeof(Serv.buffer));
}


void    run_server(std::vector<serv_d> &servers)
{
    // size_t nmb_socket;
	int option = 1;
    std::vector<serv_d> ::iterator it = servers.begin();

    // nmb_socket = servers.size();
    for (; it < servers.end(); it++)
    {
    	it->address.sin_family = AF_INET;
		it->address.sin_port = htons(atoi(it->listen.c_str()));
		it->address.sin_addr.s_addr = htonl(0);
		it->sock = socket(AF_INET, SOCK_STREAM, 0);
	    testCnnection(it->sock);
	    setsockopt(it->sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(1));
    }
    for (it = servers.begin(); it < servers.end(); it++)
	{
    it->connection = bind(it->sock, (struct sockaddr *)&it->address, sizeof(it->address));
	    testCnnection(it->connection);
	}
    for (it = servers.begin(); it < servers.end(); it++)
	{
    	it->listening = listen(it->sock,it->backlog);
	    testCnnection(it->listening);
	}



	struct pollfd fds[servers.size()];
	int j = 0;
    for (it = servers.begin(); it < servers.end(); it++)
	{
		fds[j].fd =it->sock;
		fds[j].events = POLLIN;
		j++;
	}

	
	while(1)
	{
		std::cout << "============== WAITING ==============\n";
		int ret = poll(fds, servers.size(), -1);
		puts("poll");
		if (ret == -1) {
			std::cout << "error :" << std::endl; 
		} else if (ret > 0) {
			for (size_t i = 0; i < servers.size(); i++)
			{
				if (fds[i].revents == POLLIN) {
					it = servers.begin();
					for (size_t t = 0; t < i; t++)
						it++;
					Accept((*it));
					std::cout << "{{{\n\n"<<it->buffer <<  " \n}\n";
				}
			}
			
		}
		std::cout <<"============== DONE ==============\n";
	}
	
}