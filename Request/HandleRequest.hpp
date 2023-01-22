/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:07:55 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/22 05:18:05 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLEREQUEST_HPP
# define HANDLEREQUEST_HPP

#include "../Webserv.hpp"
#include "Getdata.hpp"
#define Spliter "\r\n\r\n"
#define SpliterLen 4
using namespace std;

class HandleRequest
{
	private:
		
		string method;
		string target;
		string version;
		map<string, string> headers;
		string message;
		string Boundary;
		string queryString;
		vector<string> data;
		string body;
		map<string,map<string, vector<string> > > locations;
		int code;
		
	public:

		HandleRequest(string s);
		void treatSline(string);
		int ckeckSline();
		int ckeckHeaders();
		void treatHeaders(string);
		void splitBody();
		void checkLoctaions();
		void handleChunked();
		~HandleRequest();
		int getCode(void)
		{
			return code;
		}	
};

#endif