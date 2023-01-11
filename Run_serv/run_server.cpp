/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:16:36 by asabbar           #+#    #+#             */
/*   Updated: 2023/01/11 21:34:29 by asabbar          ###   ########.fr       */
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

struct pollfd  Accept_read(std::vector<serv_d> &servers, int i)
{
	struct sockaddr_in address = servers.at(i).address;
	int addrlen = sizeof(address);
	struct pollfd temp;

	servers.at(i).is_accept = true;
	printf("fd sock:  %d\n", servers.at(i).sock);
	temp.fd = accept(servers.at(i).sock, (sockaddr *)&address, (socklen_t *)&addrlen);
	temp.events = POLLIN | POLLOUT; 
	temp.revents = 0;
	return(temp);
}

void    run_server(std::vector<serv_d> &servers)
{
	int option = 1;
    std::vector<serv_d> ::iterator it = servers.begin();

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



	std::vector <struct pollfd> fds;
	int nfds = 0;
    for (it = servers.begin(); it < servers.end(); it++)
	{
		struct pollfd temp;
		temp.fd = it->sock;
		temp.events = POLLIN | POLLOUT; 
		temp.revents = 0;
		nfds++;
		fds.push_back(temp);
	}
	while(1)
	{
		std::cout << "==============WAITING ==============\n";
		int ret = poll(&fds[0], fds.size(), -1);
		if (ret == -1)
		{
			std::cout << "error :" << std::endl;
			break;
		}
		else if (ret > 0)
		{
			// printf("fd :  %d, revent : %d\n", fds[1].fd,fds[1].revents);
			for (size_t i = 0; i < fds.size(); i++)
			{
					if(i < servers.size() && !servers.at(i).is_accept && fds.at(i).revents)
					{
						it = servers.begin();
						for (size_t t = 0; t < i; t++)
							it++;
						puts(" accept");
						fds.push_back(Accept_read(servers, i));
					}
					if (fds.at(i).revents & POLLIN)
					{
						it = servers.begin();
						for (size_t t = 0; t < i; t++)
							it++;
						puts("read");
						bzero(it->buffer, sizeof(it->buffer));
						 recv(fds.at(i).fd, it->buffer, sizeof(it->buffer), 0);
						it->request.append(it->buffer);
						if(it->request.find("\r\n\r\n") != std::string::npos){
							it->f_read = true;
						}
					}
					if (fds.at(i).revents & POLLOUT) {
						it = servers.begin();
						for (size_t t = 0; t < i; t++)
							it++;
						if(it->f_read)
						{
						std::cout << it->sock << " request :   " << it->request << std::endl ;
						// sleep(1);
						printf("---->>> out\n");
						it = servers.begin();
						for (size_t t = 0; t < i; t++)
							it++;
							write(fds.at(i).fd, "hello my webser !!\n", 19);
							close(fds.at(i).fd);
						}
						// it->is_accept= false;
					}
					// sleep(1);
			}
		}
		std::cout <<"============== DONE ==============\n";
	}
	
}