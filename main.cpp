/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:42:44 by asabbar           #+#    #+#             */
/*   Updated: 2023/01/07 10:34:57 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Webserv.hpp"


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
        parse Parsing(arg);    
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}
