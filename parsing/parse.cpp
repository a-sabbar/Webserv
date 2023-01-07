/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:40:23 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/07 11:14:58 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.hpp"

// Constructors
parse::parse()
{
}
parse::parse(std::string file)
{
	readConfig(file);
	collectData();
}

parse::parse(const parse &copy)
{
	(void) copy;
}


void parse::remove_comments()
{
	int i = 0;
	while (this->rawFile[i])
	{
		if (this->rawFile[i] == '#')
		{
			int j = i;
			while (this->rawFile[j] != '\n' && this->rawFile[j] != '\0')
				j++;
			if(this->rawFile[j] == '\0')
				return ;
			else
				this->rawFile.erase (i , j - i );
			i = 0;
		}
		i++;
	}
}

void parse::readConfig(std::string fileName)
{
    std::ifstream   myfile;
    myfile.open(fileName);
	if(!myfile.is_open())
		throw ConfigNotValid();
	getline(myfile,rawFile, '\0');
	if(rawFile.empty())
		throw ConfigNotValid();
	remove_comments();
}


void parse::collectData()
{
	std::string Fpart;
	server s;
	size_t firstBracket = rawFile.find_first_of("{",0);
	size_t secondBracket = rawFile.find_first_of("{",firstBracket+1);

	if (firstBracket == std::string::npos || secondBracket == std::string::npos)
		throw ConfigNotValid();
	Fpart = rawFile.substr(firstBracket + 1,secondBracket - firstBracket - 1);
	// std::cout << Fpart << std::endl;
	s.server_name =  getParam(Fpart,"server_name");
	s.host = getParam(Fpart,"host");
	s.listen = getParam(Fpart,"listen");
	s.root = getParam(Fpart,"root");..............
	
}

void parse::myTrim(std::string &s, const std::string &toTrim = " \t\f\v\n\r")
{
	s = s.substr(s.find_first_not_of(toTrim), s.length());
	s = s.substr(0, s.find_last_not_of(toTrim) +1);
}

std::string parse::getParam(std::string &Fpart, std::string gg)
{
	size_t i,j;
	i = Fpart.find(gg,0) + gg.length();
	j = Fpart.find_first_of(";\n",i);
	std::string t =  Fpart.substr(i,j - i);
	myTrim(t);
	if (t.empty())
		throw ConfigNotValid(); 
	std::cout << t<< std::endl;
	return t;
}

// Destructor
parse::~parse()
{
}


// Operators
parse & parse::operator=(const parse &assign)
{
	(void) assign;
	return *this;
}
