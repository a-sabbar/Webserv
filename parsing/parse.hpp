/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:40:19 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/07 11:02:59 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "server.hpp"

// this calss is the one to parse all data and store it
// so all parsing tools will be defind in this class


class parse
{
	private:
		std::string rawFile;
		std::vector<server> serv;
	public:
		parse();
		parse(std::string file);
		parse(const parse &copy);
		

		void remove_comments();
		void readConfig(std::string fileName);
		void collectData(void);
		std::string getParam(std::string &Fpart, std::string gg);

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