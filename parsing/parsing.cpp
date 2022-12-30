/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:03:19 by asabbar           #+#    #+#             */
/*   Updated: 2022/12/30 12:24:18 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Webserv.hpp"

int check_brackets(std::string &str)
{
	int i = 0;
	int j = 0;
	while (str[i])
	{
		if (str[i] == '{')
			j++;
		if (str[i] == '}')
			j--;
		i++;
	}
	if (j == 0)
		return (0);
	else
		return (-1);
}

void remove_comments(std::string &str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '#')
		{
			int j = i;
			while (str[j] != '\n' && str[j] != '\0')
				j++;
			if(str[j] == '\0')
				return ;
			else
				str.erase (i , j - i );
			i = 0;
		}
		i++;
	}
}


int parsing(std::string  fileName)
{
    std::string     value;
    std::ifstream   myfile;
    myfile.open(fileName);
	if(!myfile.is_open())
	{
		std::cout << "Error : i can't found this file\n" << std::endl;
		return (-1);
	}
	getline(myfile,value, '\0');
	if(value.empty())
	{
		std::cout << "Error : i can't found this file\n" << std::endl;
		return (-1);
	}
	//remove comments
	remove_comments(value);

	//check brackets
	if(check_brackets(value) == -1)
	{
		std::cout << "Error : brackets\n" << std::endl;
		return (-1);
	}
	std::cout << value << std::endl;
	return (0);
}
