/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:07:55 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/13 18:28:46 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLEREQUEST_HPP
# define HANDLEREQUEST_HPP

#include "../Webserv.hpp"

class HandleRequest
{
	private:
		
		std::string method;
		std::string target;
		std::string version;
		std::map<std::string, std::string> headers;
		std::string message;
		int code;
	public:
		// Constructors
		HandleRequest(char *s);
		void treatSline(std::string);
		int ckeckSline();
		void treatHeaders(std::string);
		~HandleRequest();
		int getCode(void)
		{
			return code;
		}
		
		
		
};

#endif