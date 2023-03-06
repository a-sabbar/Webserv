/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:16:36 by asabbar           #+#    #+#             */
/*   Updated: 2023/03/04 19:12:19 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Webserv.hpp"
#include <fcntl.h>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

long long int	get_time(void)
{
	struct timeval	current_time;
	long long int	result;

	gettimeofday(&current_time, NULL);
	result = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (result);
}



struct pollfd  Accept_read(std::vector<client_d> &addNewFd, int fd)
{
	struct pollfd temp;
	client_d newFd;
	struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    temp.fd = accept(fd, (struct sockaddr*)&their_addr, &addr_size);
	fcntl(temp.fd , F_SETFL, O_NONBLOCK);
	temp.events = POLLIN | POLLOUT | POLLHUP; 
	temp.revents = 0;

	
	newFd.acceptFd = temp.fd;
	newFd.socketFd = fd;
	newFd.lenRead = 0;
	newFd.endRead = false;
	newFd.sendLen = 0;
	newFd.lastRead = 0;
	newFd.ResponsLength = 0;
	newFd.Con = false;
	newFd.endSend = false;
	newFd.request = "";

	addNewFd.push_back(newFd);
	return(temp);
}


int get_method(std::string request)
{
	std::string check = request.substr(0, 3);
	if(!check.compare("POS"))
		return(2);
	if(!check.compare("GET"))
		return(1);
	if(!check.compare("DEL"))
		return(3);
	return(-1);
}


int get_content_len(std::string request)
{
	int start = (int)request.find("Content-Length: ", 0);
	if(start == -1)
		return(0);
	else
	 start += (int)strlen("Content-Length: ");
	std::string check = request.substr(start, request.find("\r\n", start) - start);
	int endHeader = request.find("\r\n\r\n", start);
	if(endHeader == -1)
		return(atoi(check.c_str()));
	else
		return atoi(check.c_str()) + endHeader;
}

void ft_Trim(std::string &s, const std::string &toTrim = " \t\f\v\n\r")
{
	if (s.find_first_not_of(toTrim) > s.length())
	{
		s.clear();
		return;
	}
	s = s.substr(s.find_first_not_of(toTrim), s.length());
	s = s.substr(0, s.find_last_not_of(toTrim) + 1);
}

std::string  get_host(std::string request)
{
	size_t start = request.find("Host: ", 0);
	if((int)start == -1)
		return("Not Found hhhhh");
	else
	 start +=  strlen("Host: ");
	std::string host = request.substr(start, request.find("\n", start)- start);
	ft_Trim(host);
	return host;
}

void clearPollList(std::vector <struct pollfd> &fds, client_d client, std::vector <client_d> &addNewFd)
{
	if(fds.size())
	{
		std::vector<struct pollfd>::iterator it_poll = fds.begin();
		while(it_poll->fd != client.acceptFd && it_poll != fds.end())
			it_poll++;
		if(it_poll->fd == client.acceptFd)
			fds.erase(it_poll);
	}
	if(addNewFd.size())
	{
		std::vector <client_d>::iterator it_client = addNewFd.begin();
		while(it_client->acceptFd != client.acceptFd && it_client != addNewFd.end() )
			it_client++;
		if(it_client->acceptFd == client.acceptFd)
			addNewFd.erase(it_client);
	}
}


std::string get_path(std::string request)
{
	std::string firstline = request.substr(0, request.find_first_of("\r\n",0));
	
	int firstspace = firstline.find_first_of(" ",0) + 1;
	
	
	int secondspace = firstline.find_last_of(" ", firstline.length());

	return firstline.substr(firstspace, secondspace - firstspace);
};

#include <algorithm>
void    run_server(std::vector<serv_d> &serv_data)
{
	int option = 1;
    std::vector<serv_d> ::iterator it = serv_data.begin();
    for (it = serv_data.begin(); it < serv_data.end(); it++)
	{
		for (std::vector<std::string>::iterator it_listen = it->listens.begin(); it_listen < it->listens.end(); it_listen++)
		{
			struct addrinfo *result;
			struct addrinfo hints;
			it->sock.push_back(socket(AF_INET, SOCK_STREAM, 0));
			if(it->sock.back() < 0)
			{
				perror("From socket error ");
				exit(1);
			}
			int status;
			setsockopt(it->sock.back(), SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
			memset(&hints, 0, sizeof(hints));
			hints.ai_family = AF_UNSPEC;     
			hints.ai_socktype = SOCK_STREAM; 

			status = getaddrinfo(it->host.c_str(), it_listen->c_str(), &hints, &result);
			if (status != 0) {
				perror("From getaddrinfo error: ");
				exit (1);
			}
			std::cerr<<it->sock.back() << "  ---  "<< it_listen->c_str()<< "\n";
			if (bind(it->sock.back(), result->ai_addr, result->ai_addrlen) == -1) {
				perror("From Bind error ");
				exit (1);
			}
			freeaddrinfo(result);
		}
	}
    for (it = serv_data.begin(); it < serv_data.end(); it++)
	{
		for(std::vector<int>::iterator it_socket = it->sock.begin(); it_socket != it->sock.end(); it_socket++)
		{
			it->listening = listen(*it_socket,it->backlog);
			if(it->listening < 0)
			{
				perror("From listen error ");
				exit(1);
			}
		}
	}
	std::vector <int> serverSocket;
    for (it = serv_data.begin(); it < serv_data.end(); it++)
	{
		for(std::vector<int>::iterator it_socket = it->sock.begin(); it_socket != it->sock.end(); it_socket++)
		{
			fcntl(*it_socket, F_SETFL, O_NONBLOCK);
			serverSocket.push_back(*it_socket);
		}
	}
	std::vector <struct pollfd> fds;
	std::vector <client_d> addNewFd;
	int nfds = 0;
	
    for (it = serv_data.begin(); it < serv_data.end(); it++)
	{ 
		for(std::vector<int>::iterator it_socket = it->sock.begin(); it_socket != it->sock.end(); it_socket++)
		{
			struct pollfd temp;
			temp.fd = *it_socket;
			temp.events = POLLIN | POLLOUT | POLLHUP; 
			temp.revents = 0;
			nfds++;
			fds.push_back(temp);
		}
	}
	std::cout << "============== WAITING ==============\n";
	while(1)
	{
		int ret = poll(&fds[0], fds.size(), -1);
		if (ret == -1)
		{
			std::cerr << "error : POLLL" << std::endl;
			break;
		}
		else if (ret > 0)
		{
			for (size_t i = 0; i < fds.size(); i++)
			{
				if (fds.at(i).revents & POLLIN)
				{
					if (find(serverSocket.begin(), serverSocket.end(), fds.at(i).fd) != serverSocket.end()) 
					{
						std::cout << "============== ACCEPT ==============\n";
						fds.push_back(Accept_read(addNewFd, fds.at(i).fd));
						if(fds.back().fd == -1)
						{
							fds.pop_back();
							addNewFd.pop_back();
						}
					}
					std::vector<client_d> ::iterator it_c = addNewFd.begin();
					for ( ;it_c != addNewFd.end() && it_c->acceptFd != fds.at(i).fd; ){
						it_c++;
					}
					if (it_c == addNewFd.end()) {
						continue;
					}
					bzero(it_c->buffer, sizeof(it_c->buffer));
					it_c->lastRead =  get_time();
					std::cout <<"============== recv ==============\n";
					int rec =  recv(fds.at(i).fd, it_c->buffer, sizeof(it_c->buffer), 0);
					if(rec < 1)
					{
						close(fds.at(i).fd);
						clearPollList(fds, *it_c, addNewFd);
						break ;
					}
					it_c->request.append(it_c->buffer, rec);
					it_c->lenRead += rec;
					int len = get_content_len(it_c->request);
					if(it_c->lenRead >= (unsigned long)len)
					{
						if((int)it_c->request.find("\r\n\r\n") != -1)
						{
							it_c->endRead = true;
							bool useServerName = false;
							std::string hostRequest = get_host(it_c->request);
							std::string host = split(hostRequest, ':')[0];
							for (it = serv_data.begin(); it != serv_data.end(); it++)
							{
								if(std::find(it->sock.begin(), it->sock.end(), it_c->socketFd) != it->sock.end())
								{
									for (iteratorServer it_2 = it->DuplicatePort.begin(); it_2 != it->DuplicatePort.end(); it_2++)
									{
										if(std::find(it_2->server_name.begin(), it_2->server_name.end(), hostRequest) != it_2->server_name.end())
										{
											useServerName = true;
											it = it_2;
											break;
										}
									}
									if(!useServerName)
									{
										for (iteratorServer it_2 = it->DuplicatePort.begin(); it_2 != it->DuplicatePort.end(); it_2++)
										{
											if(!it_2->host.compare(host))
											{
												it = it_2;
												break;
											}
										}
									}
									break;
								}
							}
							// cout << it->server_name.at(0) << "\n"<<it_c->request <<"\n";
							HandleRequest h(*it_c, *it);	
						}
					}
				}
				else if (fds.at(i).revents & POLLOUT) {
					std::vector<client_d> ::iterator it_c = addNewFd.begin();
					for ( ;it_c != addNewFd.end() && it_c->acceptFd != fds.at(i).fd; ){
						it_c++;
					}
					if (it_c == addNewFd.end()) {
						continue;
					}
					if(it_c->endRead)
					{
						int sendSize = SENDBUFFER;
						if((ssize_t)it_c->Respons.length() - it_c->sendLen <= sendSize)
							sendSize = (ssize_t)it_c->Respons.length() - it_c->sendLen;
						if(!it_c->request.compare("timeout"))
							sendSize = it_c->Respons.length();
						it_c->sendLen += send(fds.at(i).fd, it_c->Respons.substr(it_c->sendLen).c_str(), sendSize, 0);
						std::cout <<"============== send ==============\n";
						if(it_c->sendLen < 1)
						{
							close(fds.at(i).fd);
							clearPollList(fds, *it_c, addNewFd);
							break ;
						}
						if(it_c->sendLen >= (ssize_t)it_c->Respons.length())
						{
							if(!it_c->Con || !it_c->request.compare("timeout"))
							{
								close(fds.at(i).fd);
								clearPollList(fds, *it_c, addNewFd);
								std::cout <<" ============== CLOSE ==============\n";
								continue;
							}
							else
							{
								it_c->lenRead = 0;
								it_c->endRead = false;
								it_c->sendLen = 0;
								it_c->lastRead = 0;
								it_c->ResponsLength = 0;
								it_c->Con = false;
								it_c->endSend = false;
								it_c->Respons.clear();
								it_c->request.clear();
								std::cout <<" ============== KEEPALIVE ==============\n";
							}
							std::cout <<" ============== DONE ==============\n";
						}
					}
				}
				else if (fds.at(i).revents & ( POLLHUP | POLLERR))
				{
					std::vector<client_d> ::iterator it_c = addNewFd.begin();
					for ( ;it_c != addNewFd.end() && it_c->acceptFd != fds.at(i).fd; ){
						it_c++;
					}
					if (it_c == addNewFd.end()) {
						continue;
					}
					close(fds.at(i).fd);
					clearPollList(fds, *it_c, addNewFd);
					continue;
				}
				if(i >= (size_t)nfds)
				{
					std::vector<client_d> ::iterator it_c = addNewFd.begin();
					for ( ;it_c != addNewFd.end() && it_c->acceptFd != fds.at(i).fd; ){
						it_c++;
					}
					if (it_c == addNewFd.end()) {
						continue;
					}
					if(!it_c->endRead && it_c->lastRead && get_time() - it_c->lastRead > TIMEOUT)
					{
						std::cerr << "============ TIMEOUUUUT ============\n";
						for (it = serv_data.begin(); it != serv_data.end(); it++)
						{
							if(std::find(it->sock.begin(), it->sock.end(), it_c->socketFd) != it->sock.end())
								break;
						}
						if(it != serv_data.end())
						{
							it_c->request = "timeout";
							fds.at(i).revents = POLLOUT;
							it_c->endRead = true;
							HandleRequest h(*it_c, *it);
						}
					}
				} 
			}
		}
	}
}
