/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 04:40:30 by zait-sli          #+#    #+#             */
/*   Updated: 2022/12/30 04:40:31 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>

class server
{
	public:
		std::string server_name;
		std::string host;
		std::string listen; // momkin tkoun vector 
		size_t max_body_size; //always with B
		std::string root;
		//every variable above needs to be pasred and checked for errors before getting stored;

		// Constructors
		server();
		server(const server &copy);
		
		// Destructor
		~server();
		
		// Operators
		server & operator=(const server &assign);
		
};

#endif