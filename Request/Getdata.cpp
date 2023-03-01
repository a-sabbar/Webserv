/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Getdata.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-sli <zait-sli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:42:02 by zait-sli          #+#    #+#             */
/*   Updated: 2023/03/01 14:33:56 by zait-sli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Getdata.hpp"
#include <fstream>
#include <cstdio> 

Getdata::Getdata(string s,string ct ,bool i,map<string, vector<string> > rootLoc,string root)
{
	this->rootLoc = rootLoc;
	this->root = root;
	this->ct = ct;
	if (i == 0)
	{
		string firstPart;
		string data;
		int sp = s.find(Spliter);
		firstPart = s.substr(0,sp);
		data = s.substr(sp + SpliterLen);
		if (firstPart.find("filename=") != string::npos && firstPart.find("filename=\"\"") == string::npos)
		{
			getFileName(firstPart);
			CreatFill(data);
		}
	}
	else
	{
		fileName = RandomName();
		fileName += "." + ct.substr(ct.find("/") + 1);
		CreatFill(s);
	}
}

string Getdata::RandomName(void)
{
	srand(time(NULL));
	size_t r = rand();
	string ran = to_string(r);
	return(ran);
}

void Getdata::getFileName(string str)
{
	size_t t = str.find("filename=") + 10;
	fileName  = str.substr(t, str.find_first_of("\"", t) - t);
}

void Getdata::CreatFill(string data)
{
	ofstream out;
	string g;
	if (rootLoc["upload_store"].size() == 1 )
	{
		g = root + rootLoc["upload_store"].at(0) + "/" + fileName;
	}
	else
		g = root + "/" + fileName;
	out.open(g);
	out << data;
	out.close();
}