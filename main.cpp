/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:42:44 by asabbar           #+#    #+#             */
/*   Updated: 2023/01/09 17:39:44 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"


void    print_error(std::string  print)
{
    std::cerr << print << std::endl;
}

void f()
{
    system("leaks webser");
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Ghayarha" << std::endl;
        return 1;
    }
    std::string arg = std::string(av[1]);
    try
    {
        // parse Parsing(arg);
        // run_server(Parsing.getServer());
        
        
        
        std::vector<serv_d> test;
        serv_d s1;

        s1.set_host("127.0.0.1");
        s1.set_listen("80");
        s1.set_server_name("achraf.com");
        s1.set_max_body_size(999999999);
        s1.set_root("/Users/asabbar/Desktop/websrv/public");

        serv_d s2;
    
        s2.set_host("127.0.0.1");
        s2.set_listen("8080");
        s2.set_server_name("achraf.com");
        s2.set_max_body_size(999999999);
        s2.set_root("/Users/asabbar/Desktop/websrv/public");
    
        test.push_back(s1);
        test.push_back(s2);
        run_server(test);
        
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
