/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:40:19 by zait-sli          #+#    #+#             */
/*   Updated: 2022/12/30 04:40:20 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

# include <iostream>
# include <string>

// this calss is the one to parse all data and store it
// so all parsing tools will be defind in this class

class parse
{
	private:
		std::string file;
		// Here we will add a vector a servers;
	public:
		// Constructors
		parse();
		parse(const parse &copy);
		
		// Destructor
		~parse();
		
		// Operators
		parse & operator=(const parse &assign);
		void readFile();
		
};

#endif