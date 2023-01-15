/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_server.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 20:16:36 by asabbar           #+#    #+#             */
/*   Updated: 2023/01/15 02:04:59 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Webserv.hpp"
#include <fcntl.h>

void myTrim(std::string &s, const std::string &toTrim = " \t\f\v\n\r")
{
	s = s.substr(s.find_first_not_of(toTrim), s.length());
	s = s.substr(0, s.find_last_not_of(toTrim) +1);
}

void testCnnection (int item)
{
	if(item < 0)
	{
		perror("KO :(\nFailed to connect    : ");
		exit(1);
	}
	return ;
}

struct pollfd  Accept_read(std::vector<serv_d> &servers, int i, std::vector<client_d> &addNewFd)
{
	struct sockaddr_in address = servers.at(i).address;
	int addrlen = sizeof(address);
	struct pollfd temp;
	client_d newFd;

	servers.at(i).is_accept = true;
	// printf("fd sock:  %d\n", servers.at(i).sock);
	temp.fd = accept(servers.at(i).sock, (sockaddr *)&address, (socklen_t *)&addrlen);
	temp.events = POLLIN | POLLOUT; 
	temp.revents = 0;
	newFd.acceptFd = temp.fd;
	newFd.socketFd = servers.at(i).sock;
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
	int start = request.find("Content-Length: ", 0) + strlen("Content-Length: ");
	std::string check = request.substr(start, request.find("\r\n", start));
	return atoi(check.c_str());
}



void clearPollList(std::vector<serv_d> &servers, std::vector <struct pollfd> &fds, client_d client, std::vector <client_d> &addNewFd)
{
	if(servers.size())
	{
		std::vector<serv_d>::iterator it_s = servers.begin();
		while(it_s->sock != client.socketFd && it_s != servers.end())
			it_s++;
		it_s->is_accept = false;
	}
	if(fds.size())
	{
		
		std::vector<struct pollfd>::iterator it_poll = fds.begin();
		while(it_poll->fd != client.acceptFd && it_poll != fds.end())
			it_poll++;
		fds.erase(it_poll);
	}
	if(addNewFd.size())
	{
		std::vector <client_d>::iterator it_client = addNewFd.begin();
		while(it_client->socketFd != client.socketFd && it_client != addNewFd.end() )
			it_client++;
		addNewFd.erase(it_client);
	}
}


std::string get_path(std::string request)
{
	std::string firstline = request.substr(0, request.find_first_of("\r\n",0));
	
	int firstspace = firstline.find_first_of(" ",0);
	
	
	int secondspace = firstline.find_last_of(" ", firstline.length()) - 2;

	return firstline.substr(firstspace, secondspace);
};


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
	std::vector <client_d> addNewFd;
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
			for (size_t i = 0; i < fds.size(); i++)
			{
				it = servers.begin();
				for (size_t t = 0; t < i; t++)
					it++;
				if(i < servers.size() && !servers.at(i).is_accept && fds.at(i).revents)
				{
					std::cout <<"accept : " << servers.at(i).sock <<std::endl;
					fds.push_back(Accept_read(servers, i, addNewFd));
					// sleep(1);
				}
				else if (fds.at(i).revents & POLLIN)
				{
					std::vector<client_d> ::iterator it_c = addNewFd.begin();
					for (size_t t = servers.size() ; t < i; t++)
						it_c++;
					// puts("read");
					// sleep(1);
					bzero(it_c->buffer, sizeof(it_c->buffer));
					int rec =  recv(fds.at(i).fd, it_c->buffer, sizeof(it_c->buffer), 0);
					if(rec == -1)
					{
						std::cout <<"hello by"<<std::endl;
						clearPollList(servers, fds, *it_c, addNewFd);
						break ;
					}
					it_c->request.append(it_c->buffer, rec);
					it_c->lenRead += rec;
					int m = get_method(it_c->request);
					if(m == 1)
					{
						if(it_c->request.find("\r\n\r\n") != std::string::npos && it_c->request.length()){
							it_c->endRead = true;
						}
					}
					if(m == 2)
					{
						int len = get_content_len(it_c->request);
						if(it_c->lenRead >= (unsigned long)len)
							it_c->endRead = true;
					}
				}
				else if (fds.at(i).revents & POLLOUT) {
					std::vector<client_d> ::iterator it_c = addNewFd.begin();
					for (size_t t = servers.size() ; t < i; t++)
						it_c++;
					if(it_c->endRead && it_c->request.length())
					{

						

						// std::cout << it_c->request << std::endl;
						HandleRequest h(it_c->request);								///////   HandleRequest
						// std::cout << h.getCode() << std::endl;						///////   HandleRequest







						
						std::string path = get_path(it_c->request);
						myTrim(path);
						


								
						// int fd = open("img.jpg",O_CREAT | O_RDWR,0777);   												//Don't delete these lines
						// std::string test = it->request.substr(it->request.find("\r\n\r\n", 0) + 4, it->lenRead);      	//Don't delete these lines	 
						// write(fd,test.c_str(), test.length());															//Don't delete these lines			
						// sleep(1);																							//Don't delete these lines								



						// std::string value;
						// std::ifstream  file;
						// std::ifstream  fileError;
						// file.open("Run_serv/html" + path);
						// if(!path.compare("/"))
						// {
						// 	fileError.open("Run_serv/html/home.html");
						// 	getline(fileError , value, '\0');
						// 	std::string len = std::to_string(value.length());
						// 	value = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + len + "\r\n\r\n" + value;
						// }
						// else if(!file.is_open())
						// {
						// 	puts("error KO :(\n");
						// 	fileError.open("Run_serv/html/error404.html");
						// 	getline(fileError , value, '\0');
						// 	std::string len = std::to_string(value.length());
						// 	value = "HTTP/1.1 404 KO\r\nContent-Type: text/html\r\nContent-Length: " + len + "\r\n\r\n" + value;
						// }
						// else
						// {
						// 	std::cout<< "paaath  : "<< path<< std::endl;
						// 	getline(file , value, '\0');
						// 	std::string len = std::to_string(value.length());
						// 	value = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: " + len + "\r\n\r\n" + value;
						// }
						// write(fds.at(i).fd, (char *)value.c_str(), value.length());
						close(fds.at(i).fd);
						clearPollList(servers, fds, *it_c,addNewFd);
					}
				}
			}
			// sleep(3);
		}
		std::cout <<"============== DONE ==============\n";
	}
	
}