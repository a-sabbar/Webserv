/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:40:19 by zait-sli          #+#    #+#             */
/*   Updated: 2023/02/26 20:42:51 by zait-sli         ###   ########.fr       */
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

class serv_d;

class Location{
	public:
		std::string						path;
		std::string						autoindex;
		std::string						root;
		std::string						index;
		std::vector<std::string>		methods;
		std::string						cgi_bin;
		std::string						returnn;
		std::string						upload_store;
};
class parse
{
	private:
		std::string					rawFile;
		std::vector<std::string>	servs;
		std::vector<serv_d>	serv;
	public:
		parse();
		parse(std::string file);
		parse(const parse &copy);
		
		void								printData();
		void								checkData();
		void 								remove_comments();
		void 								readConfig(std::string fileName);
		void 								setsers();
		void 								collectData(void);
		std::string 						getParam(std::string &Fpart, std::string gg, size_t max);
		std::string 						getParamLocation(std::string &Fpart, std::string gg, int i, size_t max, int obli);
		std::vector<std::string> 			getErrorPage(std::string Fpart, std::string gg);
		std::vector<Location>  				getLocations(std::string Fpart);
		std::vector<serv_d>					&getServer();
		void 								checkSantax();
		std::string 						getPaPath(std::string &Fpart, std::string gg, size_t i);
		void								checkDuplicatePort();
		void								checkErrorPage();
		void								mergeParser();
		bool								checkIsDigit(const char *str);
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