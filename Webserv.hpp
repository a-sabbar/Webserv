/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:25:45 by asabbar           #+#    #+#             */
/*   Updated: 2023/03/01 14:36:07 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include "parsing/parse.hpp"
#include "parsing/server.hpp"
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

#define TIMEOUT 50000
#define SENDBUFFER 6000000

using namespace std;
void    run_server(std::vector<serv_d> &servers);
std::vector<std::string> split(std::string str, char delimiter);
void    print_error(std::string  print);
#endif

