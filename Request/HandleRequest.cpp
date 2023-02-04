/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:07:58 by zait-sli          #+#    #+#             */
/*   Updated: 2023/02/04 18:01:55 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleRequest.hpp"
#include <cstdlib>
#include <cstdio>

#include <sys/stat.h>
#include <cstdlib>
#include <iostream>
#include <dirent.h>

HandleRequest::HandleRequest(client_d &client, serv_d &server)
{
	string buff = client.request;
	locations = server.locations;
	root = server.root;
	code = "200";
	message = "OK";
	std::string startLine = buff.substr(0, buff.find_first_of("\n") -1);
	treatSline(startLine);
	treatHeaders(buff.substr(startLine.size() + 2,buff.find(Spliter)));
	ckeckSline();
	checkLoctaions();
	if (code == "200")
	{
		body = buff.substr(buff.find(Spliter) + SpliterLen);
		ckeckHeaders();
		string Type = headers["Content-Type"].substr(0,headers["Content-Type"].find("/"));
		if (!headers["Transfer-Encoding"].compare("chunked"))
		{
			handleChunked();
			cout << "Encoding has been handled" << endl;
		}
		if (method == "GET")
			handleGet();
		if(method == "DELETE")
			handleDelte();
		if (!headers["Content-Type"].compare("multipart/form-data"))
		{
			cout << "Splited the body" << endl;
			splitBody();
		}
		else if (Type == "application" || Type == "image" || Type == "text")
		{
			Getdata gt(body,headers["Content-Type"],1,locations["/"],root);
		}
	}
	cout << "-----------------------------" << endl;
	generateResponse();
	client.Respons = Response;
	client.ResponsLength = Response.length();
	if (headers["Connection"] == "keep-alive")
		client.Con = 1;
	else 
		client.Con = 0;
}

int HandleRequest::ckeckSline()
{
	if (method != "GET" && method != "POST" && method != "DELETE")
	{
		message = "Not Implemented";
		code = "501";
		return 1;
	}
	else if (version != "HTTP/1.1")
	{
			
		message = "HTTP Version Not Supported";
		code = "505";
		return 1;
	}
	else if (target.at(0) != '/')
	{
			
		message = "Bad Request";
		code = "400";
		return 1;
	}
	return 0;
}


bool ifDir(const std::string& name)
{
	DIR *pdir = opendir(name.c_str());

	if(pdir){
		return 1;
	}
	return 0;
}

bool checkExist (const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

string HandleRequest::ReadFile(string File){	
	ifstream myfile; 
	stringstream ss;
	string name;
	myfile.open(File);
	ss << myfile.rdbuf();
	myfile.close();
	name = File.substr(File.find_last_of("/") + 1);
	BodyCT = GetCT(name);
	return ss.str();
}

map<string, vector<string> > HandleRequest::whichLocation()
{
	return locations["/"];
}


void HandleRequest::handleGet()
{
	map<string, vector<string> > location = whichLocation();
	cout << root + target << endl;
	if (ifDir(root + target) && target != "/")
	{
		if (location["autoindex"].at(0) == "on")
		{
			ResBody = GetIndex(root + target, root);
			BodyCT = "text/html";
		}
		else
		{
			code = "403";
			message = "Forbidden";
			ResBody = ReadFile(root + "/403.html");
		}
		return ;
	}
	else if (target == "/")
		ResBody = ReadFile(root + "/index.html");
	else if (!checkExist(root + target))
	{
		code = "404";
		message = "Not Found";
		ResBody = ReadFile(root + "/error404.html");
		return;
	}
	else
		ResBody = ReadFile(root + target);
}

void HandleRequest::handleDelte()
{
	if (!checkExist(root + target) || target == "/")
	{
		code = "408";
		message = "Bad Request";
		return;
	}
	string file = root + target;
	remove(file.c_str());
}

int HandleRequest::ckeckHeaders()
{
	string temp = headers["Content-Type"];
	if(!temp.empty())
	{
		if (temp.find("boundary=") != string::npos)
		{
			Boundary = temp.substr(temp.find("boundary=") + 9);
			temp = temp.substr(0, temp.find("boundary=") - 2);
			headers["Content-Type"] = temp;
		}
	}
	if (headers["Host"].empty())
	{
		message = "Bad Request";
		code = "400";
		return 1;
	}
	return 0;
}

void HandleRequest::checkRootLoctaion()
{
	map<string, vector<string> > rootLoc = locations["/"];
	vector<string>::iterator it;

	if(rootLoc["upload_enable"].at(0) == "on")
		upload = 1;
	it = find(rootLoc["allow_methods"].begin(),rootLoc["allow_methods"].end(),method);
	if (it == rootLoc["allow_methods"].end())
	{
		message = "Method Not Allowed";
		code = "405";
	}
}

void HandleRequest::checkLoctaions()
{
	if(locations.size() == 1)
		checkRootLoctaion();
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
	string endB = Boundary + "---\r\n";
	Boundary += "\r\n";
	
	b = body.find(Boundary, b) + Boundary.length() + 4;
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
		Getdata gt(*it,headers["Content-Type"],0,locations["/"],root);
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
	{
		queryString = target.substr(target.find("?"));
		target = target.substr(0,target.find("?"));
	}
}

void mytrim(std::string &s, const std::string &toTrim)
{
	s = s.substr(s.find_first_not_of(toTrim), s.length());
	s = s.substr(0, s.find_last_not_of(toTrim) +1);
}

void HandleRequest::treatHeaders(std::string hd)
{
	stringstream ss(hd);
    string line;
    while (getline(ss, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            string key = line.substr(0, pos);
            string value = line.substr(pos + 2);
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