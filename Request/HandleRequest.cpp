/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:07:58 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/17 19:53:25 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleRequest.hpp"
#include <cstdlib>

HandleRequest::HandleRequest(std::string buff)
{
	code = 200;
	message = "Everything is good";
	std::string startLine = buff.substr(0, buff.find_first_of("\n") -1);
	treatSline(startLine);
	treatHeaders(buff.substr(startLine.size() + 2,buff.find(Spliter)));
	ckeckSline();
	if (code == 200)
	{
		body = buff.substr(buff.find(Spliter) + SpliterLen);
		ckeckHeaders();
		if (!headers["Transfer-Encoding"].compare("chunked"))
		{
			handleChunked();
			cout << "Encoding has been handled" << endl;
		}
		if (!headers["Content-Type"].compare("multipart/form-data"))
		{
			cout << "Splited the body" << endl;
			splitBody();
		}
		else if (!headers["Content-Type"].compare("application/octet-stream"))
			Getdata gt(body,1);
	}
	// cout << "-----------------------------" << endl;
	// cout << message << endl;
	// cout << code << endl;
}

int HandleRequest::ckeckSline()
{
	if (method != "GET" && method != "POST" && method != "DELETE")
	{
		message = "Not Implemented";
		code = 501;
		return 1;
	}
	else if (version != "HTTP/1.1")
	{
			
		message = "HTTP Version Not Supported";
		code = 505;
		return 1;
	}
	else if (target.at(0) != '/')
	{
			
		message = "Bad Request";
		code = 404;
		return 1;
	}
	return 0;
}

int HandleRequest::ckeckHeaders()
{
	string temp = headers["Content-Type"];
	if(!temp.empty())
	{
		if (temp.find("boundary=") != string::npos)
		{
			Boundary = temp.substr(temp.find("boundary=") + 9);
			// cout << temp << endl;
			temp = temp.substr(0, temp.find("boundary=") - 2);
			headers["Content-Type"] = temp;
		}
	}
	if (headers["Host"].empty())
	{
		message = "Bad Request";
		code = 404;
		return 1;
	}
	return 0;
}

void HandleRequest::handleChunked()
{
	string tbody;
	string hexlen;
	size_t dec = 1;	
	while(dec)
	{
		hexlen = body.substr(0, body.find("\r\n"));
		body = body.substr(hexlen.length() + 2);
		dec = strtoul(hexlen.c_str(), NULL, 16);
		if (dec != 0)
		{
			tbody += body.substr(0, dec);
			body = body.substr(dec + 2);
		}
	}
	body = tbody;
}


void HandleRequest::splitBody()
{
	size_t b=0,nb;
	string endB = Boundary + "--\n";
	Boundary += "\n";
		
	b = body.find(Boundary, b) + Boundary.length();
	body = body.substr(b);
	b = 0;
	while (1)
	{
		nb = body.find(Boundary, b);
		if (nb == string::npos)
		{
			string t = body.substr(b,nb - b);
			t = t.substr(0, t.length() - endB.length() - 3);
			data.push_back(t);
			break ;
		}
		data.push_back(body.substr(b,nb - b - 3));
		nb += Boundary.length();
		b = nb;
	}
	for (vector<string>::iterator it = data.begin(); it != data.end(); it++)
	{
		// cout << "1==========" << endl;
		// cout <<*it  <<endl;
		// cout << it->substr(it->find(Spliter) + SpliterLen)  <<endl;
		// cout <<it->length()  <<endl;
		Getdata gt(*it,0);
		// cout << "2==========" << endl;
	}
}

void HandleRequest::treatSline(std::string startLine)
{
	method = startLine.substr(0,startLine.find_first_of(" "));
	startLine = startLine.substr(method.size() + 1);
	target = startLine.substr(0,startLine.find_first_of(" "));
	startLine = startLine.substr(target.size() + 1);
	version = startLine.substr(0,startLine.find_first_of(" "));
	if (target.find("?") != std::string::npos)
		queryString = target.substr(target.find("?"));
}

void mytrim(std::string &s, const std::string &toTrim = " \t\f\v\n\r")
{
	s = s.substr(s.find_first_not_of(toTrim), s.length());
	s = s.substr(0, s.find_last_not_of(toTrim) +1);
}

void HandleRequest::treatHeaders(std::string hd)
{
	std::stringstream ss(hd);
    std::string line;
    while (std::getline(ss, line)) {
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 2);
			mytrim(value);
            headers[key] = value;
        }
    }
}
HandleRequest::~HandleRequest()
{
	
}

///check request line => methode $$ uri.at(0) = '/' && http version || query string ?key=value&&key=value
///check headrs host !bad request &&  if(post)=> content lenght && content type && content lenght transfer encoded chencd
///parse body : multipart/form-data; && 