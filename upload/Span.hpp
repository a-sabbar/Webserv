/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 09:12:40 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/06 16:09:12 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include<iterator>
#include <limits>

typedef std::vector<int>::iterator iterator;

class Span 
{
	private:
		unsigned int N;
		std::vector<int> vec;
	public:
		Span();
		Span(unsigned int N);
		Span(const Span &copy);
		int shortestSpan();
		int longestSpan();
		void addNumber(int number);
		void addNumbers(iterator begin, iterator end);
		class reachedMaxNumbers  : public std::exception
		{
			public:
				const char * what() const throw(){
					return ("Reached Max Numbers");
				}
		}	;
		class sizeTooLow : public std::exception
		{
			public:
				const char * what() const throw(){
					return ("Size Too Low ");
				}
		}	;
		~Span();
		Span & operator=(const Span &assign);
		
};

#endif