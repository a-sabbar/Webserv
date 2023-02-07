/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:28:20 by zait-sli          #+#    #+#             */
/*   Updated: 2023/02/07 15:48:28 by zait-sli         ###   ########.fr       */
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
    // cout << path << endl;
    return path;
}

string GetIndex(string Dir,string root)
{
    string index;
    string name;
    string path;

    DIR *dp;
    struct dirent *ep;     
    dp = opendir (Dir.c_str());
    
    path = getPath(Dir,root);
    
    index = "<html> \n";
    index += "<head><title>Index of " + path + "</title></head>\n";
    index += "<body> \n";
    index += "<h1>Index of " + path + "</h1><hr><pre><a href=\""+ path +"../\">../</a> \n";

    while ((ep = readdir (dp)) != NULL)
    { 
        name = string(ep->d_name);
        if (name != "." && name != "..")
            index += "<a href=\"" + path + name + "\">" + name + "</a>\n";
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

void HandleRequest::generateResponse()
{
	string e = "\r\n";
	Response = version + " " + code + " " + message + e;
	Response += "Date: " + GetTime() + e;
	Response += "Connection: " + headers["Connection"] + e;
	Response += "Content-Type: " + BodyCT + e;
	Response += "Content-Length: " + to_string(ResBody.length());
	Response += Spliter + ResBody + e;
}