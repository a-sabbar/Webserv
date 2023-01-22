/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 07:53:49 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/06 16:52:09 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

 
int main()
{
    Span sp = Span(1000002);
    std::vector<int> vec;
    srand(time(0));
    for(int i = 0; i < 199; i++)
        vec.push_back(rand());
    try
    {
        sp.addNumbers(vec.begin(), vec.end());
        sp.addNumber(6);
        sp.addNumber(7);
        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

