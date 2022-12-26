/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:03:19 by asabbar           #+#    #+#             */
/*   Updated: 2022/12/25 18:47:40 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Webserv.hpp"

int parsing(std::string  file)
{
    std::string     value;
    std::ifstream   myfile;
    myfile.open(file);
	if(!myfile.is_open())
	{
		std::cout << "Error : i can't found this file\n" << std::endl;
		return (-1);
	}
    while (getline(myfile,value, '\0'))
    {
        std::cout << "*" << std::endl;
    }
    std::cout << value << std::endl;
    return (0);
}