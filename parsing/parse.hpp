/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:40:19 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/27 15:27:38 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include "../Webserv.hpp"
#include "server.hpp"
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
// this calss is the one to parse all data and store it
// so all parsing tools will be defind in this class
// class serv_d;

class parse
{
	private:
		std::string rawFile;
		std::vector<std::string> servs;
		std::vector<class serv_d> serv;
	public:
		parse();
		parse(std::string file);
		parse(const parse &copy);

		void remove_comments();
		void readConfig(std::string fileName);
		void setsers();
		void collectData(void);
		std::string getParam(std::string &Fpart, std::string gg);
		
		std::vector<serv_d> &getServer();
		class ConfigNotValid  : public std::exception
		{
			public:
				const char * what() const throw(){
					return ("Config file not valid");
				}
		}	;
		void myTrim(std::string &s, const std::string &toTrim);
		~parse();
		
		parse & operator=(const parse &assign);
		
};

#endif