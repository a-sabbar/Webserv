/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:07:58 by zait-sli          #+#    #+#             */
/*   Updated: 2023/01/16 13:24:43 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleRequest.hpp"

HandleRequest::HandleRequest(std::string buff)
{
	code = 200;
	message = "Everything is good";
	std::string startLine = buff.substr(0, buff.find_first_of("\n") -1);
	treatSline(startLine);
	treatHeaders(buff.substr(startLine.size() + 2,buff.find(Spliter)));
	if (!queryString.empty())
		std::cout<< queryString << std::endl;
	ckeckSline();
	if (code == 200)
	{
		body = buff.substr(buff.find(Spliter));
		ckeckHeaders();
		if (headers["Content-Type"] == "multipart/form-data")
			splitBody();
		else if (headers["Content-Type"] == "application/octet-stream")
			cout << "mar7aba" << endl;
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
			
		message = "target prob";
		code = 555555;
		return 1;
	}
	else if (version != "HTTP/1.1")
	{
			
		message = "HTTP Version Not Supported";
		code = 505;
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
		message = "Host prob";
		code = 5545;
		return 1;
	}
	return 0;
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
		Getdata gt(*it);
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

void HandleRequest::treatHeaders(std::string hd)
{
	std::stringstream ss(hd);
    std::string line;
    while (std::getline(ss, line)) {
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 2);
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