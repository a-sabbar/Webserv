/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:25:45 by asabbar           #+#    #+#             */
/*   Updated: 2023/01/09 17:39:19 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include "parsing/parse.hpp"
#include "parsing/server.hpp"
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

void    run_server(std::vector<serv_d> &servers);

#endif