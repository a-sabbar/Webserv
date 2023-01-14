/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:42:44 by asabbar           #+#    #+#             */
/*   Updated: 2023/01/14 09:57:58 by asabbar          ###   ########.fr       */
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
        serv_d s3;
    
        s3.set_host("127.0.0.1");
        s3.set_listen("9090");
        s3.set_server_name("achraf.com");
        s3.set_max_body_size(999999999);
        s3.set_root("/Users/asabbar/Desktop/websrv/public");
        serv_d s4;
    
        s4.set_host("127.0.0.1");
        s4.set_listen("90");
        s4.set_server_name("achraf.com");
        s4.set_max_body_size(999999999);
        s4.set_root("/Users/asabbar/Desktop/websrv/public");
        serv_d s5;
    
        s5.set_host("127.0.0.1");
        s5.set_listen("1234");
        s5.set_server_name("achraf.com");
        s5.set_max_body_size(999999999);
        s5.set_root("/Users/asabbar/Desktop/websrv/public");
    
        test.push_back(s1);
        test.push_back(s2);
        test.push_back(s3);
        test.push_back(s4);
        test.push_back(s5);
        run_server(test);
        
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
