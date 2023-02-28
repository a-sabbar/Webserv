/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:07:58 by zait-sli          #+#    #+#             */
/*   Updated: 2023/02/28 14:04:07 by asabbar          ###   ########.fr       */
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
	cgi = false;
	mbs = server.max_body_size;
	locations = server.locations;
	root = server.root;
	errorPages = server.pageErrorpageError;
	code = "200";
	message = "OK";
	if (buff == "timeout")
	{
		code = "408";
		message = "Request Timeout";
	}
	std::string startLine = buff.substr(0, buff.find_first_of("\n") -1);
	treatSline(startLine);
	if (code == "200")
	{
		treatHeaders(buff.substr(startLine.size() + 2,buff.find(Spliter)));
		checkTarget();

		checkLoctaions();
		if (loc.find("return") != loc.end())
		{
			if (loc["return"].size() == 2)
			{
				method = "GET";
				code = loc["return"].at(0);
				target = loc["return"].at(1);
			}
			checkLoctaions();
		}
		ckeckSline();
		fixTarget();
	}
	if (code == "200" || ifRederection())
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
		{
			handleGet();
		}
		if(method == "DELETE")
			handleDelte();
		if (!headers["Content-Type"].compare("multipart/form-data"))
		{
			cout << "Splited the body" << endl;
			splitBody();
		}
		else if (Type == "application" || Type == "image" || Type == "text" )
		{
			string name ,ext;
			name = target.substr(target.find_last_of("/") + 1);
			ext = name.substr(name.find_first_of(".") + 1);
			if (ext == "php" || ext == "py")
			{
				if (ext == "php")
					cgiType = PHP;
				if (ext == "py")
					cgiType = PY;
				ResBody = handle_cgi(root + target);
			}
			else
				Getdata gt(body,headers["Content-Type"],1,locations["/"],root);
		}
	}
	if (headers["Connection"] == "keep-alive")
		client.Con = 1;
	else
	{
		client.Con = 0;
		headers["Connection"] = "close";
	}
	generateResponse();
	client.Respons = Response;
	client.ResponsLength = Response.length();
	// cout << Response << endl;
}

int HandleRequest::ifRederection()
{
	int intCode = atoi(code.c_str());
	
	if (intCode >= 300 && intCode <= 308  && intCode != 306)
	{	
		switch (intCode) 
		{
			case 300 :
				message = "Multiple Choices"; break;
			case 301 :
				message = "Moved Permanently"; break;
			case 302 :
				message = "Found"; break;
			case 303 :
				message = "See Other"; break;
			case 304 :
				message = "Not Modified"; break;
			case 305 :
				message = "Use Proxy"; break;
			case 307 :
				message = "Temporary Redirect"; break;
			case 308 :
				message = "Permanent Redirect"; break;
		}
		return 1;
	}
	return 0;
}

void HandleRequest::checkTarget()
{
	size_t f;
	string replacement;
	string hex;
	f = target.find("%");
	while(f != string::npos)
	{
		hex = target.substr(f + 1);
		hex = hex.substr(0 ,2);
		replacement = strtoul(hex.c_str(), NULL, 16);
		target = target.replace(f,3,replacement);
		f = target.find("%");
	}
}

void HandleRequest::fixTarget()
{
	string path = root + target;
	char rootPath[PATH_MAX];
	char childPath[PATH_MAX];


	// if (
		realpath(root.c_str(), rootPath) ;
		realpath(path.c_str(), childPath);
	// {
	// 	cout << "olaasdasdasdasdasdasdssadsdasdasd" << endl;
	// 	code = "404";
	// 	message = "Not Found";
	// }
	root = rootPath;
	path = childPath;
	if (path.find(root) == 0);
	else
	{
		code = "403";
		message = "Forbidden";
	}

}

void HandleRequest::ckeckSline()
{

	if (method != "GET" && method != "POST" && method != "DELETE")
	{
		message = "Method Not Allowed";
		code = "405";
	}
	if (version != "HTTP/1.1")
	{	
		message = "HTTP Version Not Supported";
		code = "505";
	}
	else if (target.at(0) != '/')
	{
		message = "Bad Request";
		code = "400";
	}
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
	string ext;
	size_t p;

	name = File.substr(File.find_last_of("/") + 1);
	p = name.find(".");
	if (p != string::npos)
		ext = name.substr(name.find_first_of(".") + 1);
	if (ext == "php" || ext == "py")
	{
		if (ext == "php")
			cgiType = PHP;
		if (ext == "py")
			cgiType = PY;
		return handle_cgi(File);
	}
	myfile.open(File);
	ss << myfile.rdbuf();
	myfile.close();
	BodyCT = GetCT(name);
	return ss.str();
}

