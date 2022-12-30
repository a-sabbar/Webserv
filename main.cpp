/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:42:44 by asabbar           #+#    #+#             */
/*   Updated: 2022/12/30 12:24:06 by asabbar          ###   ########.fr       */
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
    atexit(f);
    if (ac != 2)
        return (print_error("ERROR : number of args\n"), 0);
    if(parsing((std::string)av[1]) == -1)
        return (print_error("ERROR : parsing\n"), 0);
    return (0);
}
