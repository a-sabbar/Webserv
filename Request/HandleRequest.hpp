/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:07:55 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/25 11:15:15 by zait-sli         ###   ########.fr       */
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
		// serv_d serv;
		int code;
		string root;
		bool upload;
		
	public:

		HandleRequest(string s, serv_d server);
		void treatSline(string);
		int ckeckSline();
		int ckeckHeaders();
		void treatHeaders(string);
		void splitBody();
		void handleDelte();
		void checkLoctaions();
		void checkRootLoctaion();
		void handleChunked();
		~HandleRequest();
		int getCode(void)
		{
			return code;
		}	
};

#endif