map<string, vector<string> > HandleRequest::whichLocation()
{
	string loc = target;
	string name ,ext;


	if (locations.find(loc) != locations.end())
		return locations[loc];

	name = target.substr(target.find_last_of("/") + 1);
	if (name.find(".") != string::npos)
		ext = name.substr(name.find_last_of(".") + 1);

	if (ext == "php" || ext == "py")
	{
		loc = "*." + ext;
		if (locations.find(loc) != locations.end())
		{
			return locations[loc];
		}
		else
		{
			code = "501";
			message = "Not Implemented";
		}
	}
	while(loc != "/" && code != "501")
	{
		mytrim(loc,"/");
		loc = "/" + loc;
		if (locations.find(loc) != locations.end())
			return locations[loc];
		else
		{
			mytrim(loc,"/");
			loc = "/" + loc;
			loc = loc.substr(0,loc.find_last_of("/") + 1);
		}
	}
	return locations["/"];
}


void HandleRequest::handleGet()
{

	if (root != "/")
	{
		mytrim(root,"/");
		root = "/" + root;
	}
	if (ifDir(root + target))
	{
		if (loc.find("index") != loc.end() && checkExist(root + target + "/" +  loc["index"].at(0)))
		{
			ResBody = ReadFile(root + target + "/" + loc["index"].at(0));
		}
		else if (checkExist(root + target + "/index.html"))
		{
			ResBody = ReadFile(root + target + "/index.html");
		}
		else if (loc["autoindex"].at(0) == "on")
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
	}
	// else if (target == "/")
	// {
	// 	ResBody = ReadFile(root + "/home.html");	
	// }
	else if (!checkExist(root + target))
	{
		code = "404";
		message = "Not Found";
		ResBody = ReadFile(root + "/error404.html");
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

void HandleRequest::fix_target()
{
	string loc_name = loc["name"].at(0);
	if (loc_name != "/")
	{
		if (loc_name  == target)
			target = "/";
		else
			target = target.substr(loc_name.length());
	}
}

void HandleRequest::checkLoctaions()
{
	loc = whichLocation();
	fix_target();
	vector<string>::iterator it;
	if(loc.find("root") != loc.end())
		root = loc["root"].at(0);
	if (code != "501")
	{
		it = find(loc["allow_methods"].begin(),loc["allow_methods"].end(),method);
		if (it == loc["allow_methods"].end())
		{
			code = "405";
			message = "Method Not Allowed";
		}
	}

}

void HandleRequest::handleChunked()
{
	string tbody;
	string hexlen;
	size_t dec = 1;	
	while(dec && !body.empty())
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
		Getdata gt(*it,headers["Content-Type"],0,locations["/"],root);
	}
}

void HandleRequest::treatSline(string startLine)
{
	if(startLine.size() < 14)
	{
		code = "400";
		message = "Bad Request";
		return;
	}
	method = startLine.substr(0,startLine.find_first_of(" "));
	// if (method.length() <= 3 )
	// {
	// 	message = "Not Implemented";
	// 	code = "501";
	// 	return;
	// 	}
	startLine = startLine.substr(method.size() + 1);
	target = startLine.substr(0,startLine.find_first_of(" "));
	startLine = startLine.substr(target.size() + 1);
	version = startLine.substr(0,startLine.find_first_of(" "));
	if (target.find("?") != string::npos)
	{
		queryString = target.substr(target.find("?") + 1);
		target = target.substr(0,target.find("?"));
	}
}

void mytrim(string &s, const string &toTrim)
{
	s = s.substr(s.find_first_not_of(toTrim), s.length());
	if(!s.empty())
		s = s.substr(0, s.find_last_not_of(toTrim) + 1);
}

void HandleRequest::treatHeaders(string hd)
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
	
	if(atoi(headers["Content-Length"].c_str()) > (int)mbs)
	{
		code = "413";
		message = "Content Too Large";
	}

}

HandleRequest::~HandleRequest()
{
	
}


///check request line => methode $$ uri.at(0) = '/' && http version || query string ?key=value&&key=value
///check headrs host !bad request &&  if(post)=> content lenght && content type && content lenght transfer encoded chencd
///parse body : multipart/form-data; && 