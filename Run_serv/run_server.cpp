/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:16:36 by asabbar           #+#    #+#             */
/*   Updated: 2023/03/12 13:00:18 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Webserv.hpp"
#include "run_server.hpp"
#include <fcntl.h>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


runMyServer::runMyServer(/* args */)
{
}
runMyServer::runMyServer(std::vector<serv_d> &serv_data)
{
	run(serv_data);
}

runMyServer::~runMyServer()
{
}

long long int runMyServer::get_time(void)
{
	struct timeval current_time;
	long long int result;

	gettimeofday(&current_time, NULL);
	result = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (result);
}

struct pollfd runMyServer::Accept_read(int fd)
{
	struct pollfd temp;
	client_d newFd;
	struct sockaddr_storage their_addr;
	socklen_t addr_size = sizeof(their_addr);

	temp.fd = accept(fd, (struct sockaddr *)&their_addr, &addr_size);
	fcntl(temp.fd, F_SETFL, O_NONBLOCK);
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
	return (temp);
}

int runMyServer::get_content_len(std::string request)
{
	int start = (int)request.find("Content-Length: ", 0);
	if (start == -1)
		return (0);
	else
		start += (int)strlen("Content-Length: ");
	std::string check = request.substr(start, request.find("\r\n", start) - start);
	int endHeader = request.find("\r\n\r\n", start);
	if (endHeader == -1)
		return (atoi(check.c_str()));
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

std::string runMyServer::get_host(std::string request)
{
	size_t start = request.find("Host: ", 0);
	if ((int)start == -1)
		return ("Not Found hhhhh");
	else
		start += strlen("Host: ");
	std::string host = request.substr(start, request.find("\n", start) - start);
	ft_Trim(host);
	return host;
}

void runMyServer::clearPollList(client_d client)
{
	if (fds.size())
	{
		std::vector<struct pollfd>::iterator it_poll = fds.begin();
		while (it_poll->fd != client.acceptFd && it_poll != fds.end())
			it_poll++;
		if (it_poll->fd == client.acceptFd)
			fds.erase(it_poll);
	}
	if (addNewFd.size())
	{
		std::vector<client_d>::iterator iterator_clientlient = addNewFd.begin();
		while (iterator_clientlient->acceptFd != client.acceptFd && iterator_clientlient != addNewFd.end())
			iterator_clientlient++;
		if (iterator_clientlient->acceptFd == client.acceptFd)
			addNewFd.erase(iterator_clientlient);
	}
}

std::string runMyServer::get_path(std::string request)
{
	std::string firstline = request.substr(0, request.find_first_of("\r\n", 0));

	int firstspace = firstline.find_first_of(" ", 0) + 1;

	int secondspace = firstline.find_last_of(" ", firstline.length());

	return firstline.substr(firstspace, secondspace - firstspace);
};

void runMyServer::binding(std::vector<serv_d> &serv_data)
{
	int option = 1;
	it = serv_data.begin();
	for (it = serv_data.begin(); it < serv_data.end(); it++)
	{
		for (std::vector<std::string>::iterator it_listen = it->listens.begin(); it_listen < it->listens.end(); it_listen++)
		{
			struct addrinfo *result;
			struct addrinfo hints;
			it->sock.push_back(socket(AF_INET, SOCK_STREAM, 0));
			if (it->sock.back() < 0)
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
			if (status != 0)
			{
				perror("From getaddrinfo error: ");
				exit(1);
			}
			if (bind(it->sock.back(), result->ai_addr, result->ai_addrlen) == -1)
			{
				perror("From Bind error ");
				exit(1);
			}
			GreenColor
			std::cerr	<< " socket : " << it->sock.back()
						<< "  Binding with Port :  " << it_listen->c_str() 
						<< " Host : " << it->host.c_str() << " ✅\n\n";
			DefaultColor
			freeaddrinfo(result);
		}
	}
	for (it = serv_data.begin(); it < serv_data.end(); it++)
	{
		for (std::vector<int>::iterator it_socket = it->sock.begin(); it_socket != it->sock.end(); it_socket++)
		{
			if (listen(*it_socket, it->backlog) < 0)
			{
				perror("From listen error ");
				exit(1);
			}
		}
	}
}


int runMyServer::readRequest(std::vector<serv_d> &serv_data, int fd)
{
	bzero(iterator_client->buffer, sizeof(iterator_client->buffer));
	iterator_client->lastRead = get_time();
	GreenColor
	std::cout << "                            RECV                \n\n";
	DefaultColor
	int rec = recv(fd, iterator_client->buffer, sizeof(iterator_client->buffer), 0);
	if (rec < 1)
	{
		close(fd);
		clearPollList(*iterator_client);
		return 0;
	}
	iterator_client->request.append(iterator_client->buffer, rec);
	iterator_client->lenRead += rec;
	int len = get_content_len(iterator_client->request);
	if (iterator_client->lenRead >= (unsigned long)len)
	{
		if ((int)iterator_client->request.find("\r\n\r\n") != -1)
		{
			iterator_client->endRead = true;
			bool useServerName = false;
			std::string hostRequest = get_host(iterator_client->request);
			std::string host = split(hostRequest, ':')[0];
			for (it = serv_data.begin(); it != serv_data.end(); it++)
			{
				if (std::find(it->sock.begin(), it->sock.end(), iterator_client->socketFd) != it->sock.end())
				{
					for (iteratorServer it_2 = it->DuplicatePort.begin(); it_2 != it->DuplicatePort.end(); it_2++)
					{
						if (std::find(it_2->server_name.begin(), it_2->server_name.end(), hostRequest) != it_2->server_name.end())
						{
							useServerName = true;
							it = it_2;
							break;
						}
					}
					if (!useServerName)
					{
						for (iteratorServer it_2 = it->DuplicatePort.begin(); it_2 != it->DuplicatePort.end(); it_2++)
						{
							if (!it_2->host.compare(host))
							{
								it = it_2;
								break;
							}
						}
					}
					break;
				}
			}
			HandleRequest h(*iterator_client, *it);
		}
	}
	return 1;
}



void runMyServer::run(std::vector<serv_d> &serv_data)
{
	binding(serv_data);

	/* Stored  socket of servers*/
	
	for (it = serv_data.begin(); it < serv_data.end(); it++)
	{
		for (std::vector<int>::iterator it_socket = it->sock.begin(); it_socket != it->sock.end(); it_socket++)
		{
			fcntl(*it_socket, F_SETFL, O_NONBLOCK);
			serverSocket.push_back(*it_socket);
		}
	}

	/* Create  polllist*/

	nfds = 0;
	for (it = serv_data.begin(); it < serv_data.end(); it++)
	{
		for (std::vector<int>::iterator it_socket = it->sock.begin(); it_socket != it->sock.end(); it_socket++)
		{
			struct pollfd temp;
			temp.fd = *it_socket;
			temp.events = POLLIN | POLLOUT | POLLHUP;
			temp.revents = 0;
			fds.push_back(temp);
			nfds++;
		}
	}
	std::cout << "            ==============  WAITING  ==============\n";
	while (true)
	{
		int ret = poll(&fds[0], fds.size(), -1);
		if (ret == -1)
		{
			RedColor
			std::cerr << "error : POLLL" << std::endl;
			DefaultColor
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
						GreenColor
						std::cout << "                            ACCEPT              \n\n";
						DefaultColor
						fds.push_back(Accept_read(fds.at(i).fd));
						if (fds.back().fd == -1)
						{
							fds.pop_back();
							addNewFd.pop_back();
						}
						continue ;
					}
					iterator_client = addNewFd.begin();
					for (; iterator_client != addNewFd.end() && iterator_client->acceptFd != fds.at(i).fd;)
					{
						iterator_client++;
					}
					if (iterator_client == addNewFd.end())
					{
						continue;
					}
					if(!readRequest(serv_data, fds.at(i).fd))
						break;
				}
				else if (fds.at(i).revents & POLLOUT)
				{
					iterator_client = addNewFd.begin();
					for (; iterator_client != addNewFd.end() && iterator_client->acceptFd != fds.at(i).fd;)
					{
						iterator_client++;
					}
					if (iterator_client == addNewFd.end())
					{
						continue;
					}
					if (iterator_client->endRead)
					{
						int sendSize = SENDBUFFER;
						if ((ssize_t)iterator_client->Respons.length() - iterator_client->sendLen <= sendSize)
							sendSize = (ssize_t)iterator_client->Respons.length() - iterator_client->sendLen;
						if (!iterator_client->request.compare("timeout"))
							sendSize = iterator_client->Respons.length();
						iterator_client->sendLen += send(fds.at(i).fd, iterator_client->Respons.substr(iterator_client->sendLen).c_str(), sendSize, 0);
						GreenColor
						std::cout << "                            SEND                \n\n";
						DefaultColor
						if (iterator_client->sendLen < 1)
						{
							close(fds.at(i).fd);
							clearPollList(*iterator_client);
							break;
						}
						if (iterator_client->sendLen >= (ssize_t)iterator_client->Respons.length())
						{
							if (!iterator_client->Con || !iterator_client->request.compare("timeout"))
							{
								close(fds.at(i).fd);
								clearPollList(*iterator_client);
								YellowColor
								std::cout << "                            CLOSE               \n\n";
								DefaultColor
								GreenColor
								std::cout << "                            DONE ✅              \n\n";
								DefaultColor
								continue;
							}
							else
							{
								iterator_client->lenRead = 0;
								iterator_client->endRead = false;
								iterator_client->sendLen = 0;
								iterator_client->lastRead = 0;
								iterator_client->ResponsLength = 0;
								iterator_client->Con = false;
								iterator_client->endSend = false;
								iterator_client->Respons.clear();
								iterator_client->request.clear();
								GreenColor
								std::cout << "                            KEEPALIVE           \n\n";
								DefaultColor
							}
							GreenColor
							std::cout << "                            DONE ✅              \n\n";
							DefaultColor
						}
					}
				}
				else if (fds.at(i).revents & (POLLHUP | POLLERR))
				{
					iterator_client = addNewFd.begin();
					for (; iterator_client != addNewFd.end() && iterator_client->acceptFd != fds.at(i).fd;)
					{
						iterator_client++;
					}
					if (iterator_client == addNewFd.end())
					{
						continue;
					}
					RedColor
					std::cout << "                            POLLHUP && POLLERR  \n\n";
					DefaultColor
					close(fds.at(i).fd);
					clearPollList(*iterator_client);
					continue;
				}
				if (i >= (size_t)nfds)
				{
					iterator_client = addNewFd.begin();
					for (; iterator_client != addNewFd.end() && iterator_client->acceptFd != fds.at(i).fd;)
					{
						iterator_client++;
					}
					if (iterator_client == addNewFd.end())
					{
						continue;
					}
					if (!iterator_client->endRead && iterator_client->lastRead && get_time() - iterator_client->lastRead > TIMEOUT)
					{
						RedColor
						std::cerr << "                            TIMEOUUUUT          \n\n";
						DefaultColor
						for (it = serv_data.begin(); it != serv_data.end(); it++)
						{
							if (std::find(it->sock.begin(), it->sock.end(), iterator_client->socketFd) != it->sock.end())
								break;
						}
						if (it != serv_data.end())
						{
							iterator_client->request = "timeout";
							fds.at(i).revents = POLLOUT;
							iterator_client->endRead = true;
							HandleRequest h(*iterator_client, *it);
						}
					}
				}
			}
		}
	}
}
