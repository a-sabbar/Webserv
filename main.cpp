/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:42:44 by asabbar           #+#    #+#             */
/*   Updated: 2023/03/12 13:30:28 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"
#include <iostream>
#include <filesystem>

void    print_error(std::string  print)
{
    std::cerr << print << std::endl;
}

int main(int ac, char **av)
{   
    std::string arg;
    if (ac > 2)
    {
        print_error("Ghayarha\n");
        return 1;
    }
    else if(ac == 2)
        arg = std::string(av[1]);
    else
        arg = "config_file/default.conf";
    try
    {
        parse Parsing(arg);
        std::__1::vector<serv_d> myServers = Parsing.getServer();
        
        runMyServer runServer(myServers);
        
        std::vector<serv_d> ::iterator it = myServers.begin();
        for (it = myServers.begin(); it < myServers.end(); it++)
        {
            for (std::vector<int> ::iterator i = it->sock.begin(); i < it->sock.end(); i++)
                close(*i);
        }
    }
    catch(std::exception &e)
    {
        RedColor
        std::cerr << e.what() << std::endl;
        DefaultColor
    }

    return (0);
}
