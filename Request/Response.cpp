/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:28:20 by zait-sli          #+#    #+#             */
/*   Updated: 2023/03/01 14:33:28 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandleRequest.hpp"

#include <sys/stat.h>
#include <cstdlib>
#include <iostream>
#include <dirent.h>


string GetCT(string fileName)
{
    string ext = fileName.substr(fileName.find_last_of(".") + 1);
    string CT;


    if (ext == "png" || ext == "jpg" || ext == "webp" || ext == "tiff" || ext == "svg")
    {
        CT = "image/" + ext;
        if (ext == "svg")
            CT += "+xml"; 
    }
    else if (ext == "pdf" || ext == "zip" || ext == "xml"|| ext == "rtf" || ext == "json")
        CT = "application/" + ext;
    else if (ext == "mp4" || ext == "mpeg")
        CT = "video/" + ext;
    else if (ext == "txt")
        CT = "text/plain";
    else if (ext == "html")
        CT = "text/html";
    return CT;
}

string getPath(string g, string r)
{
    string path;
    string root;
    
    root = r;
    mytrim(g,"/");    
    mytrim(root,"/");
    path = g.substr(root.length());
    path += "/";
    return path;
}

string GetIndex(string Dir,string root,string locName)
{
    string index;
    string name;
    string path;

    DIR *dp;
    struct dirent *ep;     
    dp = opendir (Dir.c_str());
    path = getPath(Dir,root);
    if (locName != "/")
    {
        path = locName + path;
    }
    index = "<html> \n";
    index += "<head><title>Index of " + path + "</title></head>\n";
    index += "<body> \n";
    index += "<h1>Index of "  + path + "</h1><hr><pre><a href=\""+ path +"../\">../</a> \n";

    while ((ep = readdir (dp)) != NULL)
    { 
        name = string(ep->d_name);
        if (name != "." && name != "..")
            index += "<a href=\""  + path + name + "\">" + name + "</a>\n";
    }
    (void) closedir (dp);

    index += "</pre><hr></body>\n";
    index += "<html>";
    return index;
}

string GetTime()
{
    string T;
    time_t givemetime = time(NULL);
    T = string(ctime(&givemetime));
    mytrim(T);
    T += " GMT+1";
    return T;
}

map<string, string> Handle_cgi_body(string &body)
{
    map<string, string> headers;
    string hd = body.substr(0, body.find(Spliter));
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
    if (!body.empty() && body.find(Spliter) != string::npos)
        body = body.substr(body.find(Spliter) + SpliterLen);
    return headers;
}


string Generate_status_body(string code, string message)
{
    string r;
    string m;

    m = code + " " + message;
    r = "<html><head><title>" + m + "</title></head><body><center><h1>" + m + "</h1></center></body></html>" ;
    return r;
}

void HandleRequest::get_default()
{
    if (method.empty())
        method = "GET";
    if (version.empty() || version.compare("HTTP/1.1"))
        version = "HTTP/1.1";
    if (ResBody.empty() && code != "200")
    {
        if (errorPages.find(code) != errorPages.end() && checkExist(errorPages[code]))
        {
            ResBody  = ReadFile(errorPages[code]);
        }
        else
        {
            BodyCT = "text/html";
            ResBody = Generate_status_body(code, message);   
        }
    }
    else if (ResBody.empty() && code == "200")
    {
        ResBody = ReadFile(root + "/home.html");
    }
}

void HandleRequest::generateResponse()
{
    map<string, string> cgiHeaders;
    map<string, string>::iterator it;
    

    get_default();
	string e = "\r\n";
	Response = version + " " + code + " " + message + e;
	Response += "Date: " + GetTime() + e;
    if (reder == true)
	    Response += "Location: " + target + e;
    if (!headers["Connection"].empty())
	    Response += "Connection: " + headers["Connection"] + e;
    if(cgi && cgiType == PHP)
    {
        cgiHeaders = Handle_cgi_body(ResBody);
        for(it = cgiHeaders.begin(); it != cgiHeaders.end(); it++)
        {
	        Response += it->first + ": " + it->second + e;
        }
    }
    else
	    Response += "Content-Type: " + BodyCT + e;
	Response += "Content-Length: " + to_string(ResBody.length());
	Response += Spliter + ResBody + e;
}