/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:25:45 by asabbar           #+#    #+#             */
/*   Updated: 2023/03/12 12:34:16 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include "parsing/parse.hpp"
#include "parsing/server.hpp"
#include "Run_serv/run_server.hpp"
#include "Request/HandleRequest.hpp"
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

#define RedColor std::cout << "\033[31m";
#define DefaultColor std::cout << "\033[0m";
#define GreenColor std::cout << "\033[32m";
#define YellowColor std::cout << "\033[33m";
#define TIMEOUT 50000
#define SENDBUFFER 6000000

using namespace std;
std::vector<std::string> split(std::string str, char delimiter);
void    print_error(std::string  print);
#endif

