/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:42:44 by asabbar           #+#    #+#             */
/*   Updated: 2023/02/27 21:40:21 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

                    
void    print_error(std::string  print)
{
    std::cerr << print << std::endl;
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
        parse Parsing(arg);
        std::__1::vector<serv_d> value = Parsing.getServer();
        run_server(value);
        std::vector<serv_d> ::iterator it = value.begin();
        for (it = value.begin(); it < value.end(); it++)
        {
            for (std::vector<int> ::iterator i = it->sock.begin(); i < it->sock.end(); i++)
                close(*i);
        }
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
