/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:07:55 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/30 16:06:08 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLEREQUEST_HPP
# define HANDLEREQUEST_HPP

#include "../Webserv.hpp"
#include "Getdata.hpp"
#include "../parsing/server.hpp"
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
		string Response;
		string ResBody;
		// serv_d serv;
		string code;
		string root;
		bool upload;
		
	public:

		HandleRequest(class client_d &client, serv_d &server);
		void generateResponse();
		void treatSline(string);
		int ckeckSline();
		int ckeckHeaders();
		void treatHeaders(string);
		void splitBody();
		void handleDelte();
		void handleGet();
		void checkLoctaions();
		void checkRootLoctaion();
		void handleChunked();
		~HandleRequest();
		string getCode(void)
		{
			return code;
		}	
};

string ReadFile(string File);
bool checkExist (const std::string& name);
void mytrim(std::string &s, const std::string &toTrim = " \t\f\v\n\r");

#endif